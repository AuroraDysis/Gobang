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

	void calculate_next_step()
	{
		shared_ptr<Point> max = (*board)[Axis(0, 0)];
		for (auto point : (*board).empty_points())
			if (point->get_value(board->get_turn()) > max->get_value(board->get_turn()))
				max = point;
		next_step = max;
		board->input_chess(next_step->axis);
		add_history(next_step->axis);
	}

	void add_history(Axis axis)
	{
		history.push((*board)[axis]);
	}

	void remove_history()
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
			board->input_chess(Axis(7, 7));
			add_history(Axis(7, 7));
		}
	}

	void input_axis(Axis &axis)
	{
		board->input_chess(axis);
		add_history(axis);
		calculate_next_step();
	}

	int undo_input_axis()
	{
		int count = 0;
		for (int i = 0; i < 2 && history.size() > 0; i++)
		{
			if (history.size() == 1 && history.top()->color == my_color)
				break;
			board->undo_input_chess(history.top()->axis);
			remove_history();
			++count;
		}
		return count;
	}

	std::shared_ptr<Point> get_next_step()
	{
		return next_step;
	}

	Color get_turn()
	{
		return board->get_turn();
	}

	Color judge_win()
	{
		return board->judge_win();
	}

	std::shared_ptr<Point> operator[](Axis &axis)
	{
		return (*board)[axis];
	}
};

