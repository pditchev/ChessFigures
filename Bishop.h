#pragma once
#include "Figure.h"

class Bishop : public Figure {
    virtual bool markImpactedFields(FieldPointer fieldPtr, Board* instance) override;
public:
    Bishop();
};

