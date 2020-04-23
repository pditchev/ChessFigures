#include "Queen.h"
#include "Initializer.h"

void Queen::fillCache(const Initializer& initializer)
{
    FieldPointer rows = initializer.boardDimensions.first;
    FieldPointer cols = initializer.boardDimensions.second;
    FieldPointer total_f = rows * cols;

    for (FieldPointer f = 0; f < total_f; ++f)
    {
        std::vector<FieldPointer> temp;

        FieldPointer st = f % cols;
        for (FieldPointer i = st; i < total_f; i += cols)
        {
            if (i == f) continue;
            temp.push_back(i);
        }

        for (FieldPointer i = cols * (f / cols); i < cols * (f / cols + 1); ++i)
        {
            if (i == f) continue;
            temp.push_back(i);
        }

        //------------------------

        auto row = f / cols;
        auto col = f % cols;
        auto diff = row - col;
        row = 0, col = 0;
        diff > 0 ? row = diff : diff < 0 ? col = -diff : 0; //find the start field

        for (; row < rows && col < cols; ++row, ++col)
        {
            auto i = row * cols + col;
            if (i == f)continue;
            temp.push_back(i);
        }

        //------------------------------
        row = f / cols;
        col = f % cols;
        auto inv_col = cols - col - 1;
        diff = row - inv_col;
        row = 0, inv_col = 0;
        diff > 0 ? row = diff : diff < 0 ? inv_col = -diff : 0; //find the start field

        for (; row < rows && inv_col < cols; ++row, ++inv_col)
        {
            col = cols - inv_col - 1;
            auto i = row * cols + col;
            if (i == f)continue;
            temp.push_back(i);
        }

        cache[f] = std::move(temp);
    }
}

std::unordered_map<FieldPointer, std::vector<FieldPointer>> Queen::cache;