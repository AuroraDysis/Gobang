#pragma once
#include "stdafx.h"
#include <vector>
#include "PartLine.h"
using std::shared_ptr;


class Line
{
public:
	Line(LineDirection ld);
	//检查本行是否有胜利者
	Color check_win();
	//往这条线里面添加位置
	void add_point(shared_ptr<Point> point);
	//分析整条线，并将分析结果储存在parts内，每次下棋后让对应的行和列，斜线重新分析
	void analyse_line();
	//评价每个点的价值
	void evaluate();
	shared_ptr<Point> operator[] (int index)
	{
		return line[index];
	}
private:
	LineDirection direction;
	std::vector<shared_ptr<Point>> line;
	std::vector<shared_ptr<Part>> parts;
	std::vector<PartLine> part_lines;
};