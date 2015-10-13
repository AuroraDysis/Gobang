#pragma once
#include "stdafx.h"
#include <hash_map>
#include <tuple>
#include "Line.h"


class Board
{
public:
	Board();
	//����
	void input(Axis axis);
	//��������
	void undo_input(Axis axis);
	Point &operator[] (Axis axis)
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
	std::vector<Axis> empty_points();
	Boundary boundary;
	Color turn = Black;
	std::hash_map<std::tuple<int, int>, Point> board;
	std::hash_map<int, Line> row;
	std::hash_map<int, Line> column;
	std::hash_map<int, Line> leftOblique;
	std::hash_map<int, Line> rightOblique;
};

