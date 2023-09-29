#include "headers/utils.hpp"

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

    std::string getRandomColor()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 255);

        int red = dis(gen);
        int green = dis(gen);
        int blue = dis(gen);

        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << red
           << std::hex << std::setw(2) << std::setfill('0') << green
           << std::hex << std::setw(2) << std::setfill('0') << blue;

        std::string hexColor = ss.str();

        return "#" + hexColor;
    }
}