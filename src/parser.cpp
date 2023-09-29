#include "headers/parser.hpp"

std::vector<size_t> getCoordsFromString(const std::string &str)
{
    std::vector<size_t> res;
    std::string tmp;
    for (size_t i = 0; i < str.size(); ++i)
    {
        tmp = "";
        while (str[i] != ',')
        {
            tmp += str[i];
            ++i;
        }
        res.push_back(std::stoi(tmp));
    }
    return res;
}

Rectangle parseRectangle(const std::string &line)
{
    size_t tlStartPos = line.find('(');
    size_t tlEndPos = line.find(')');

    std::string tlCoords = line.substr(tlStartPos + 1, tlEndPos - tlStartPos - 1);

    auto tdCoordsVec = getCoordsFromString(tlCoords);

    size_t brStartPos = line.find('(', tlEndPos + 1);
    size_t brEndPos = line.find(')', tlEndPos + 1);

    std::string brCoords = line.substr(brStartPos + 1, brEndPos - brStartPos - 1);

    auto brCoordsVec = getCoordsFromString(brCoords);

    return {{tdCoordsVec[0], tdCoordsVec[1]},
            {brCoordsVec[0], brCoordsVec[1]}};
}

std::vector<Rectangle> parseInput(const std::string &path)
{
    std::vector<Rectangle> rectangles;

    std::ifstream fStream(path);
    std::string line;
    while (std::getline(fStream, line))
    {
        line.erase(std::remove_if(line.begin(), line.end(), [](char ch)
                                  { return std::isspace(ch); }),
                   line.end());
        rectangles.push_back(parseRectangle(line));
    }
    return rectangles;
}