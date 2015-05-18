#pragma once
#include "stdafx.h"
#include <hash_map>
#include <tuple>
#include "Line.h"

using std::hash_map;
using std::shared_ptr;

class Board
{
public:
	Board();
	~Board();
	//下棋
	void input(Axis axis);
	//撤销下棋
	void undo_input(Axis axis);
	shared_ptr<Point> operator[] (Axis axis)
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
	std::vector<shared_ptr<Point>> empty_points();

	Color turn;
	shared_ptr<Boundary> boundary;
	
	hash_map<std::tuple<int, int>, shared_ptr<Point>> board;
	hash_map<int, shared_ptr<Line>> row;
	hash_map<int, shared_ptr<Line>> column;
	hash_map<int, shared_ptr<Line>> left_oblique;
	hash_map<int, shared_ptr<Line>> right_oblique;
	std::vector<shared_ptr<Line>> total_line;
};

