#pragma once
#include "stdafx.h"
#include <vector>

struct Part
{
	Part(int _start, int _end, int _length, Color _color);
	int start;
	int end;
	int length;
	Color color;
};

Part::Part(int _start, int _end, int _length, Color _color)
{
	start = _start;
	end = _end;
	length = _length;
	color = _color;
}

class Line
{
public:
	using line_index_type = std::vector<Point>::size_type;
	using part_index_type = std::vector<Part>::size_type;

	Line(LineDirection ld);
	//检查本行是否有胜利者
	Color check_win();
	//往这条线里面添加位置
	void add_point(shared_ptr<Point> point);
	//分析整条线，并将分析结果储存在parts内，每次下棋后让对应的行和列，斜线重新分析
	void analyse_line();
	//评价每个点的价值
	void evaluate();
	shared_ptr<Point> operator[] (line_index_type index)
	{
		return line[index];
	}
private:
	LineDirection direction;
	std::vector<shared_ptr<Point>> line;
	std::vector<Part> parts;
};