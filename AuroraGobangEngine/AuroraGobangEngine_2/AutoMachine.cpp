#include "stdafx.h"
#include "AutoMachine.h"
#include <fstream>


AutoMachine::AutoMachine(Color _color) : board(std::make_shared<Board>(_color)), MColor(_color)
{
	if (_color == Black)
	{
		NextStep = (*board)[Axis(7, 7)];
		board->InputChess(Axis(7, 7));
		addHistory(Axis(7, 7));
	}
}

void AutoMachine::addHistory(Axis axis)
{
	history.push((*board)[axis]);
}

AutoMachine::~AutoMachine() = default;

void AutoMachine::InputAxis(int row, int column)
{
	board->InputChess(Axis(row, column));
	addHistory(Axis(row, column));
	calculateNextStep();
}

int AutoMachine::UndoInputAxis()
{
	int count = 0;
	for (int i = 0; i < 2 && history.size() > 0; i++)
	{
		if (history.size() == 1 && history.top()->PointColor == MColor)
		{
			break;
		}
		board->UndoInputChess(history.top()->Axis);
		removeHistory();
		++count;
	}
	return count;
}

void AutoMachine::removeHistory()
{
	history.pop();
}

Color AutoMachine::JudgeWin()
{
	return board->JudgeWin();
}

Axis AutoMachine::OutputAxis()
{
	return NextStep->Axis;
}

void AutoMachine::calculateNextStep()
{
	shared_ptr<Point> max = (*board)[Axis(0, 0)];
	for (auto point : (*board).EmptyPoints())
		if (point->GetValue(board->turn) > max->GetValue(board->turn))
			max = point;
	NextStep = max;
	board->InputChess(NextStep->Axis);
	addHistory(NextStep->Axis);
}

double AutoMachine::alphaBeta(int depth, double alpha, double beta)
{
	if (depth == 0 || board->JudgeWin() != Empty)
		throw std::exception("未完成，应返回局面价值");
	for (auto point : board->EmptyPoints())
	{
		board->InputChess(point->Axis);
		double value = -alphaBeta(depth - 1, -alpha, -beta);
		board->UndoInputChess(point->Axis);
		if (value >= beta)
			return beta;
		if (value > alpha)
			alpha = value;
	}
	return alpha;
}

Color AutoMachine::GetTurn()
{
	return board->turn;
}

std::shared_ptr<Point> AutoMachine::GetPoint(int row, int column)
{
	return (*board)[Axis(row, column)];
}