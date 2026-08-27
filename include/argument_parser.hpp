#pragma once

#include <string>

// Parses command-line arguments and returns the directory path to be processed.
// Throws std::invalid_argument if the number of arguments is incorrect.
// \param argc The number of command-line arguments.
// \param argv The array of command-line argument strings.
// \return The directory path specified by the user or a default path if none is provided.
std::string parseArguments(int argc, char *argv[]);
