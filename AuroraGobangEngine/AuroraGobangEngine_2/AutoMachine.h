#pragma once
#include "stdafx.h"
class AutoMachine
{
public:
	AutoMachine(Color _color);
	~AutoMachine();

	void InputAxis(int row, int column);
	int UndoInputAxis();
	Axis OutputAxis();
	Color JudgeWin();
	Color GetTurn();

	std::string fileName;
	shared_ptr<Point> NextStep;
	Color MColor;
private:
	
	std::shared_ptr<Board> board;
	void addHistory(Axis axis);
	void removeHistory();
	std::stack<std::shared_ptr<Point>> history;
	void calculateNextStep();
	double alphaBeta(int depth, double alpha, double beta);
};

