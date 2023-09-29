#pragma once
#include <utility>

struct Rectangle
{
    // Rectangle() = default;
    // Rectangle(int x1, int y1, int x2, int y2)
    // {
    //     topleft = {x1, y1};
    //     bottomright = {x2, y2};
    // }

    inline int Width() const
    {
        return bottomright.first - topleft.first + 1;
    }

    inline int Height() const
    {
        return bottomright.second - topleft.second + 1;
    }

    std::pair<int, int> topleft;
    std::pair<int, int> bottomright;
};