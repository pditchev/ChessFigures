#pragma once
//typedef char uint8_t;

enum class Occupied : uint8_t { NotOccupied, OccupiedByWhite, OccupiedByBlack };

struct Field {

    uint8_t whiteAttacks;
    uint8_t blackAttacks;
    Occupied status;

    Field() : whiteAttacks(0)
        , blackAttacks(0)
        , status(Occupied::NotOccupied)
    {}
};