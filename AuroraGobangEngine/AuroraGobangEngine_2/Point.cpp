#include "stdafx.h"
#include "Point.h"

Point::Point(int row, int column) : Axis(row, column), PointColor(Color::Empty)
{
	this->Row = row;
	this->Column = column;
	this->LeftOblique = row + column;
	this->RightOblique = (row > column) ? 14 + _abs(row - column) : 14 - _abs(row - column);
}

double Point::GetValue(Color color)
{
	return std::accumulate(value[Black].cbegin(), value[Black].cend(), 0.0) + std::accumulate(value[White].cbegin(), value[White].cend(), 0.0);
}


void Point::ChangeValue(Color color, Direction ld, double val)
{
	assert(color != Empty);
	value[color][ld] += val;
}
void Point::ClearValue()
{
	std::fill(value[Black].begin(), value[Black].end(), 0);
	std::fill(value[White].begin(), value[White].end(), 0);
}

void Point::ChangeTwoValue(Direction ld, double value)
{
	ChangeValue(Black, ld, value);
	ChangeValue(White, ld, value);
}