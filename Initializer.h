#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "FigureFactory.h"

#define MAX_ROWS 8
#define MAX_COLS 8
#define MAX_FIGURES 8

struct Initializer
{

    std::vector<std::pair<Piece, int>> init{ {Piece::Queen,  0},
                                             {Piece::Rook,   0},
                                             {Piece::Bishop, 0},
                                             {Piece::Knight, 0}
    };
    std::pair<int, int> boardDimensions;

    std::vector<Piece> initial;
    std::vector<std::stack<std::shared_ptr<Figure>>> piecesRepo;



    void getInput();

    void start();

    void makeInitial(std::vector<std::pair<Piece, int>>& pieces);

    void permute(int index);

    void noPermute();


};

