#include "stdafx.h"

#include "Board.h"
#include <tuple>


Board::Board()
{
	initialize();
}

void Board::initialize()
{
	for (int i = 0; i < range; i++)
	{
		row[i] = Line(Row);
		column[i] = Line(Column);
	}
	for (int i = 0; i < range * 2 - 1; i++)
	{
		leftOblique[i] = Line(LeftOblique);
		rightOblique[i] = Line(RightOblique);
	}
	for (int _row = 0; _row < range; _row++)
	{
		for (int _column = 0; _column < range; _column++)
		{
			Point point(_row, _column);
			//std::make_tuple(_row, _column)
			board[Axis(_row, _column)] = point;
			row[_row].add_point(point);
			column[_column].add_point(point);
		}
	}
	//左上到右下，每一行左下到右上
	for (int oblique = 0; oblique < range; oblique++)
		for (int row = oblique, column = 0; row >= 0; --row, ++column)
			leftOblique[oblique].add_point(board[Axis(row, column)]);
	for (int oblique = range; oblique < range * 2 - 1; oblique++)
		for (int row = range - 1, column = oblique - range + 1; column < range; --row, ++column)
			leftOblique[oblique].add_point(board[Axis(row, column)]);
	//右上到左下，每一行左上到右下
	for (int oblique = 0; oblique < range; oblique++)
		for (int row = 0, column = 14 - oblique; column < range; ++row, ++column)
			rightOblique[oblique].add_point(board[Axis(row, column)]);
	for (int oblique = range; oblique < range * 2 - 1; oblique++)
		for (int row = oblique - range + 1, column = 0; row < range; ++row, ++column)
			rightOblique[oblique].add_point(board[Axis(row, column)]);
}

std::vector<Axis> Board::empty_points()
{
	std::vector<Axis> va;
	for (int row = boundary.get_range(Up); row < boundary.get_range(Down); row++)
		for (int column = boundary.get_range(Left); column < boundary.get_range(Right); column++)
			if (board[Axis(row, column)].State != Empty)
				va.push_back(board[Axis(row, column)].axis);
	return va;
}

void Board::input(Axis axis)
{
	if (board[axis].State == Empty)
		board[axis].State = turn;
	else
		throw std::exception("下到了已有棋子的位置上");
	boundary.change_boundary(axis);
	evaluate_points();
	turn = !turn;
}

void Board::undo_input(Axis axis)
{
	board[axis].State = Empty;
	boundary.undo_change_boundary();
	evaluate_points();
	turn = !turn;
}

Color Board::judge_win()
{
	for (auto pair : row)
		if (pair.second.check_win() != Empty) return pair.second.check_win();
	for (auto pair : column)
		if (pair.second.check_win() != Empty) return pair.second.check_win();
	for (auto pair : leftOblique)
		if (pair.second.check_win() != Empty) return pair.second.check_win();
	for (auto pair : rightOblique)
		if (pair.second.check_win() != Empty) return pair.second.check_win();
	return Empty;
}

void Board::evaluate_points()
{
	for (auto pair : row)
		pair.second.evaluate();
	for (auto pair : column)
		pair.second.evaluate();
	for (auto pair : leftOblique)
		pair.second.evaluate();
	for (auto pair : rightOblique)
		pair.second.evaluate();
}