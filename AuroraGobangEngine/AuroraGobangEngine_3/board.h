#pragma once

#include "stdafx.h"
#include <unordered_map>

using std::unordered_map;
using std::shared_ptr;
using std::vector;

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

	vector<shared_ptr<Line>>									rows;
	vector<shared_ptr<Line>>									columns;
	vector<shared_ptr<Line>>									lefts;
	vector<shared_ptr<Line>>									rights;

	vector<shared_ptr<Line>>									lines;
	shared_ptr<Boundary>										boundary;

	void initialize();

	void evaluate_points()
	{
		for (auto &point : board)
			point.second->ClearValue();
		for (auto &pair : lines)
			pair->Evaluate();
	}
public:
	Board(Color _mPieceColor)
		: boundary(std::make_shared<Boundary>())
		, turn(BLACK)
		, mPieceColor(_mPieceColor)
		, oPieceColor(!_mPieceColor)
		, board(15, Hasher, Equal)
		, rows(RANGE, std::make_shared<Line>(ROW))
		, columns(RANGE, std::make_shared<Line>(COLUMN))
		, lefts(RANGE * 2 - 1, std::make_shared<Line>(LEFT))
		, rights(RANGE * 2 - 1, std::make_shared<Line>(RIGHT))
	{
		initialize();
	}

	shared_ptr<Point> operator[](Axis axis)
	{
		return board[axis];
	}

	Color JudgeWin()
	{
		auto it = find_if(lines.begin(), lines.end(), [=](shared_ptr<Line> pair){return pair->CheckWin() != EMPTY; });
		return it == lines.end() ? EMPTY : (*it)->CheckWin();
	}

	void InputChess(Axis axis)
	{
		assert(board[axis]->color == EMPTY);
		board[axis]->color = turn;
		boundary->change_boundary(axis);
		evaluate_points();
		turn = !turn;
	}
	void undo_InputChess(Axis axis)
	{
		board[axis]->color = EMPTY;
		boundary->undo_change_boundary();
		evaluate_points();
		turn = !turn;
	}

	std::vector<shared_ptr<Point>> empty_points()
	{
		std::vector<shared_ptr<Point>> va;
		for (auto &axis : boundary->GetRangeAxis())
			if (board[axis]->color == EMPTY)
				va.push_back(board[axis]);
		return va;
	}

	Color GetTurn()
	{
		return turn;
	}
};
