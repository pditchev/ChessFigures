#pragma once
#include <vector>
#include <string>
#include <stack>
#include <memory>
#include "Field.h"
#include "Board.h"

struct Initializer;

enum class Piece { Queen, Rook, Bishop, Knight };

class FigureBase {
public:
    FigureBase(Piece type) : type(type) {}
    Piece type;

    virtual bool check(const FieldPointer fieldPtr, const std::vector<Field>& fields) const = 0;
    virtual void increaseAttackedState(const FieldPointer fieldPtr, std::vector<Field>& fields) const = 0;
    virtual void decreaseAttackedState(const FieldPointer fieldPtr, std::vector<Field>& fields) const = 0;
    virtual void initCache(const Initializer& i) const = 0;

    virtual ~FigureBase(){}
};

template <typename T>       // CRTP
class Figure : public FigureBase
{

public:
    virtual bool check(const FieldPointer fieldPtr, const std::vector<Field>& fields) const override
    {
        for (const auto& f : T::cache[fieldPtr])
        {
            if (fields[f].isOccupied() == true) { return false; }
        }
        return true;
    }

    virtual void increaseAttackedState(const FieldPointer fieldPtr, std::vector<Field>& fields) const override
    {
        for (const auto& f : T::cache[fieldPtr])
        {
            fields[f].attack();
        }
    }

    Figure() : FigureBase(T::type){}

    virtual void decreaseAttackedState(const FieldPointer fieldPtr, std::vector<Field>& fields) const override
    {
        for (const auto& f : T::cache[fieldPtr])
        {
            fields[f].removeAttack();
        }
    }

    virtual void initCache(const Initializer& i) const override
    {
        T::fillCache(i);
    }
};