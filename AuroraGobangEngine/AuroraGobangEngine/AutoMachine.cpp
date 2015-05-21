#include "stdafx.h"
#include "AutoMachine.h"
#include <thread>
#include <iostream>
#include <iomanip>
#include <fstream>

using std::thread;

AutoMachine::AutoMachine(Color _color) : board(std::make_shared<Board>(_color))
{
	if (_color == Black)
	{
		next_step = (*board)[Axis(7, 7)];
		board->input(Axis(7, 7));
		add_history(Axis(7, 7));
	}
}

void AutoMachine::add_history(Axis axis)
{
	history.push((*board)[axis]);
	std::ofstream fout;
	fout.open(file_name, std::ios::app);
	fout << history.top()->axis.x << "," << history.top()->axis.y << "\t" << (history.top()->State == Black ? "Black" : "White") << std::endl;
	fout.flush();
	fout.close();
}

AutoMachine::~AutoMachine() = default;

void AutoMachine::input_axis(int row, int column)
{
	board->input(Axis(row, column));
	add_history(Axis(row, column));
	calculate_next_step();
	//thread cal(&AutoMachine::calculate_next_step, this);
	//cal.join();
}

Color AutoMachine::judge_win()
{
	return board->judge_win();
}

Axis AutoMachine::output_axis()
{
	return next_step->axis;
}

void AutoMachine::calculate_next_step()
{
	shared_ptr<Point> max = (*board)[Axis(0, 0)];
	for (auto point : (*board).empty_points())
		if (point->get_value(board->turn) > max->get_value(board->turn))
			max = point;
	next_step = max;
	board->input(next_step->axis);
	add_history(next_step->axis);
}

double AutoMachine::alphaBeta(int depth, double alpha, double beta)
{
	if (depth == 0 || board->judge_win() != Empty)
		throw std::exception("未完成，应返回局面价值");
	for (auto point : board->empty_points())
	{
		board->input(point->axis);
		double value = -alphaBeta(depth - 1, -alpha, -beta);
		board->undo_input(point->axis);
		if (value >= beta)
			return beta;
		if (value > alpha)
			alpha = value;
	}
	return alpha;
}

Color AutoMachine::get_turn()
{
	return board->turn;
}