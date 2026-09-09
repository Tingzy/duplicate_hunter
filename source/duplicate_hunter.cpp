#include "file_reader.hpp"
#include "argument_parser.hpp"
#include <iostream>
#include "utilities/read_path_to_file.hpp"
#include <thread>
#include <vector>
#include <filesystem>
#include "file_comparator.hpp"

int main(int argc, char *argv[])
{
    // Parse command-line arguments to get the directory path.
    std::string directoryPath = parseArguments(argc, argv);

    // Create a FileReader object to read the directory contents and stores the hashes and paths of the files for duplicate detection.
    FileReader reader{};

    // This thread will read the directory content, pickout the files with identical file sizes to a buffer.
    std::thread addFilesThread([&reader, &directoryPath]() {
        try {
            reader.addFilesForProcessing(directoryPath);
        } catch (const std::exception& e) {
            std::cerr << "Error in addFilesThread: " << e.what() << std::endl;
            return -1;
        }
    });

    // Create multiple threads to read files from the buffer, generate their hashes, and store them to further checking if they files are truly identical by comparing byte-by-byte.
    // These threads works asynchronously with addFilesThread.
    std::vector<std::thread> hashThreads;

    for (int i = 0; i < 4; ++i) {
        hashThreads.emplace_back([&reader]() {
            while (true) {
                try {
                    reader.addFileForComparison();
                } catch (const std::exception& e) {
                    std::cerr << "Error in thread: " << e.what() << std::endl;
                    break;
                }
            }
        });
    }

    addFilesThread.join();
    for (auto& thread : hashThreads) {
        thread.join();
    }

    // Create a FileComparator object to compare files with the same hash and save duplicates.
    // Now from the buffer which contains the buckets of files with the same hash, just go through all again and do a byte-by-byte comparison.
    FileComparator comparator{reader.getCompareBuffer()};

    std::vector<std::thread> compareThreads;

    for (int i = 0; i < 4; ++i) {
        compareThreads.emplace_back([&comparator]() {
            while (true) {
                try {
                    comparator.saveDupe();
                } catch (const std::exception& e) {
                    std::cerr << "Error in thread: " << e.what() << std::endl;
                    break;
                }
            }
        });
    }

    for (auto& thread : compareThreads) {
        thread.join();
    }

    return 0;
}             
