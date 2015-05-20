#pragma once
#include "stdafx.h"
#include "Board.h"
#include <fstream>

class AutoMachine
{
public:
	AutoMachine(Color _color);
	void input_axis(int row, int column);
	Axis output_axis();
	Color judge_win();
	Color get_turn();
	std::string file_name;
	~AutoMachine();
private:
	std::shared_ptr<Board> board;
	void add_history(Axis axis);
	std::stack<std::shared_ptr<Point>> history;
	shared_ptr<Point> next_step;

	void calculate_next_step();
	double alphaBeta(int depth, double alpha, double beta);
};

