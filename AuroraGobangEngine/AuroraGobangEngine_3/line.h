#pragma once
#include "stdafx.h"
#include <vector>

class Line
{
	typedef std::vector<std::shared_ptr<Point>>				PointContainer;
	typedef std::vector<std::shared_ptr<Part>>				PartContainer;
	typedef std::vector<std::shared_ptr<PartialLine>>		PartialLineContainer;
private:
	Orientation						orientation;
	PointContainer					line;
	PartContainer					parts;
	PartialLineContainer			partial_lines;

	void analyse_line();
public:
	Line(Orientation _orientation)
		: orientation(_orientation)
	{
	}
	
	std::shared_ptr<Point> operator[] (int index)
	{
		return line[index];
	}

	void add_point(std::shared_ptr<Point> point)
	{
		line.push_back(point);
	}

	void evaluate()
	{
		if (line.size() < 5)
			return;
		analyse_line();
		for (auto &partialLine : partial_lines)
			partialLine->evaluate();
	}

	Color check_win()
	{
		auto it = std::find_if(parts.begin(), parts.end()
			, [=](std::shared_ptr<Part> part){ return part->color != EMPTY && part->length >= 5; });
		return it == parts.end() ? EMPTY : (*it)->color;
	}
};

