#pragma once
#include <utility>
#include <stdexcept>
#include <memory>
#include "FieldPointer.h"
#include "Field.h"


enum class PieceColor {black, white};


class Board		// Meyers' Singleton with parameters
{
	std::pair<size_t, size_t> _dimensions;

	static Board& getInstanceImpl(std::pair<size_t, size_t>* dimensionsPtr = nullptr); // the magic is here

	Board(std::pair<size_t, size_t>* dimensionsPtr);	// !! private c'tor !!!

	class BoardImpl;		// pImpl idiom
	std::unique_ptr<BoardImpl> impl_;


public:
	static void init(std::pair<size_t, size_t> dimensions);

	static Board& getInstance();

	Board(const Board&) = delete;
	void operator=(const Board&) = delete;

	std::pair<size_t, size_t> getDimensions();

	size_t getRows();

	size_t getCols();


	Occupied isOccupied(FieldPointer f);

	std::pair<size_t, size_t> isAttacked(FieldPointer);	// .first -> by blacks; .second -> by whites

	void attack(FieldPointer field, PieceColor color);

	void removeAttack(FieldPointer field, PieceColor color);

	void occupy(FieldPointer field, PieceColor color);

	void deoccupy(FieldPointer field);

	FieldPointer begin();

	FieldPointer end();
};