#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <utility>
#include "Figure.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"


class FigureFactory {
    std::vector<std::stack<std::unique_ptr<FigureBase>, std::vector<std::unique_ptr<FigureBase>>>> piecesForThread;

public:
    static std::unique_ptr<FigureBase> produceFigure(Piece piece);

    FigureFactory(std::vector<std::stack<std::unique_ptr<FigureBase>, std::vector<std::unique_ptr<FigureBase>>>> piecesForThread);

    std::unique_ptr<FigureBase> getNextPiece();

    void returnPiece(std::unique_ptr<FigureBase> piece);

    bool dropPermutation();
};