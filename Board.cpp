#include "Board.h"

Board& Board::getInstanceImpl(std::pair<size_t, size_t>* dimensionsPtr)
{
	static Board instance{ dimensionsPtr };
	return instance;
}

Board::Board(std::pair<size_t, size_t>* dimensionsPtr) noexcept
	: _dimensions(dimensionsPtr ? std::move(*dimensionsPtr) : std::make_pair(size_t{ 0 }, size_t{ 0 }))
{
	fields.assign(_dimensions.first * _dimensions.second, {});
}

void Board::init(std::pair<size_t, size_t> dimensions)
{
	getInstanceImpl(&dimensions);
}

Board& Board::getInstance()
{
	return getInstanceImpl();
}

std::pair<size_t, size_t> Board::getDimensions()
{
	return _dimensions;
}

size_t Board::getRows()
{
	return _dimensions.first;
}

size_t Board::getCols()
{
	return _dimensions.second;
}

std::vector<Field>& Board::exposeFields()
{
	return fields;
}

FieldPointer Board::begin()
{
	return 0;
}

FieldPointer Board::end()
{
	return fields.size();
}
