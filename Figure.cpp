#include "Figure.h"

bool Figure::check(FieldPointer fieldPtr, Board* instance)
{
    if(instance->isOccupied(fieldPtr) == Occupied::NotOccupied)
    {
        impacted.push_back(fieldPtr);
        return true;
    }
    else
        impacted.clear();
    return false;
}

Figure::Figure(std::string name) : name(name) {}

Figure::~Figure(){}

bool Figure::increaseAttackedState(FieldPointer fieldPtr, Board* board) {

    if (markImpactedFields(fieldPtr, board)) {
        for (auto& field : impacted)
        {
            board->attack(field, PieceColor::white);   // dealing only with white figures for now
        }
        impacted.clear();
        return true;
    }
    return false;
}

void Figure::decreaseAttackedState(FieldPointer fieldPtr, Board* board) {

    markImpactedFields(fieldPtr, board);

    for (auto& field : impacted)
    {      
        board->removeAttack(field, PieceColor::white);  // dealing only with white figures for now
    }
    impacted.clear();
}