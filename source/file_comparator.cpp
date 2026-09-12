#include "file_comparator.hpp"
#include "utilities/read_path_to_file.hpp"

FileComparator::FileComparator(std::shared_ptr<FileCompareBuffer> compareBuffer) : m_compareBuffer(compareBuffer)
{

}

bool FileComparator::isDuplicate(const std::filesystem::path& file1, const std::filesystem::path& file2)
{
    return readPathToBytes(file1) == readPathToBytes(file2);
}

void FileComparator::saveDupe()
{
    std::forward_list<std::filesystem::path> dupes = m_compareBuffer->getSameHashBucket();
    if (dupes.empty())
    {
        return;
    }
    auto iter = dupes.begin();
    while (iter != dupes.end())
    {
        std::unique_lock<std::mutex> lock(dupeListMutex);
        for (auto& bucket : dupeList)
        {
            // Compare *iter with bucket.front().
            // The comparison is to recheck if the files are really duplicates byte-by-byte before adding them to the final list.
            if (isDuplicate(*iter, bucket.front()))
            {
                bucket.push_front(*iter);
                break;
            }
        }
        // If there is no Bucket for its kind in the dupeList, add new bucket.
        // If the hash function works efficiently, it should not go to this  after the first element of dupes is added.
        std::forward_list<std::filesystem::path> newList;
        newList.push_front(*iter);
        dupeList.push_back(newList);
        ++iter;
    }
}

bool FileComparator::bufferEmpty() const
{
    return m_compareBuffer->getFileCount() == 0;
}