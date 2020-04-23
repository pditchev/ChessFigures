#pragma once
#include <vector>
#include <algorithm>

#include "Occupator.h"


class Solution : private std::vector<Occupator>
{
	size_t rows = Board::getInstance().getRows();
	size_t cols = Board::getInstance().getCols();

public:
	typedef std::vector<Occupator> Vector;

	using Vector::at;
	using Vector::push_back;
	using Vector::emplace_back;
	using Vector::pop_back;
	using Vector::begin;
	using Vector::end;
	using Vector::empty;
	using Vector::size;
	using Vector::operator[];

	bool operator==(const  Solution& other) const {

		if (this == &other) return true;
		if (this->size() != other.size()) return false;

		for (size_t i = 0; i < this->size(); i++)
		{
			if (this->at(i).type != other[i].type) return false;
			if (this->at(i).fieldPtr != other[i].fieldPtr) return false;
		}
		return true;
	}

	friend std::ostream& operator<<(std::ostream& out, const Solution& sol)
	{
		std::vector<char>b(sol.rows * sol.cols, '*');

		for (const auto& occ : sol)
		{
			switch (occ.type)
			{
			case Piece::Queen:
				b[occ.fieldPtr] = 'Q';
				break;
			case Piece::Rook:
				b[occ.fieldPtr] = 'R';
				break;
			case Piece::Bishop:
				b[occ.fieldPtr] = 'B';
				break;
			case Piece::Knight:
				b[occ.fieldPtr] = 'K';
				break;
			}
		}

		auto cntr = 0;
		for (auto& ch : b)
		{
			out << ch << ' ';
			if (!(++cntr % sol.cols))	out << '\n';
		}

		out << '\n' << '\n';
		return out;
	}
};



// template specialization of std::hash as needed for std::unordered_set<Solution> !!!
namespace std {
	template<>
	struct hash<Solution> {
		size_t operator()(const Solution& solution) const {
			size_t seed = 0;
			for (auto& s : solution) {
				hash_combine(seed, s);
			}
			return seed;
		}
	};
}