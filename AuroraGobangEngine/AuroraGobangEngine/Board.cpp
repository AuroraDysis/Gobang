#include "stdafx.h"

#include "Board.h"
#include <tuple>


Board::Board() : boundary(std::make_shared<Boundary>()), turn(Black)
{
	initialize();
}

Board::~Board() = default;

void Board::initialize()
{
	for (int i = 0; i < range; i++)
	{
		row[i] = std::make_shared<Line>(Row);
		column[i] = std::make_shared<Line>(Column);
	}
	for (int i = 0; i < range * 2 - 1; i++)
	{
		left_oblique[i] = std::make_shared<Line>(left_oblique);
		right_oblique[i] = std::make_shared<Line>(right_oblique);
	}
	for (int _row = 0; _row < range; _row++)
	{
		for (int _column = 0; _column < range; _column++)
		{
			auto point = std::make_shared<Point>(_row, _column);
			board[Axis(_row, _column)] = point;
			row[_row]->add_point(point);
			column[_column]->add_point(point);
		}
	}
	//左上到右下，每一行左下到右上
	for (int oblique = 0; oblique < range; oblique++)
		for (int row = oblique, column = 0; row >= 0; --row, ++column)
			left_oblique[oblique]->add_point(board[Axis(row, column)]);
	for (int oblique = range; oblique < range * 2 - 1; oblique++)
		for (int row = range - 1, column = oblique - range + 1; column < range; --row, ++column)
			left_oblique[oblique]->add_point(board[Axis(row, column)]);
	//右上到左下，每一行左上到右下
	for (int oblique = 0; oblique < range; oblique++)
		for (int row = 0, column = 14 - oblique; column < range; ++row, ++column)
			right_oblique[oblique]->add_point(board[Axis(row, column)]);
	for (int oblique = range; oblique < range * 2 - 1; oblique++)
		for (int row = oblique - range + 1, column = 0; row < range; ++row, ++column)
			right_oblique[oblique]->add_point(board[Axis(row, column)]);

	for (auto pair : row)
		total_line.push_back(pair.second);
	for (auto pair : column)
		total_line.push_back(pair.second);
	for (auto pair : left_oblique)
		total_line.push_back(pair.second);
	for (auto pair : right_oblique)
		total_line.push_back(pair.second);
}

std::vector<shared_ptr<Point>> Board::empty_points()
{
	std::vector<shared_ptr<Point>> va;
	for (int row = boundary->get_range(Up); row < boundary->get_range(Down); row++)
		for (int column = boundary->get_range(Left); column < boundary->get_range(Right); column++)
			if (board[Axis(row, column)]->State != Empty)
				va.push_back(board[Axis(row, column)]);
	return va;
}

void Board::input(Axis axis)
{
	if (board[axis]->State == Empty)
		board[axis]->State = turn;
	else
		throw std::exception("下到了已有棋子的位置上");
	boundary->change_boundary(axis);
	evaluate_points();
	turn = !turn;
}

void Board::undo_input(Axis axis)
{
	board[axis]->State = Empty;
	boundary->undo_change_boundary();
	evaluate_points();
	turn = !turn;
}

Color Board::judge_win()
{
	for (auto pair : total_line)
		if (pair->check_win() != Empty) return pair->check_win();
	return Empty;
}

void Board::evaluate_points()
{
	for (auto pair : total_line)
		pair->evaluate();
}