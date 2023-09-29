#pragma once

#include <string>
#include <fstream>
#include <random>
#include <iomanip>

namespace utils
{
    std::string readAllFileContents(const std::string &path);
    void dumpToFile(const std::string &path, const std::string &str);
    std::string getRandomColor();
}