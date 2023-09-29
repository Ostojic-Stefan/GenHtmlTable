#pragma once

#include <string>
#include <fstream>

namespace utils
{
    std::string readAllFileContents(const std::string &path)
    {
        std::ifstream file(path);
        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return fileContents;
    }

    void dumpToFile(const std::string &path, const std::string &str)
    {
        std::ofstream file(path, std::ios::binary);
        file.write(str.c_str(), str.size());
    }
}