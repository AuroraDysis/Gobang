#pragma once
#include "stdafx.h"

class Axis
{
public:
	Axis(int _row,int _column);
	~Axis() = default;
	int row;
	int column;
	operator int();
};

inline Axis::Axis(int _row, int _column)
{
	assert(_row < range && _row >= 0 && _column < range && _column >= 0);
	this->row = _row;
	this->column = _column;
}

inline Axis::operator int()
{
	return row * 100 + column;
}