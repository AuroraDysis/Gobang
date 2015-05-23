#include "stdafx.h"
#include "Part.h"


Part::Part(std::shared_ptr<Point> start, int startIndex) : StartIndex(startIndex), EndIndex(startIndex), Length(1), PartColor(start->PointColor)
{
	Points.push_back(start);
}

Part::~Part() = default;

void Part::AddPoint(std::shared_ptr<Point> point)
{
	Points.push_back(point);
	++EndIndex;
	++Length;
}

Part::operator int()
{
	return this->Length;
}