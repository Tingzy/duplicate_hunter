#pragma once
#include <deque>
#include "file_compare_buffer.hpp"

class FileComparator 
{
public:
    // Constructor.
    FileComparator(std::shared_ptr<FileCompareBuffer> compareBuffer);

    // Compare 2 files byte by byte. 
    bool isDuplicate(const std::filesystem::path& file1, const std::filesystem::path& file2);

    // Get a list of files with the same hash (from m_compareBuffer).
    // CHeck if they are real dupes using isDuplicate().
    // Save duplicate. to dupList.
    void saveDupe();

    bool bufferEmpty() const;

private:
    // The buffer to read and compare.
    std::shared_ptr<FileCompareBuffer> m_compareBuffer;

    // The list of duplicate files.
    // A stack of lists that contain duplicate files. Each vector is a set of duplicate files.
    // Why deque? Need removing in the middle in rare case. No order needed. 
    std::deque<std::forward_list<std::filesystem::path>> dupeList;

    std::mutex dupeListMutex;

    std::condition_variable dupeListCv;
};