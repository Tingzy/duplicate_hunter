#include "file_comparator.hpp"

FileComparator::FileComparator(std::shared_ptr<FileCompareBuffer> compareBuffer) : m_compareBuffer(compareBuffer)
{

}

bool FileComparator::isDuplicate(const std::filesystem::path& file1, const std::filesystem::path& file2)
{
    // TODO: Implement.
    return {};
}