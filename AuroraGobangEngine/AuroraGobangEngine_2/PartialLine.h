#pragma once
#include <vector>
#include "stdafx.h"

class PartialLine
{
public:
	typedef std::vector<std::shared_ptr<Part>>::const_iterator iterator;
	PartialLine(iterator start, iterator end, Direction dir, Color color);
	Color PartialLineColor;
	Direction LineDirection;
	int Length;
	void Evaluate();
	~PartialLine();
private:
	std::vector<std::shared_ptr<Part>> parts;
};

