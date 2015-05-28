#include "stdafx.h"
#include "Part.h"


Part::Part(point_iterator begin, point_iterator end, int startIndex) 
	: StartIndex(startIndex)
	, PartColor((*begin)->PointColor)
{
	for (auto it = begin; it != end; it++)
		Points.push_back(*it);
	Length = end - begin;
	EndIndex = StartIndex + Length - 1;
}

Part::~Part() = default;

Part::operator int()
{
	return this->Length;
}