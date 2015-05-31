#pragma once
#include <vector>
#include "point.h"
#include "stdafx.h"

class Part
{
	typedef std::vector<std::shared_ptr<Point>>		Container;
	typedef Container::const_iterator				ConstIterator;
public:
	int					start_index;
	int					end_index;
	int					length;
	Color				color;
	Container			points;

	Part(ConstIterator _begin, ConstIterator _end, int _startIndex)
		: start_index(_startIndex)
		, end_index(_startIndex + (_end - _begin) - 1)
		, color((*_begin)->color)
		, length(_end - _begin)
		, points(_begin, _end)
	{
	}
	operator int() { return length; }
};

