#include "FieldPointer.h"
#include "Board.h"


FieldPointer::FieldPointer()
	: pos_X(0)
	, pos_Y(0)
	, rows(Board::getInstance().getDimensions().first)
	, cols(Board::getInstance().getDimensions().second)
{}

FieldPointer::FieldPointer(size_t X, size_t Y)
	: pos_X(X)
	, pos_Y(Y)
	, rows(Board::getInstance().getDimensions().first)
	, cols(Board::getInstance().getDimensions().second)
{}

FieldPointer::FieldPointer(size_t X, size_t Y, size_t rows, size_t cols)
	: pos_X(X)
	, pos_Y(Y)
	, rows(rows)
	, cols(cols)
{}

size_t FieldPointer::getX() const
{
	return pos_X;
}

size_t FieldPointer::getY() const
{
	return pos_Y;
}

void FieldPointer::setX(size_t X)
{
	pos_X = X;
}

void FieldPointer::setY(size_t Y)
{
	pos_Y = Y;
}

FieldPointer& FieldPointer::operator++()
{
	if ( !(++pos_Y %= cols)) ++pos_X;
	return *this;
}

bool FieldPointer::operator==(const FieldPointer& other)
{
	return this->pos_X == other.pos_X && this->pos_Y==other.pos_Y;
}
