#include "Board.h"
#include "Field.h"

Board& Board::getInstanceImpl(std::pair<size_t, size_t>* dimensionsPtr)
{
	static Board instance{ dimensionsPtr };
	return instance;
}

Board::Board(std::pair<size_t, size_t>* dimensionsPtr)
	: _dimensions(dimensionsPtr ? std::move(*dimensionsPtr) : std::make_pair(size_t{ 0 }, size_t{ 0 }))
{
	if (nullptr == dimensionsPtr) {
		throw std::runtime_error{ "Board not initialized!!" };
	}

	impl_ = std::make_unique<BoardImpl>(_dimensions);
}

void Board::init(std::pair<size_t, size_t> dimensions)
{
	getInstanceImpl(&dimensions);
}

Board& Board::getInstance()
{
	return getInstanceImpl();
}

class Board::BoardImpl {

	size_t rows, cols;

	Field** fields;

public:
	BoardImpl(std::pair<size_t, size_t> dimensions)
		: rows(dimensions.first), cols(dimensions.second)
	{
		fields = createBoard(rows, cols);
	}


	Field** createBoard(size_t rows, size_t cols)
	{
		Field** result = nullptr;
		Field* pool = nullptr;

		try
		{
			result = new Field*[rows];		// can throw here
			pool = new Field[rows * cols]{};	// can throw here

			for (size_t i = 0; i < rows; ++i, pool +=cols)
			{
				result[i] = pool;
			}
			return result;
		}
		catch (const std::bad_alloc& ex)
		{
			delete[] result;		// either this is nullptr or it was allocated
			throw ex;
		}
		return nullptr;
	}

	~BoardImpl()
	{
		delete[] fields[0];
		delete[] fields;
	}

	Occupied isOccupied(FieldPointer f)
	{	 
		auto result = fields[f.getX()][f.getY()].status;
		return result;
	}

	std::pair<size_t, size_t> isAttacked(FieldPointer f)
	{
		auto result = std::make_pair(fields[f.getX()][f.getY()].blackAttacks
								   , fields[f.getX()][f.getY()].whiteAttacks);
		return result;			
	}

	void attack(FieldPointer f, PieceColor color)
	{
		color == PieceColor::black ? 
				++fields[f.getX()][f.getY()].blackAttacks
			  : ++fields[f.getX()][f.getY()].whiteAttacks;
	}

	void removeAttack(FieldPointer f, PieceColor color)
	{
		color == PieceColor::black ?
				--fields[f.getX()][f.getY()].blackAttacks
			  : --fields[f.getX()][f.getY()].whiteAttacks;
	}

	void occupy(FieldPointer f, PieceColor color)
	{
		color == PieceColor::black ?
				fields[f.getX()][f.getY()].status = Occupied::OccupiedByBlack
			  : fields[f.getX()][f.getY()].status = Occupied::OccupiedByWhite;
	}

	void deoccupy(FieldPointer f)
	{
		fields[f.getX()][f.getY()].status = Occupied::NotOccupied;
	}
};

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

Occupied Board::isOccupied(FieldPointer field)
{
	return impl_->isOccupied(field);
}

std::pair<size_t, size_t> Board::isAttacked(FieldPointer field)
{
	return impl_->isAttacked(field);
}

void Board::attack(FieldPointer field, PieceColor color)
{
	impl_->attack(field, color);
}

void Board::removeAttack(FieldPointer field, PieceColor color)
{
	impl_->removeAttack(field, color);
}

void Board::occupy(FieldPointer field, PieceColor color)
{
	impl_->occupy(field, color);
}

void Board::deoccupy(FieldPointer field)
{
	impl_->deoccupy(field);
}

FieldPointer Board::begin()
{
	return FieldPointer{ 0,0 };
}

FieldPointer Board::end()
{
	return FieldPointer{ _dimensions.first, 0 };
}