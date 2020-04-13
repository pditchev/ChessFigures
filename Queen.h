#pragma once
#include "Figure.h"

class Queen : public Figure {
    virtual bool markImpactedFields(FieldPointer fieldPtr, Board* instance) override;

public:
    Queen();
};