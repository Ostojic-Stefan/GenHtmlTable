#pragma once

#include <string>
#include <sstream>
#include <algorithm>

#include "structureGeneration.hpp"
#include "Rectangle.hpp"
#include "utils.hpp"

std::string genTable(const IterateStructure &structure);
Dimensions getTableDimensions(const std::vector<Rectangle> &rectangles);