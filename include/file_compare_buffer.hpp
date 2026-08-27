#pragma once

#include <unordered_map>
#include <filesystem>
#include <mutex>

class FileCompareBuffer {

public:

    //Constructor.
    FileCompareBuffer() = default;

    //Destructor.
    ~FileCompareBuffer() = default;

    // Copy constructor.
    FileCompareBuffer(const FileCompareBuffer&) = delete;   
        
    // Copy assignment operator.
    FileCompareBuffer& operator=(const FileCompareBuffer&) = delete;

    // Move constructor.
    FileCompareBuffer(FileCompareBuffer&&) = delete;

    // Move assignment operator.
    FileCompareBuffer& operator=(FileCompareBuffer&&) = delete;

    // Returns the number of occupied buckets in the fileMapBySize.
    // This can be used to analyze the distribution of file sizes in the map.
    // \return The number of occupied buckets in the fileMapBySize.
    size_t getBucketOccupiedCount() const;

    // Returns the number of files detected in the directory.
    size_t getFileCount() const;

    // Adds file hash and its corresponding full path to the fileMapByHash for duplicate detection.
    // \param hashValue The hash value of the file.
    // \param filePath The full path of the file.   
    void addFile(size_t hashValue, const std::filesystem::path& filePath);

    // Choose a hash value (at fileMapByHash.begin()).
    // If no duplicate, remove from fileMapByHash, if duplicates exist, add all to a vector, return the vector and remove all from fileMapByHash.
    // \return a vector of files, if there is more than 1 file with that same hash value.
    std::vector<std::filesystem::path> getSameHashBucket();

private:
    // Mutex to protect access to the shared buffer.
    std::mutex compareBufferMutex;

    //Condition variable to signal when the buffer is ready for processing.
    std::condition_variable compareBufferCv;

    // Map to store file hashes and their corresponding full paths.
    std::unordered_multimap<size_t, std::filesystem::path> fileMapByHash;
};