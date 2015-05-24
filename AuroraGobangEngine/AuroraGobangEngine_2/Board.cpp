#include "stdafx.h"
#include "Board.h"

#include <iostream>
#include <iomanip>4



Board::Board(Color _mPieceColor) : boundary(std::make_shared<Boundary>()), turn(Black), mPieceColor(_mPieceColor), oPieceColor(!_mPieceColor)
{
	initialize();
}

Board::~Board() = default;

void Board::initialize()
{
	for (int i = 0; i < range; i++)
	{
		allRow[i] = std::make_shared<Line>(Row);
		allColumn[i] = std::make_shared<Line>(Column);
	}
	for (int i = 0; i < range * 2 - 1; i++)
	{
		allLeftOblique[i] = std::make_shared<Line>(LeftOblique);
		allRightOblique[i] = std::make_shared<Line>(RightOblique);
	}
	for (int _row = 0; _row < range; _row++)
	{
		for (int _column = 0; _column < range; _column++)
		{
			auto point = std::make_shared<Point>(_row, _column);
			board[Axis(_row, _column)] = point;
			allRow[_row]->AddPoint(board[Axis(_row, _column)]);
			allColumn[_column]->AddPoint(board[Axis(_row, _column)]);
		}
	}
	//左上到右下，每一行左下到右上
	for (int oblique = 0; oblique < range; oblique++)
		for (int row = oblique, column = 0; row >= 0; --row, ++column)
			allLeftOblique[oblique]->AddPoint(board[Axis(row, column)]);
	for (int oblique = range; oblique < range * 2 - 1; oblique++)
		for (int row = range - 1, column = oblique - range + 1; column < range; --row, ++column)
			allLeftOblique[oblique]->AddPoint(board[Axis(row, column)]);
	//右上到左下，每一行左上到右下
	for (int oblique = 0; oblique < range; oblique++)
		for (int row = 0, column = 14 - oblique; column < range; ++row, ++column)
			allRightOblique[oblique]->AddPoint(board[Axis(row, column)]);
	for (int oblique = range; oblique < range * 2 - 1; oblique++)
		for (int row = oblique - range + 1, column = 0; row < range; ++row, ++column)
			allRightOblique[oblique]->AddPoint(board[Axis(row, column)]);

	for (auto &pair : allRow)
		totalLine.push_back(pair.second);
	for (auto &pair : allColumn)
		totalLine.push_back(pair.second);
	for (auto &pair : allLeftOblique)
		totalLine.push_back(pair.second);
	for (auto &pair : allRightOblique)
		totalLine.push_back(pair.second);
}

std::vector<shared_ptr<Point>> Board::EmptyPoints()
{
	std::vector<shared_ptr<Point>> va;
	for (int row = boundary->GetUp(); row < boundary->GetDown(); row++)
		for (int column = boundary->GetLeft(); column < boundary->GetRight(); column++)
			if (board[Axis(row, column)]->PointColor == Empty)
				va.push_back(board[Axis(row, column)]);
	return va;
}

void Board::InputChess(Axis axis)
{
	assert(board[axis]->PointColor == Empty);
	if (board[axis]->PointColor == Empty)
		board[axis]->PointColor = turn;
	else
		throw std::exception("下到了已有棋子的位置上");
	boundary->ChangeBoundary(axis);
	evaluatePoints();
	turn = !turn;
}

void Board::UndoInputChess(Axis axis)
{
	board[axis]->PointColor = Empty;
	boundary->UndoChangeBoundary();
	evaluatePoints();
	turn = !turn;
}

Color Board::JudgeWin()
{
	auto it = find_if(totalLine.begin(), totalLine.end(), [=](shared_ptr<Line> pair){return pair->CheckWin() != Empty; });
	return it == totalLine.end() ? Empty : (*it)->CheckWin();
}

void Board::evaluatePoints()
{
	for (auto &point : board)
		point.second->ClearValue();
	for (auto &pair : totalLine)
		pair->Evaluate();
	//for (int i = 0; i < range; i++)
	//{
	//	for (int j = 0; j < range; j++)
	//	{
	//		std::cout << std::setw(4) << board[Axis(i, j)]->GetValue(turn) << " ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;
}

shared_ptr<Point> Board::operator[](Axis axis) 
{
	return board[axis];
}