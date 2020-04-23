#pragma once
#include "Figure.h"
#include <map>
#include <unordered_map>

struct Initializer;

class Rook : public Figure<Rook>
{
    static void fillCache(const Initializer& initializer);
    static std::unordered_map<FieldPointer, std::vector<FieldPointer>> cache;
    static const Piece type = Piece::Rook;
    friend Figure;
};
