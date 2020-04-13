#pragma once
#include <vector>
#include <string>
#include <stack>
#include <memory>
#include "Field.h"
#include "Board.h"

class Figure
{
private:

    std::vector<FieldPointer> impacted;

    virtual bool markImpactedFields(FieldPointer fieldPtr, Board* instance) = 0;

protected:

    bool check(FieldPointer fieldPtr, Board* instance);

public:

    Figure(std::string name);

    std::string name;

 //   bool increaseAttackedState(std::pair<int, int> position, Board* board);
    bool increaseAttackedState(FieldPointer fieldPtr, Board* board);

    void decreaseAttackedState(FieldPointer fieldPtr, Board* board);
};