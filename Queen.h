#pragma once
#include "Figure.h"
#include <map>
#include <unordered_map>

struct Initializer;

class Queen : public Figure<Queen>
{
    static void fillCache(const Initializer& initializer);
    static std::unordered_map<FieldPointer, std::vector<FieldPointer>> cache;
    static const Piece type = Piece::Queen;
    friend Figure;
};