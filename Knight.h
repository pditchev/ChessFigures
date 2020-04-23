#pragma once
#include "Figure.h"
//#include <map>
#include <unordered_map>

struct Initializer;

class Knight : public Figure<Knight> {

    static constexpr std::pair<int, int> att[]{
        {-2, 1 },
        {-1, 2 },
        { 1, 2 },
        { 2, 1},
        {2, -1},
        {1, -2},
        {-1, -2},
        {-2, -1}
    };

    static void fillCache(const Initializer& initializer);
    static std::unordered_map<FieldPointer, std::vector<FieldPointer>> cache;
    static const Piece type = Piece::Knight;
    friend Figure;
};

