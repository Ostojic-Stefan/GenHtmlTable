#pragma once
#include <utility>

struct Rectangle
{
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