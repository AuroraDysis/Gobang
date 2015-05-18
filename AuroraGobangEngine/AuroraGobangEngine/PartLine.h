#pragma once
#include <vector>
#include "Part.h"
#include "stdafx.h"

class PartLine
{
public:
	PartLine(LineDirection ld);
	void add_part(std::shared_ptr<Part> part);
	Color color;
	LineDirection direction;
	void evaluate();
	~PartLine();
private:
	std::vector<std::shared_ptr<Part>> parts;
};

