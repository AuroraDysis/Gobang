#pragma once
#include "stdafx.h"
#include <hash_map>
#include <tuple>
#include "Line.h"


class Board
{
public:
	Board();
	//下棋
	void input(Axis axis);
	//撤销下棋
	void undo_input(Axis axis);
	Point &operator[] (Axis axis)
	{
		return board[axis];
	}
	Color judge_win();
private:
	//重新评价每个点的价值
	void evaluate_points();
	//初始化棋盘
	void initialize();
	//输出boundary范围内空的点
	std::vector<Axis> empty_points();
	Boundary boundary;
	Color turn = Black;
	std::hash_map<std::tuple<int, int>, Point> board;
	std::hash_map<int, Line> row;
	std::hash_map<int, Line> column;
	std::hash_map<int, Line> leftOblique;
	std::hash_map<int, Line> rightOblique;
};

