#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

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
const Rectangle *containsRect(int i, int j, const std::vector<Rectangle> &rectangles);
bool isInRange(const std::vector<Range> &ranges, int idx);
IterateStructure genStructure(int width, int height, const std::vector<Rectangle> &rectangles);