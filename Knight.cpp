#include "Knight.h"
#include "Initializer.h"

void Knight::fillCache(const Initializer& initializer)
{
    FieldPointer rows = initializer.boardDimensions.first;
    FieldPointer cols = initializer.boardDimensions.second;
    FieldPointer total_f = rows * cols;

    for (FieldPointer f = 0; f < total_f; ++f)
    {
        std::vector<FieldPointer> temp;

        for (const auto& c : att)
        {
            auto row = f / cols + c.first;
            auto col = f % cols + c.second;

            if (row >= 0 && row < rows && col >= 0 && col < cols)
            {
                temp.push_back(row * cols + col);
            }
        }

        cache[f] = std::move(temp);
    }
}

std::unordered_map<FieldPointer, std::vector<FieldPointer>> Knight::cache;