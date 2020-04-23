#pragma once
#include "Field.h"
#include <vector>

typedef int FieldPointer;

class Board {

	std::vector<Field> fields;

	std::pair<size_t, size_t> _dimensions;

	static Board& getInstanceImpl(std::pair<size_t, size_t>* dimensionsPtr = nullptr); // the magic is here

	Board(std::pair<size_t, size_t>* dimensionsPtr) noexcept;	// !! private c'tor !!!

public:

	static void init(std::pair<size_t, size_t> dimensions);

	static Board& getInstance();

	Board(const Board&) = delete;
	void operator=(const Board&) = delete;

	std::pair<size_t, size_t> getDimensions();

	size_t getRows();

	size_t getCols();

	std::vector<Field>& exposeFields();

	FieldPointer begin();
	FieldPointer end();
};