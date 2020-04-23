#include "FigureFactory.h"

std::unique_ptr<FigureBase> FigureFactory::produceFigure(Piece piece) {

    switch (piece)
    {
    case Piece::Queen:
        return std::make_unique<Queen>();
        break;
    case Piece::Rook:
        return std::make_unique<Rook>();
        break;
    case Piece::Bishop:
        return std::make_unique<Bishop>();
        break;
    case Piece::Knight:
        return std::make_unique<Knight>();
        break;
    default:
        break;
    }
}

FigureFactory::FigureFactory(std::vector<std::stack<std::unique_ptr<FigureBase>
    , std::vector<std::unique_ptr<FigureBase>>>> piecesForThread)
    : piecesForThread(std::move(piecesForThread)) {}


std::unique_ptr<FigureBase> FigureFactory::getNextPiece() {
    if (piecesForThread.back().empty()) {
        return nullptr;
    }
    else {
        auto result = std::move(piecesForThread.back().top());  // moved!!
        piecesForThread.back().pop();
        return result;
    }
}

void FigureFactory::returnPiece(std::unique_ptr<FigureBase> piece) {
    if (piece)
        piecesForThread.back().push(std::move(piece));  // moved
}

bool FigureFactory::dropPermutation() {     // not used!

    piecesForThread.pop_back();

    if (piecesForThread.empty())
        return false;
    else
        return true;
}
