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

double Point::get_value(Color color)
{
	double result1 = 0;
	double result2 = 0;
	for (auto &c : value[color])
		result1 += c;
	for (auto &c : value[!color])
		result2 += c;

	return result1 + result2;
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
		if (this->State == Empty)
		{
			value[color][ld] += val;
		}
	}
}
void Point::clear_value()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			value[i][j] = 0;
		}
	}
}

void Point::change_two_value(LineDirection ld, double value)
{
	change_value(Black, ld, value);
	change_value(White, ld, value);
}