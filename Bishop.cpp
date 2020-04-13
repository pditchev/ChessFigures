#include "Bishop.h"

bool Bishop::markImpactedFields(FieldPointer fieldPtr, Board* instance) {
    for (int row = fieldPtr.getX() + 1, col = fieldPtr.getY() + 1;
        row < instance->getRows() && col < instance->getCols();
        ++row, ++col) {
        if (!check(FieldPointer(row, col), instance)) return false;
    }

    for (int row = fieldPtr.getX() - 1, col = fieldPtr.getY() - 1;
        row >= 0 && col >= 0;
        --row, --col) {
        if (!check(FieldPointer(row, col), instance)) return false;
    }

    for (int row = fieldPtr.getX() + 1, col = fieldPtr.getY() - 1;
        row < instance->getRows() && col >= 0;
        ++row, --col) {
        if (!check(FieldPointer(row, col), instance)) return false;
    }

    for (int row = fieldPtr.getX() - 1, col = fieldPtr.getY() + 1;
        row >= 0 && col < instance->getCols();
        --row, ++col) {
        if (!check(FieldPointer(row, col), instance)) return false;
    }

    return true;
}

Bishop::Bishop() : Figure("bishop") {}
