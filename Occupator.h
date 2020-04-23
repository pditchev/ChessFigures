#pragma once
#include <memory>
#include <iostream>
#include "Figure.h"
//#include "FieldPointer.h"

struct Occupator
{
	//std::shared_ptr<Figure> figure;
	Piece type;
	FieldPointer fieldPtr;

	//Occupator(FieldPointer fieldPtr, std::shared_ptr<Figure> figure = nullptr)
	//	:  fieldPtr(fieldPtr), figure(figure) {}

	Occupator(FieldPointer fieldPtr, Piece type) : fieldPtr(fieldPtr), type(type) {}



	//bool operator<(const Occupator& other) const
	//{
	//	if (fieldPtr.getX() < other.fieldPtr.getX())
	//		return true;
	//	else if (fieldPtr.getX() == other.fieldPtr.getX())
	//		return fieldPtr.getY() < other.fieldPtr.getY();
	//	return false;
	//}

	bool operator<(const Occupator& other) const
	{
		return fieldPtr < other.fieldPtr;
	}




	//friend std::ostream& operator<<(std::ostream& out, const Occupator& occupator)
	//{

	//	out << "(" << occupator.fieldPtr.getX() << ", "
	//		<< occupator.fieldPtr.getY() << ") "
	//		<< occupator.figure->name;

	//	return out;
	//}
};

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {

	template<>
	struct hash<Occupator> {
		size_t operator()(const Occupator& occupator) const {
			size_t seed = 0;
			hash_combine(seed, occupator.type);
			//hash_combine(seed, occupator.fieldPtr.getX());//
			//hash_combine(seed, occupator.fieldPtr.getY());//
			hash_combine(seed, occupator.fieldPtr);

			return seed;
		}
	};
}