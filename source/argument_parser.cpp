#include "argument_parser.hpp"
#include <iostream>

std::string parseArguments(int argc, char *argv[]) {
    if (argc > 2) {
        throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <directory>");
    }

    if (argc == 1) {
        return "D:\\C++"; // Default path
    }
        
    return argv[1];
}