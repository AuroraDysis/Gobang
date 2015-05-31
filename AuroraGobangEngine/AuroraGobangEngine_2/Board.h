#pragma once

#include "stdafx.h"
#include <hash_map>
using std::hash_map;
using std::shared_ptr;

class Board
{
private:
	Color								mPieceColor;
	Color								oPieceColor;
	shared_ptr<Boundary>				boundary;
	hash_map<int, shared_ptr<Line>>		allRow;
	hash_map<int, shared_ptr<Line>>		allColumn;
	hash_map<int, shared_ptr<Line>>		allLeftOblique;
	hash_map<int, shared_ptr<Line>>		allRightOblique;
	hash_map<int, shared_ptr<Point>>	board;
	std::vector<shared_ptr<Line>>		totalLine;
	//重新评价每个点的价值
	void evaluatePoints();
	//初始化棋盘
	void initialize();
public:
	Color				turn;
	Board(Color _mPieceColor);
	~Board();
	//下棋
	void InputChess(Axis axis);
	//撤销下棋
	void UndoInputChess(Axis axis);
	
	//输出boundary范围内空的点
	std::vector<shared_ptr<Point>> EmptyPoints();
	//判断是否有一方胜利
	Color JudgeWin();
	shared_ptr<Point> operator[](Axis axis);
};

