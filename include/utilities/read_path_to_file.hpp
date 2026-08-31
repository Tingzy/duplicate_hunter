#pragma once
#include <vector>
#include <filesystem>

std::vector<char> readPathToBytes(const std::filesystem::path& filePath);