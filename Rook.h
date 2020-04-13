#pragma once
#include "Figure.h"

class Rook : public Figure
{
    virtual bool markImpactedFields(FieldPointer fieldPtr, Board* instance) override;

public:
    Rook();
};
