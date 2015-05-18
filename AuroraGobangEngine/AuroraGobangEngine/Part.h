#pragma once
#include <vector>
#include "stdafx.h"

class Part
{
public:
	Part();
	void set_value(int _start, int _end, int _length, Color _color);
	~Part();
	int start;
	int end;
	int length;
	Color color;
	std::vector<std::shared_ptr<Point>> points;
};
