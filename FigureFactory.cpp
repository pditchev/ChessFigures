#include "FigureFactory.h"

std::shared_ptr<Figure> FigureFactory::produceFigure(Piece piece) {

    switch (piece)
    {
    case Piece::Queen:
        return std::make_shared<Queen>();
        break;
    case Piece::Rook:
        return std::make_shared<Rook>();
        break;
    case Piece::Bishop:
        return std::make_shared<Bishop>();
        break;
    case Piece::Knight:
        return std::make_shared<Knight>();
        break;
    default:
        break;
    }
}

FigureFactory::FigureFactory(std::vector<std::stack<std::shared_ptr<Figure>>> piecesForThread)
    : piecesForThread(piecesForThread) {}


std::shared_ptr<Figure> FigureFactory::getNextPiece() {
    if (piecesForThread.back().empty()) {
        return nullptr;
    }
    else {
        auto result = piecesForThread.back().top();
        piecesForThread.back().pop();
        return result;
    }
}

void FigureFactory::returnPiece(std::shared_ptr<Figure> piece) {
    if (piece)
        piecesForThread.back().push(piece);
}

bool FigureFactory::dropPermutation() {     // not used!

    piecesForThread.pop_back();

    if (piecesForThread.empty())
        return false;
    else
        return true;
}
