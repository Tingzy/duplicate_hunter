#include <filesystem>
#include <iostream>
#include <unordered_map>
#include "file_reader.hpp"
#include "xxhash.h"
#include "utilities/read_path_to_file.hpp"

namespace fs = std::filesystem;

FileReader::FileReader() 
{
    // Initialize the file process buffer and file compare buffer.
    m_processBuffer = std::make_unique<FileProcessBuffer>();
    m_compareBuffer = std::make_shared<FileCompareBuffer>();
}

void FileReader::addFilesForProcessing(const fs::path& directoryPath) 
{
    // Temporary map to store file sizes and their corresponding full paths.
    // This is a big list so it is going to take lots of space. Only use local var to store.
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
    m_processBuffer->isDone();
}

void FileReader::addFileForComparison() 
{
    // Get a file from the fileProcessBuffer for comparison.
    fs::path filePath = m_processBuffer->getFile();

    // Store the hash value and the full path of the file into the m_compareBuffer for duplicate detection.
    // The hashFunction() will run first because function arguments are evaluated before function call. Therefore, no Mutex is lock to wait for hashFunction().
    if (!filePath.empty())
    {
        m_compareBuffer->addFile(hashFunction(filePath), filePath);
    }
}

size_t FileReader::hashFunction(const fs::path& filePath) 
{
    auto buffer = readPathToBytes(filePath);
    // XXH64 returns uint64_t. So this should work on 64-bit platform.
    return static_cast<size_t>(XXH64(buffer.data(), buffer.size(), 0));
}

std::shared_ptr<FileCompareBuffer> FileReader::getCompareBuffer() const
{
    return m_compareBuffer;
}

bool FileReader::bufferEmpty() const
{
    return m_compareBuffer->getFileCount() == 0;
}