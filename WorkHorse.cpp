#include "WorkHorse.h"

void WorkHorse::cleanFigure(const SnapShotStruct snapshotStruct)
{
    snapshotStruct.figure->decreaseAttackedState(snapshotStruct.fieldPtr, board);  // ????
    board->deoccupy(snapshotStruct.fieldPtr);
}


WorkHorse::WorkHorse(std::vector<std::stack<std::shared_ptr<Figure>>> piecesForThread)
    : board(&Board::getInstance()), figFactory(new FigureFactory(piecesForThread)) {}

WorkHorse::~WorkHorse()
{
    delete figFactory;
}

WorkHorse::SnapShotStruct::SnapShotStruct(std::shared_ptr<Figure> figure, FieldPointer passedField)
    : figure(figure), fieldPtr(passedField) {}

void WorkHorse::startIter() {

    std::stack<SnapShotStruct> snapshots;

    SnapShotStruct firstSnapShot(nullptr, board->begin());  // starts at [0][0] without figure

    snapshots.push(firstSnapShot);

    while (!snapshots.empty())
    {
        auto currentSnapShot = snapshots.top();
        snapshots.pop();

        if (nullptr == currentSnapShot.figure) currentSnapShot.figure = figFactory->getNextPiece();

        switch (currentSnapShot.stage) {
        case 0:
            if (walkingOnTheBoard(currentSnapShot)) {

                currentSnapShot.stage = 1;
                snapshots.push(currentSnapShot);

                solution.push_back(Occupator(currentSnapShot.fieldPtr, currentSnapShot.figure));

                if (auto nextFigure = figFactory->getNextPiece(); !nextFigure) {
                    distinctSolutions.push_back(solution);
                }
                else if (typeid(*currentSnapShot.figure) == typeid(*nextFigure)) {
                    snapshots.push(SnapShotStruct(nextFigure, ++currentSnapShot.fieldPtr));
                }
                else snapshots.push(SnapShotStruct(nextFigure, board->begin()));
            }
            break;

        case 1:

            solution.pop_back();    // rolling back!

            cleanFigure(currentSnapShot);

            if (++currentSnapShot.fieldPtr == board->end())
            {
                figFactory->returnPiece(currentSnapShot.figure);
                break;    // go to the end of the for loop after recuring from "recursion"
            }
            currentSnapShot.stage = 0;
            snapshots.push(currentSnapShot);

            break;
        }
    }
}

bool WorkHorse::walkingOnTheBoard(WorkHorse::SnapShotStruct& currentSnapShot)
{
    for (auto fieldPtr = currentSnapShot.fieldPtr; ; ++fieldPtr) {

        if (fieldPtr == board->end()) {
            figFactory->returnPiece(currentSnapShot.figure);
            return false;
        }

        if(board->isOccupied(fieldPtr) == Occupied::NotOccupied
            && !board->isAttacked(fieldPtr).first   // by blacks
            && !board->isAttacked(fieldPtr).second  // by whites
            && currentSnapShot.figure->increaseAttackedState(fieldPtr, board))
        {
            board->occupy(fieldPtr, PieceColor::white);     // for now only whites
            currentSnapShot.fieldPtr = fieldPtr;
            return true;
        }
    }
}

std::vector<Solution> WorkHorse::getDistinctSolutions() {
    return distinctSolutions;
}