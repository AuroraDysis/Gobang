#pragma once
#include <vector>
#include "stdafx.h"

class PartialLine
{
public:
	PartialLine(Direction dir,std::shared_ptr<Part> part);
	
	Color PartialLineColor;
	Direction LineDirection;
	int Length;
    
	void AddPart(std::shared_ptr<Part> part);
	void Evaluate();
	~PartialLine();
private:
	std::vector<std::shared_ptr<Part>> parts;
};

