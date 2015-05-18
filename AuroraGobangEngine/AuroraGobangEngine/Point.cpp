#include "stdafx.h"
#include "Point.h"

using std::array;


Point::Point(int row, int column) : axis(row, column)
{
	Row = row;
	Column = column;
	Left_oblique = row + column;
	Right_oblique = (row > column) ? 14 + _abs(row - column) : 14 - _abs(row - column);
	weight = 1 - _max(_abs(7 - row), _abs(7 - column)) * 0.01;
}

double Point::get_value(Color &color)
{
	double result = 0;
	for (auto &c : value[color])
		result += c;
	return result;
}


void Point::change_value(Color color, LineDirection ld, double val)
{
	if (color == Empty)
	{
		value[Black][ld] = 0;
		value[White][ld] = 0;
	}
	else
	{
		value[color][ld] = val;
	}
}
void Point::clear_value()
{
	for (auto &item : value)
		for (auto &val : item)
			val = 0;
}

void Point::change_two_value(LineDirection ld, double value)
{
	change_value(Black, ld, value);
	change_value(White, ld, value);
}