#pragma once

#include "stdafx.h"
#include <unordered_map>

using std::unordered_map;
using std::shared_ptr;

int Hasher(const Axis &axis);
int Equal(const Axis &left, const Axis &right);

class Board
{
	using BoardMap = unordered_map < Axis, shared_ptr<Point>, decltype(Hasher)*, decltype(Equal)* > ;
private:
	Color														turn;

	Color														mPieceColor;
	Color														oPieceColor;

	BoardMap													board;

	std::vector<shared_ptr<Line>>								rows;
	std::vector<shared_ptr<Line>>								columns;
	std::vector<shared_ptr<Line>>								lefts;
	std::vector<shared_ptr<Line>>								rights;

	std::vector<shared_ptr<Line>>								lines;
	shared_ptr<Boundary>										boundary;

	void initialize();

	void evaluate_points()
	{
		for (auto &point : board)
			point.second->clear_value();
		for (auto &pair : lines)
			pair->evaluate();
	}
public:
	Board(Color _mPieceColor)
		: boundary(std::make_shared<Boundary>())
		, turn(BLACK)
		, mPieceColor(_mPieceColor)
		, oPieceColor(!_mPieceColor)
		, board(15, Hasher, Equal)
	{
		initialize();
	}

	shared_ptr<Point> operator[](Axis axis)
	{
		return board[axis];
	}

	Color judge_win()
	{
		auto it = find_if(lines.begin(), lines.end(), [=](shared_ptr<Line> pair){return pair->check_win() != EMPTY; });
		return it == lines.end() ? EMPTY : (*it)->check_win();
	}

	void input_chess(Axis axis)
	{
		assert(board[axis]->color == EMPTY);
		board[axis]->color = turn;
		boundary->change_boundary(axis);
		evaluate_points();
		turn = !turn;
	}
	void undo_input_chess(Axis axis)
	{
		board[axis]->color = EMPTY;
		boundary->undo_change_boundary();
		evaluate_points();
		turn = !turn;
	}

	std::vector<shared_ptr<Point>>	empty_points()
	{
		std::vector<shared_ptr<Point>> va;
		for (int row = boundary->get_up(); row < boundary->get_down(); row++)
			for (int column = boundary->get_left(); column < boundary->get_right(); column++)
				if (board[Axis(row, column)]->color == EMPTY)
					va.push_back(board[Axis(row, column)]);
		return va;
	}

	Color get_turn()
	{
		return turn;
	}
};
