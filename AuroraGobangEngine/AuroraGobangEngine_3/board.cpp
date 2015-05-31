#include "stdafx.h"
#include "board.h"

int Hasher(const Axis &axis)
{
	return std::hash<int>()(axis.axis);
}

int Equal(const Axis &left, const Axis &right)
{
	return left.axis == right.axis;
}

void Board::initialize()
{
	for (int _row = 0; _row < RANGE; _row++)
	{
		for (int _column = 0; _column < RANGE; _column++)
		{
			auto point = std::make_shared<Point>(_row, _column);
			board[Axis(_row, _column)] = point;
			rows[_row]->add_point(point);
			columns[_column]->add_point(point);
		}
	}
	//左上到右下，每一行左下到右上
	for (int oblique = 0; oblique < RANGE; oblique++)
		for (int row = oblique, column = 0; row >= 0; --row, ++column)
			lefts[oblique]->add_point(board[Axis(row, column)]);
	for (int oblique = RANGE; oblique < RANGE * 2 - 1; oblique++)
		for (int row = RANGE - 1, column = oblique - RANGE + 1; column < RANGE; --row, ++column)
			lefts[oblique]->add_point(board[Axis(row, column)]);

	//右上到左下，每一行左上到右下
	for (int oblique = 0; oblique < RANGE; oblique++)
		for (int row = 0, column = 14 - oblique; column < RANGE; ++row, ++column)
			rights[oblique]->add_point(board[Axis(row, column)]);
	for (int oblique = RANGE; oblique < RANGE * 2 - 1; oblique++)
		for (int row = oblique - RANGE + 1, column = 0; row < RANGE; ++row, ++column)
			rights[oblique]->add_point(board[Axis(row, column)]);

	using std::copy;
	auto bi = std::back_inserter(lines);
	copy(rows.begin(), rows.end(), bi);
	copy(columns.begin(), columns.end(), bi);
	copy(lefts.begin(), lefts.end(), bi);
	copy(rights.begin(), rights.end(), bi);
}