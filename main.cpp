#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include "Rectangle.hpp"

struct Dimensions
{
    int colSpan, rowSpan;
};

struct Range
{
    int start, end;
};

using IterateStructure = std::map<int, std::vector<std::pair<int, Dimensions>>>;

const Rectangle *containsRect(int i, int j, const std::vector<Rectangle> &rectangles)
{
    for (const auto &rect : rectangles)
    {
        if (rect.topleft.first == i && rect.topleft.second == j)
            return &rect;
    }
    return nullptr;
}

bool IsInRange(const std::vector<Range> &ranges, int idx)
{
    for (const auto &range : ranges)
    {
        if (idx >= range.start && idx <= range.end)
            return true;
    }
    return false;
}

IterateStructure GenStructure(int width, int height, const std::vector<Rectangle> &rectangles)
{
    IterateStructure structure;
    std::unordered_map<int, std::vector<Range>> ignoreMap;

    for (int i = 1; i <= height; ++i)
    {
        for (int j = 1; j <= width; ++j)
        {
            // check for the igore cells
            if (ignoreMap.find(i) != ignoreMap.end())
            {
                const auto &list = ignoreMap[i];
                if (IsInRange(list, j))
                    continue;
            }

            const Rectangle *rect = containsRect(j, i, rectangles);
            if (rect)
            {
                int row = rect->topleft.second;
                int col = rect->topleft.first;
                structure[row].push_back({col, {rect->Width(), rect->Height()}});

                // ignore cell addition logic
                for (int k = rect->topleft.second + 1; k <= rect->bottomright.second; ++k)
                    ignoreMap[k].push_back({rect->topleft.first, rect->bottomright.first});

                j = rect->bottomright.first;
                continue;
            }
            structure[i].push_back({j, {1, 1}});
        }
    }

    return structure;
}

std::string GenTable(const IterateStructure &structure)
{
    std::string result;

    for (const auto &[_row, data] : structure)
    {
        result += "<tr>\n";
        for (const auto &pair : data)
        {
            result += "\t<td rowspan='" + std::to_string(pair.second.rowSpan) + "' colspan='" + std::to_string(pair.second.colSpan) + "'></td>\n";
        }
        result += "</tr>\n";
    }
    return result;
}

int parseInt(char ch)
{
    return ch - '0';
}

std::vector<int> getCoordsFromString(const std::string &str)
{
    std::vector<int> res;
    std::string tmp;
    for (int i = 0; i < str.size(); ++i)
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

Rectangle ParseRectangle(const std::string &line)
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
        rectangles.push_back(ParseRectangle(line));
    }
    return rectangles;
}

Dimensions GetTableDimensions(const std::vector<Rectangle> &rectangles)
{
    int width = (*std::max_element(rectangles.begin(), rectangles.end(), [](const Rectangle &rect1, const Rectangle &rect2)
                                   { return rect1.bottomright.first < rect2.bottomright.first; }))
                    .bottomright.first;

    int height = (*std::max_element(rectangles.begin(), rectangles.end(), [](const Rectangle &rect1, const Rectangle &rect2)
                                    { return rect1.bottomright.second < rect2.bottomright.second; }))
                     .bottomright.second;

    return {width, height};
}

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

int main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //     std::cerr << "Usage: gentable <path_to_file>\n";
    //     exit(1);
    // }

    // std::filesystem::path filePath = argv[1];
    // if (!std::filesystem::exists(filePath))
    // {
    //     std::cerr << "Provided File does not exist\n";
    //     exit(1);
    // }

    // std::vector<Rectangle> rectangles = parseInput(argv[1]);

    std::vector<Rectangle> rectangles = parseInput("Rectangles.txt");

    auto res = GetTableDimensions(rectangles);

    int width = res.colSpan;
    int height = res.rowSpan;

    auto structure = GenStructure(width, height, rectangles);

    std::string htmlTemplate = readAllFileContents("template.html");
    std::string result = GenTable(structure);

    std::string token = "{{#input}}";
    size_t pos = htmlTemplate.find(token);

    if (pos != std::string::npos)
        htmlTemplate.replace(pos, token.size(), result);

    dumpToFile("output.html", htmlTemplate);

    return 0;
}
