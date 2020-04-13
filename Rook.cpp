#include "Rook.h"

bool Rook::markImpactedFields(FieldPointer fieldPtr, Board* instance) {

    for (size_t row = 0; row < instance->getRows(); row++)
    {
        if (row == fieldPtr.getX()) continue;
        if (!check(FieldPointer(row, fieldPtr.getY()), instance)) return false;
    }

    for (size_t col = 0; col < instance->getCols(); col++)
    {
        if (col == fieldPtr.getY()) continue;
        if (!check(FieldPointer(fieldPtr.getX(), col), instance)) return false;
    }
    return true;
}

Rook::Rook() : Figure("rook") {}
