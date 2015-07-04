#pragma once
#pragma once
#include "stdafx.h"
#include "board.h"

class StateMachine
{
private:
	std::shared_ptr<Board>							board;
	std::stack<std::shared_ptr<Point>>				history;
	shared_ptr<Point>								next_step;
	Color											my_color;

	void CalculateNextStep()
	{
		shared_ptr<Point> max = (*board)[Axis(0, 0)];
		for (auto point : (*board).empty_points())
			if (point->GetValue(board->GetTurn()) > max->GetValue(board->GetTurn()))
				max = point;
		next_step = max;
		board->InputChess(next_step->axis);
		AddHistory(next_step->axis);
	}

	void AddHistory(Axis axis)
	{
		history.push((*board)[axis]);
	}

	void RemoveHistory()
	{
		history.pop();
	}

	//double alphaBeta(int depth, double alpha, double beta);
public:

	StateMachine(Color _color)
		: board(std::make_shared<Board>(_color))
		, my_color(_color)
	{
		if (_color == BLACK)
		{
			next_step = (*board)[Axis(7, 7)];
			board->InputChess(Axis(7, 7));
			AddHistory(Axis(7, 7));
		}
	}

	void InputAxis(Axis &axis)
	{
		board->InputChess(axis);
		AddHistory(axis);
		CalculateNextStep();
	}

	int UndoInputAxis()
	{
		int count = 0;
		for (int i = 0; i < 2 && history.size() > 0; i++)
		{
			if (history.size() == 1 && history.top()->color == my_color)
				break;
			board->undo_InputChess(history.top()->axis);
			RemoveHistory();
			++count;
		}
		return count;
	}

	std::shared_ptr<Point> GetNextStep()
	{
		return next_step;
	}

	Color GetTurn()
	{
		return board->GetTurn();
	}

	Color JudgeWin()
	{
		return board->JudgeWin();
	}

	std::shared_ptr<Point> operator[](Axis &axis)
	{
		return (*board)[axis];
	}
};

