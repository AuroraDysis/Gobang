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
	//��������ÿ����ļ�ֵ
	void evaluatePoints();
	//��ʼ������
	void initialize();
public:
	Color				turn;
	Board(Color _mPieceColor);
	~Board();
	//����
	void InputChess(Axis axis);
	//��������
	void UndoInputChess(Axis axis);
	
	//���boundary��Χ�ڿյĵ�
	std::vector<shared_ptr<Point>> EmptyPoints();
	//�ж��Ƿ���һ��ʤ��
	Color JudgeWin();
	shared_ptr<Point> operator[](Axis axis);
};

