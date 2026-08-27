#include "file_reader.hpp"
#include "argument_parser.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    try {
        // Parse command-line arguments to get the directory path.
        std::string directoryPath = parseArguments(argc, argv);

        // Create a FileReader object to read the directory contents and stores the hashes and paths of the files for duplicate detection.
        FileReader reader(directoryPath);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}             
