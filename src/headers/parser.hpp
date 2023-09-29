#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include "Rectangle.hpp"

std::vector<size_t> getCoordsFromString(const std::string &str);
Rectangle parseRectangle(const std::string &line);
std::vector<Rectangle> parseInput(const std::string &path);