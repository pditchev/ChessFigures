#include "Knight.h"

bool Knight::markImpactedFields(FieldPointer fieldPtr, Board* instance) {

    for (auto f : att) {
        int row = fieldPtr.getX() + f.first;
        int col = fieldPtr.getY() + f.second;
        if (row >= 0 && row < instance->getRows() && col >= 0 && col < instance->getCols()) {
            if (!check(FieldPointer(row, col), instance)) return false;
        }
    }
    return true;
}

Knight::Knight() : Figure("knight") {}
