#include "WorkHorse.h"

//bool WorkHorse::setFigure(const Occupator& occupator) {  // place a figure on the board
//
//    std::pair<int, int> fromPosition = std::make_pair(occupator.field.row, occupator.field.col);
//
//    if (occupator.figure->increaseAttackedState(fromPosition, board)) { // if successfully 
//                                                                        // implemented attack logic
//        board->at(occupator.field).status = Occupied::OccupiedByWhite;  // for now working only with white figures!!
//                                          // to do: implement a switch for different game variants!
//        return true;
//    }
//    return false;
//}

void WorkHorse::cleanFigure(const SnapShotStruct snapshotStruct) {
    //std::pair<int, int> fromPosition = std::make_pair(occupator.field.row, occupator.field.col);

    snapshotStruct.figure->decreaseAttackedState(snapshotStruct.fieldPtr, board);  // ????
    board->deoccupy(snapshotStruct.fieldPtr);

    //board->at(occupator.field).status = Occupied::NotOccupied;
}


WorkHorse::WorkHorse(std::vector<std::stack<std::shared_ptr<Figure>>> piecesForThread)
    : board(&Board::getInstance()), figFactory(new FigureFactory(piecesForThread)) {}

WorkHorse::~WorkHorse()
{
    delete figFactory;
}

//void WorkHorse::start() {
//    if (auto figure = figFactory->getNextPiece())
//        place(figure, FieldPtr(board)); //start with fields[0][0] (default c'tor of iterator)
//}

//void WorkHorse::place(std::shared_ptr<Figure> figure, FieldPtr passedField) {
//
//    static int level = 0;
//    ++level;
//
//    for (auto field = passedField; field != board->end(); ++field) {
//
//        Occupator occupator{ figure, field };
//
//        if (field->status == Occupied::NotOccupied
//            && field->whiteAttacks == 0     // change logic
//            && field->blackAttacks == 0     // for different variants!!!
//            && setFigure(occupator)) {
//
//            solution.push_back(occupator);
//
//            auto nextFigure = figFactory->getNextPiece();
//
//            if (!nextFigure) {
//                distinctSolutions.push_back(solution);
//            }
//
//            else place(nextFigure, field);   // recursion !!
//
//            solution.pop_back();    // rolling back!
//
//            cleanFigure(occupator);
//
//            figFactory->returnPiece(nextFigure);
//        }
//    }
//
//    --level;
//    if (level == 0 && figFactory->dropPermutation())  start();
//
//}



WorkHorse::SnapShotStruct::SnapShotStruct(std::shared_ptr<Figure> figure, FieldPointer passedField)
    : figure(figure), fieldPtr(passedField) {}

//WorkHorse::SnapShotStruct::SnapShotStruct(const SnapShotStruct& other)
//    : figure(other.figure), fieldPtr(other.fieldPtr)
//{
//    stage = other.stage;
//    fieldPtr.board = other.fieldPtr.board;
//    fieldPtr.row = other.fieldPtr.row;
//    fieldPtr.col = other.fieldPtr.col;
//}
//
//WorkHorse::SnapShotStruct& WorkHorse::SnapShotStruct::operator=(const SnapShotStruct& other)
//{
//    if (this != &other) {
//        stage = other.stage;
//        figure = other.figure;
//        fieldPtr.board = other.fieldPtr.board;
//        fieldPtr.col = other.fieldPtr.col;
//        fieldPtr.row = other.fieldPtr.row;
//    }
//    return *this;
//}


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

            //    board->at(currentSnapShot.fieldPtr).status = Occupied::OccupiedByWhite; // !!!!!!???  central board???
                currentSnapShot.stage = 1;
                snapshots.push(currentSnapShot);

                solution.push_back(Occupator(currentSnapShot.fieldPtr, currentSnapShot.figure));

                if (auto nextFigure = figFactory->getNextPiece(); !nextFigure) {
                    distinctSolutions.push_back(solution);
                }
                else if (typeid(*currentSnapShot.figure) == typeid(*nextFigure)) {
                   // auto tempFieldPtr = currentSnapShot.fieldPtr;
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

        //if (snapshots.empty() && figFactory->dropPermutation())
        //    snapshots.push(SnapShotStruct(nullptr, board));
    }
}

bool WorkHorse::walkingOnTheBoard(WorkHorse::SnapShotStruct& currentSnapShot)
{
    for (auto fieldPtr = currentSnapShot.fieldPtr; ; ++fieldPtr) {

        if (fieldPtr == board->end()) {
            figFactory->returnPiece(currentSnapShot.figure);
            return false;
        }

 //       if (fieldPtr->status == Occupied::NotOccupied
        if(board->isOccupied(fieldPtr) == Occupied::NotOccupied
 //           && fieldPtr->whiteAttacks == 0     // change logic
            && !board->isAttacked(fieldPtr).first   // by blacks
 //           && fieldPtr->blackAttacks == 0     // for different variants!!!
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

