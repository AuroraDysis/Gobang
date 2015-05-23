#pragma once
#include <vector>
#include "stdafx.h"

class Part
{
public:
	Part(std::shared_ptr<Point> start, int startIndex);
	~Part();
	int StartIndex;
	int EndIndex;
	int Length;
	Color PartColor;
	std::vector<std::shared_ptr<Point>> Points;

	void AddPoint(std::shared_ptr<Point> point);
	operator int();
};
