#pragma once
#include <vector>
#include <algorithm>

#include "Occupator.h"


class Solution : private std::vector<Occupator>
{
public:
	typedef std::vector<Occupator> Vector;

	using Vector::at;
	using Vector::push_back;
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
			if (this->at(i).figure->name != other[i].figure->name) return false;
			if (this->at(i).fieldPtr.getX() != other[i].fieldPtr.getX()) return false;
			if (this->at(i).fieldPtr.getY() != other[i].fieldPtr.getY()) return false;
		}
		return true;
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