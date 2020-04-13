#include "Queen.h"

bool Queen::markImpactedFields(FieldPointer fieldPtr, Board* instance) {

    auto rows = instance->getRows();
    auto cols = instance->getCols();

    for (size_t row = 0; row < rows; row++)
    {
        if (row == fieldPtr.getX()) continue;
        if (!check(FieldPointer(row, fieldPtr.getY()), instance)) return false;
    }

    for (size_t col = 0; col < cols; col++)
    {
        if (col == fieldPtr.getY()) continue;
        if (!check(FieldPointer(fieldPtr.getX(), col), instance)) return false;
    }

    for (int row = fieldPtr.getX() + 1, col = fieldPtr.getY() + 1;
        row < rows && col < cols;
        ++row, ++col) {
        if (!check(FieldPointer(row, col), instance)) return false;
    }

    for (int row = fieldPtr.getX() - 1, col = fieldPtr.getY() - 1;
        row >= 0 && col >= 0;
        --row, --col) {
        if (!check(FieldPointer(row, col), instance)) return false;
    }

    for (int row = fieldPtr.getX() + 1, col = fieldPtr.getY() - 1;
        row < rows && col >= 0;
        ++row, --col) {
        if (!check(FieldPointer(row, col), instance)) return false;
    }

    for (int row = fieldPtr.getX() - 1, col = fieldPtr.getY() + 1;
        row >= 0 && col < cols;
        --row, ++col) {
        if (!check(FieldPointer(row, col), instance)) return false;
    }

    return true;
}

Queen::Queen() : Figure("queen") {}