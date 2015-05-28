#pragma once
#include <vector>
#include "stdafx.h"

class Part
{
public:
	typedef std::vector<std::shared_ptr<Point>>::const_iterator point_iterator;
	Part(point_iterator begin, point_iterator end, int startIndex);
	~Part();
	int StartIndex;
	int EndIndex;
	int Length;
	Color PartColor;
	std::vector<std::shared_ptr<Point>> Points;
	operator int();
};
