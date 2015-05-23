#pragma once
#include "stdafx.h"
class Line
{
public:
	Line(Direction ld);
	~Line();

	//检查本行是否有胜利者
	Color CheckWin();
	//往这条线里面添加位置
	void AddPoint(std::shared_ptr<Point> point);
	//分析整条线，并将分析结果储存在parts内，每次下棋后让对应的行和列，斜线重新分析
	void Evaluate();
	std::shared_ptr<Point> operator[] (int index);

private:
	Direction direction;
	std::vector<std::shared_ptr<Point>> line;
	std::vector<std::shared_ptr<Part>> parts;
	std::vector<std::shared_ptr<PartialLine>> partialLines;

	void analyseLine();
	//评价每个点的价值
};
