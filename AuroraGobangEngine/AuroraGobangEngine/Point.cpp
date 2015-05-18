#include "stdafx.h"
#include "Point.h"


Point::Point(int row, int column) : axis(row, column)
{
	Row = row;
	Column = column;
	left_oblique = row + column;
	right_oblique = (row > column) ? 14 + _abs(row - column) : 14 - _abs(row - column);
	weight = 1 - _max(_abs(7 - row), _abs(7 - column)) * 0.01;
}

inline double Point::get_value(Color &color)
{
	double result = 0;
	for (auto &c : value[color])
		result += c;
	return result;
}

inline void Point::set_value(Color &color, LineDirection ld, double val)
{
	value[color][ld] = val;
}