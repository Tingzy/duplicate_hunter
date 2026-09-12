#pragma once

#include <vector>
#include <filesystem>
#include "file_process_buffer.hpp"
#include "file_compare_buffer.hpp"

// Read directory contents and store file hashes and their full paths
// in a map for duplicate detection.
class FileReader {
public:
    // Connstructor.
    explicit FileReader();

    // Reads the directory contents.
    // Stores all files and its size into a temporary map.
    // From this map, only store the files with the same size into fileProcessBuffer for further processing
    // \param directoryPath The directory path to be processed.
    void addFilesForProcessing(const std::filesystem::path& directoryPath);

    // From the fileProcessBuffer, read the file and store its hash and full path into fileCompareBuffer for duplicate detection.
    // Uses hashFunction to generate a hash value for each file.
    void addFileForComparison();

    // Returns the shared pointer to the fileCompareBuffer.
    // \return A shared pointer to the fileCompareBuffer.
    std::shared_ptr<FileCompareBuffer> getCompareBuffer() const;

    // Check if the fileCompareBuffer is empty.
    // \return true if the fileCompareBuffer is empty, false otherwise.
    bool bufferEmpty() const;

private:

    // The buffer to store the file paths for further processing (hashing and comparison).
    std::unique_ptr<FileProcessBuffer> m_processBuffer;

    //The buffer to store the file hashes and their corresponding full paths for duplicate detection.
    std::shared_ptr<FileCompareBuffer> m_compareBuffer;

    // Flag to indicate that all files have been added to the process buffer.
    bool m_done = false;

    // Hash function to generate a hash value for a given file path.
    // \param filePath The path of the file to be hashed.
    // \return A hash value representing the file.
    size_t hashFunction(const std::filesystem::path& filePath);
};