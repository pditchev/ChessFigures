#include "Figure.h"

bool Figure::check(FieldPointer fieldPtr, Board* instance)
{
  //  Field& field = instance->fields[position.first][position.second]; // for simplicity!!

 //   if (field.status == Occupied::NotOccupied)
    bool res = instance->isOccupied(fieldPtr) == Occupied::NotOccupied;
    if(res)
    {
        //field.attemptedAttack = true;

        impacted.push_back(fieldPtr);

        return true;
    }
    else
        impacted.clear();
    return false;
}

Figure::Figure(std::string name) : name(name) {
    //impacted.reserve(32);
}

bool Figure::increaseAttackedState(FieldPointer fieldPtr, Board* board) {

    if (markImpactedFields(fieldPtr, board)) {
        for (auto& field : impacted) {
 //           ++field->whiteAttacks;       // dealing only with white figures for now
            board->attack(field, PieceColor::white);
        }
        impacted.clear();
        return true;
    }
    return false;

    //bool success = markImpactedFields(position, board);

    ////for (auto& field : board) {
    //for (auto& field : impacted) {

    //    if (success/* && field->attemptedAttack*/) {
    //        ++field->whiteAttacks;       // dealing only with white figures for now
    //    }
    //    //field.attemptedAttack = false;
    //}
    //impacted.clear();
    //return success;
}

void Figure::decreaseAttackedState(FieldPointer fieldPtr, Board* board) {

    markImpactedFields(fieldPtr, board);

    for (auto& field : impacted) {
        //for (auto& field : board) {

         //   if (field.attemptedAttack) {
        //--field->whiteAttacks;       // dealing only with white figures for now
        board->removeAttack(field, PieceColor::white);
 //   }
 //   field.attemptedAttack = false;
    }
    impacted.clear();
}
