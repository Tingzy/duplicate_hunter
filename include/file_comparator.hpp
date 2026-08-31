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

private:
    // The buffer to read and compare.
    std::shared_ptr<FileCompareBuffer> m_compareBuffer;

    // The list of duplicate files.
    std::deque<std::vector<std::filesystem::path>> dupList;
};