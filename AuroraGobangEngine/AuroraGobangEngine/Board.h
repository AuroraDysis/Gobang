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
	//����
	void input(Axis axis);
	//��������
	void undo_input(Axis axis);
	shared_ptr<Point> operator[] (Axis axis)
	{
		return board[axis];
	}
	Color judge_win();
private:
	
	//��������ÿ����ļ�ֵ
	void evaluate_points();
	//��ʼ������
	void initialize();
	//���boundary��Χ�ڿյĵ�
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

