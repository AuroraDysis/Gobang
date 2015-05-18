#pragma once
#include "stdafx.h"
#include <hash_map>
#include "Line.h"
#include "Boundary.h"

using std::hash_map;
using std::shared_ptr;

class Board
{
public:
	Board(Color _mPieceColor);
	~Board();
	//下棋
	void input(Axis axis);
	//撤销下棋
	void undo_input(Axis axis);
	shared_ptr<Point> operator[](Axis axis);
	Color judge_win();
private:
	Color mPieceColor;
	Color oPieceColor;
	//重新评价每个点的价值
	void evaluate_points();
	//初始化棋盘
	void initialize();
	//输出boundary范围内空的点
	std::vector<shared_ptr<Point>> empty_points();

	Color turn;
	shared_ptr<Boundary> boundary;
	
	hash_map<int, shared_ptr<Point>> board;
	hash_map<int, shared_ptr<Line>> all_row;
	hash_map<int, shared_ptr<Line>> all_column;
	hash_map<int, shared_ptr<Line>> all_left_oblique;
	hash_map<int, shared_ptr<Line>> all_right_oblique;

	std::vector<shared_ptr<Line>> total_line;
};

