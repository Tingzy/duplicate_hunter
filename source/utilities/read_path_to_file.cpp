#include "utilities/read_path_to_file.hpp"
#include <fstream>
#include <iostream>

std::vector<char> readPathToBytes(const std::filesystem::path& filePath)
{
    auto fileSize = std::filesystem::file_size(filePath);
    std::ifstream fileStream(filePath, std::ios::binary);
    if (!fileStream.is_open())
    {
        return {};
    }

    std::vector<char> buffer(fileSize);
    fileStream.read(buffer.data(), fileSize);
    return buffer;

}