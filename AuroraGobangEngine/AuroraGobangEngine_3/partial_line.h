#pragma once
#include <vector>
#include "stdafx.h"
#include "part.h"

class ImplicitConversion
{
public:
	int operator()(int _para1, std::shared_ptr<Part> _para2)
	{
		return _para1 + _para2->length;
	}
};

class PartialLine
{
	typedef std::vector<std::shared_ptr<Part>>		Container;
	typedef Container::const_iterator				ConstIterator;
private:
	Container parts;
public:
	int						length;
	Color					color;
	Orientation				orientation;

	PartialLine(ConstIterator _begin, ConstIterator _end, Orientation _orientation, Color _color)
		: orientation(_orientation)
		, color(_color)
		, length(std::accumulate(_begin, _end, 0, ImplicitConversion()))
		, parts(_begin, _end)
	{
	}

	void evaluate();
};

