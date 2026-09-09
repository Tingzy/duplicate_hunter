#include <iostream>
#include "utilities/read_path_to_file.hpp"

void printHex(const std::vector<char>& buffer) 
{
    for (size_t i = 0; i < buffer.size(); ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                   << (static_cast<int>(buffer[i]) & 0xFF);
        std::cout << " ";
    }
    std::cout << std::dec << std::endl;
}

int main(int argc, char *argv[])
{
    std::vector<char> content = readPathToBytes("D:/C++/binary_tree/Readme.txt");
    printHex(content);

    return 0;
}             
