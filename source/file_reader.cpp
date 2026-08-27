#include <filesystem>
#include <iostream>
#include <unordered_map>
#include "file_reader.hpp"

namespace fs = std::filesystem;

FileReader::FileReader(const fs::path& directoryPath) {
    // Initialize the file process buffer and file compare buffer.
    m_processBuffer = std::make_unique<FileProcessBuffer>();
    m_compareBuffer = std::make_shared<FileCompareBuffer>();
}

void FileReader::addFilesForProcessing(const fs::path& directoryPath) {
    // Temporary map to store file sizes and their corresponding full paths.
    std::unordered_multimap<size_t, std::filesystem::path> fileMapBySize;

    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        if (!entry.is_directory())
        {
            fileMapBySize.insert({entry.file_size(), entry.path()});
        }
        
    }

    // The files with the same size will be stored to fileProcessBuffer for further duplicate detection.
    for (const auto& [size, path] : fileMapBySize) {
        if (fileMapBySize.count(size) != 1) {
            // Add to fileProcessBuffer for further processing (hashing and comparison).
            m_processBuffer->addFile(path);
        }
    }
}

void FileReader::addFileForComparison() {
    // Get a file from the fileProcessBuffer for comparison.
    fs::path filePath = m_processBuffer->getFile();

    // Store the hash value and the full path of the file into the m_compareBuffer for duplicate detection.
    m_compareBuffer->addFile(hashFunction(filePath), filePath);
}
size_t FileReader::hashFunction(const fs::path& filePath) {
    // Use some library here to hash.
    return {};
}