#include "stdafx.h"
#include "Board.h"
#include <tuple>
#include <algorithm>
#include <iostream>
#include <iomanip>

using std::find_if;


Board::Board(Color _mPieceColor) : boundary(std::make_shared<Boundary>()), turn(Black), mPieceColor(_mPieceColor), oPieceColor(!_mPieceColor)
{
	initialize();
}

Board::~Board() = default;

void Board::initialize()
{
	for (int i = 0; i < range; i++)
	{
		all_row[i] = std::make_shared<Line>(Row);
		all_column[i] = std::make_shared<Line>(Column);
	}
	for (int i = 0; i < range * 2 - 1; i++)
	{
		all_left_oblique[i] = std::make_shared<Line>(Left_oblique);
		all_right_oblique[i] = std::make_shared<Line>(Right_oblique);
	}
	for (int _row = 0; _row < range; _row++)
	{
		for (int _column = 0; _column < range; _column++)
		{
			auto point = std::make_shared<Point>(_row, _column);
			board[Axis(_row, _column)] = point;
			all_row[_row]->add_point(board[Axis(_row, _column)]);
			all_column[_column]->add_point(board[Axis(_row, _column)]);
		}
	}
	//左上到右下，每一行左下到右上
	for (int oblique = 0; oblique < range; oblique++)
		for (int row = oblique, column = 0; row >= 0; --row, ++column)
			all_left_oblique[oblique]->add_point(board[Axis(row, column)]);
	for (int oblique = range; oblique < range * 2 - 1; oblique++)
		for (int row = range - 1, column = oblique - range + 1; column < range; --row, ++column)
			all_left_oblique[oblique]->add_point(board[Axis(row, column)]);
	//右上到左下，每一行左上到右下
	for (int oblique = 0; oblique < range; oblique++)
		for (int row = 0, column = 14 - oblique; column < range; ++row, ++column)
			all_right_oblique[oblique]->add_point(board[Axis(row, column)]);
	for (int oblique = range; oblique < range * 2 - 1; oblique++)
		for (int row = oblique - range + 1, column = 0; row < range; ++row, ++column)
			all_right_oblique[oblique]->add_point(board[Axis(row, column)]);

	for (auto &pair : all_row)
		total_line.push_back(pair.second);
	for (auto &pair : all_column)
		total_line.push_back(pair.second);
	for (auto &pair : all_left_oblique)
		total_line.push_back(pair.second);
	for (auto &pair : all_right_oblique)
		total_line.push_back(pair.second);
}

std::vector<shared_ptr<Point>> Board::empty_points()
{
	std::vector<shared_ptr<Point>> va;
	for (int row = boundary->get_range(Up); row < boundary->get_range(Down); row++)
		for (int column = boundary->get_range(Left); column < boundary->get_range(Right); column++)
			if (board[Axis(row, column)]->State == Empty)
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
	auto it = find_if(total_line.begin(), total_line.end(), [=](shared_ptr<Line> pair){return pair->check_win() != Empty; });
	return it == total_line.end() ? Empty : (*it)->check_win();
}

void Board::evaluate_points()
{
	for (auto &point : board)
		point.second->clear_value();
	for (auto &pair : total_line)
		pair->evaluate();
	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < range; j++)
		{
			std::cout << std::setw(4) << board[Axis(i, j)]->get_value(turn) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

shared_ptr<Point> Board::operator[](Axis axis)
{
	return board[axis];
}
