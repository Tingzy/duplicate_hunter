#include "file_compare_buffer.hpp"

size_t FileCompareBuffer::getBucketOccupiedCount() const 
{
    size_t count = 0;
    for (size_t i = 0; i < fileMapByHash.bucket_count(); ++i) {
        if (fileMapByHash.bucket_size(i) > 0) {
            ++count;
        }
    }
    return count;
}

size_t FileCompareBuffer::getFileCount() const 
{
    return fileMapByHash.size();
}

void FileCompareBuffer::addFile(size_t hashValue, const std::filesystem::path& filePath)
{
    std::lock_guard<std::mutex> lock(compareBufferMutex);
    fileMapByHash.insert({hashValue, filePath});
    compareBufferCv.notify_one();
}

std::forward_list<std::filesystem::path> FileCompareBuffer::getSameHashBucket() 
{
    std::forward_list<std::filesystem::path> sameHashList;
    std::unique_lock<std::mutex> lock(compareBufferMutex);
    compareBufferCv.wait(lock, [this] { return !fileMapByHash.empty();});

    // Pop the unique-hash files out of the map until iterator returns a non-unique hash. 
    auto it = fileMapByHash.begin();
    while (it != fileMapByHash.end())
    {
        if (fileMapByHash.count(it->first) == 1)
        {
            it = fileMapByHash.erase(it);
            continue;  
        }
        // If there is more than 1 elements with the same hash, add all to a vector to return.
        // Then erase (pop) those processed element from the map.
        auto range = fileMapByHash.equal_range(it->first);
        for (auto itEquRange = range.first; itEquRange != range.second; ++itEquRange)
        {
            sameHashList.push_front(itEquRange->second);
        }

        fileMapByHash.erase(it->first);
        break;
    }

    return sameHashList;
}
