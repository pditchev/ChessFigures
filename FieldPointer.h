#pragma once


class FieldPointer
{
	size_t pos_X, pos_Y;

	size_t rows, cols;

public:

	FieldPointer();

	FieldPointer(size_t X, size_t Y);

	size_t getX() const;

	size_t getY() const;

	void setX(size_t X);

	void setY(size_t Y);



	FieldPointer& operator++();

	bool operator==(const FieldPointer& other);


};

