#include "WorkHorse.h"

WorkHorse::WorkHorse(std::vector<std::stack<std::unique_ptr<FigureBase>
    , std::vector<std::unique_ptr<FigureBase>>>> piecesForThread)
    : board(&Board::getInstance())
    , figFactory(new FigureFactory(std::move(piecesForThread)))
    , fields(board->exposeFields()) {}


WorkHorse::~WorkHorse()
{
    delete figFactory;
}

WorkHorse::SnapShotStruct::SnapShotStruct(SnapShotStruct&& other) noexcept
    : figure(std::move(other.figure)), fieldPtr(other.fieldPtr), stage(other.stage) {}

WorkHorse::SnapShotStruct& WorkHorse::SnapShotStruct::operator=(SnapShotStruct&& other) noexcept
{
    if (this == &other) return *this;
    stage = other.stage;
    fieldPtr = other.fieldPtr;
    figure = std::move(other.figure);
    return *this;
}

WorkHorse::SnapShotStruct::SnapShotStruct(std::unique_ptr<FigureBase> figure, FieldPointer passedField)
    : figure(std::move(figure)), fieldPtr(passedField) {}


void WorkHorse::startIter() {

    std::stack<SnapShotStruct, std::vector<SnapShotStruct>> snapshots;

    SnapShotStruct firstSnapShot(nullptr, board->begin());  // starts at [0][0] without figure

    snapshots.push(std::move(firstSnapShot));

    while (!snapshots.empty())
    {
        auto currentSnapShot = std::move(snapshots.top());
        snapshots.pop();

        if (nullptr == currentSnapShot.figure) currentSnapShot.figure = figFactory->getNextPiece();

        switch (currentSnapShot.stage) {
        case 0:
        {
            bool success = tryToPlace(currentSnapShot);
            if (true == success)
            {
                auto currentFieldPtr = currentSnapShot.fieldPtr;
                auto currentFigureType = currentSnapShot.figure->type;

                solution.emplace_back(currentFieldPtr, currentFigureType);

                currentSnapShot.stage = 1;
                snapshots.push(std::move(currentSnapShot));

                if (auto nextFigure = figFactory->getNextPiece())  // any pieces left??
                {
                    if (currentFigureType == nextFigure->type)     // if not same type, start from begin!
                    {
                        snapshots.emplace(std::move(nextFigure), ++currentFieldPtr);
                    }
                    else snapshots.emplace(std::move(nextFigure), board->begin());
                }
                else distinctSolutions.push_back(solution);
            }
            break;
        }
        case 1:

            solution.pop_back();    // rolling back!
            unboardFigure(currentSnapShot);

            ++currentSnapShot.fieldPtr; // and go to the next field!

            if (currentSnapShot.fieldPtr < board->end())
            {
                currentSnapShot.stage = 0;  // one more "recursive" loop
                snapshots.emplace(std::move(currentSnapShot));
                break;
            }

            figFactory->returnPiece(std::move(currentSnapShot.figure)); // this loop is dying
            break;         
        }
    }
}

bool WorkHorse::tryToPlace(WorkHorse::SnapShotStruct& currentSnapShot)
{
    for (auto fieldPtr = currentSnapShot.fieldPtr; ; ++fieldPtr)
    {
        if (fieldPtr == board->end()) {
            figFactory->returnPiece(std::move(currentSnapShot.figure));
            return false;
        }

        if(possiblePlacement(*currentSnapShot.figure, fieldPtr))
        {
            fields[fieldPtr].occupy();
            currentSnapShot.figure->increaseAttackedState(fieldPtr, fields);
            currentSnapShot.fieldPtr = fieldPtr;
            return true;
        }
    }
}

bool WorkHorse::possiblePlacement(const FigureBase& figure, FieldPointer where)
{
    if(     fields[where].isOccupied() == false
         && fields[where].isAttacked() == false
         && figure.check(where, fields) == true)
    {
        return true;
    }
    return false;
}

void WorkHorse::unboardFigure(SnapShotStruct& snapshotStruct)
{
    fields[snapshotStruct.fieldPtr].deoccupy();
    snapshotStruct.figure->decreaseAttackedState(snapshotStruct.fieldPtr, fields); 
}

std::vector<Solution> WorkHorse::getDistinctSolutions() {
    return distinctSolutions;
}