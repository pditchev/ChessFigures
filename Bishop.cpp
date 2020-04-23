#include "Bishop.h"
#include "Initializer.h"

void Bishop::fillCache(const Initializer& initializer)
{
    FieldPointer rows = initializer.boardDimensions.first;
    FieldPointer cols = initializer.boardDimensions.second;
    FieldPointer total_f = rows * cols;

    for (FieldPointer f = 0; f < total_f; ++f)
    {
        std::vector<FieldPointer> temp;

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





        //FieldPointer start = f;
        //while (start > cols && start % cols != 0) start -= (cols + 1);

        //for (FieldPointer i = start; i < total_f && i % cols != (cols - 1); i += (cols + 1))
        //{
        //    if (i == f) continue;
        //    temp.push_back(i);
        //}

        //start = f;
        //while (start < (total_f - cols) && start % cols != 0) start += (cols - 1);

        //for (FieldPointer i = start; i > (cols - 1) && i % cols != (cols - 1); i -= (cols - 1))
        //{
        //    if (i == f) continue;
        //    temp.push_back(i);
        //}

        cache[f] = std::move(temp);
    }
}

std::unordered_map<FieldPointer, std::vector<FieldPointer>> Bishop::cache;