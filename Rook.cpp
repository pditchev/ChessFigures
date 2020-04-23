#include "Rook.h"
#include "Initializer.h"

void Rook::fillCache(const Initializer& initializer)
{
    FieldPointer rows = initializer.boardDimensions.first;
    FieldPointer cols = initializer.boardDimensions.second;
    FieldPointer total_f = rows * cols;

    for (FieldPointer f = 0; f < total_f; ++f)
    {
        std::vector<FieldPointer> temp;

        FieldPointer st = f % cols;  // put column into temp vector
        for (FieldPointer i = st; i < total_f; i += cols)
        {
            if (i == f) continue;
            temp.push_back(i);
        }

        // put row into temp vector
        for (FieldPointer i = cols * (f / cols); i < cols * (f / cols + 1); ++i)
        {
            if (i == f) continue;
            temp.push_back(i);
        }

        cache[f] = std::move(temp);
    }
}

std::unordered_map<FieldPointer, std::vector<FieldPointer>> Rook::cache;
