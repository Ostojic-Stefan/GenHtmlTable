#include "headers/structureGeneration.hpp"

const Rectangle *containsRect(int i, int j, const std::vector<Rectangle> &rectangles)
{
    for (const auto &rect : rectangles)
    {
        if (rect.topleft.first == i && rect.topleft.second == j)
            return &rect;
    }
    return nullptr;
}

bool isInRange(const std::vector<Range> &ranges, int idx)
{
    for (const auto &range : ranges)
    {
        if (idx >= range.start && idx <= range.end)
            return true;
    }
    return false;
}

IterateStructure genStructure(int width, int height, const std::vector<Rectangle> &rectangles)
{
    IterateStructure structure;
    std::unordered_map<int, std::vector<Range>> ignoreMap;

    for (int i = 1; i <= height; ++i)
    {
        for (int j = 1; j <= width; ++j)
        {
            if (ignoreMap.find(i) != ignoreMap.end())
            {
                const auto &list = ignoreMap[i];
                if (isInRange(list, j))
                    continue;
            }

            const Rectangle *rect = containsRect(j, i, rectangles);
            if (rect)
            {
                int row = rect->topleft.second;
                int col = rect->topleft.first;
                structure[row].push_back({col, {rect->Width(), rect->Height()}});

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
