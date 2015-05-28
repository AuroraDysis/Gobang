#include "stdafx.h"
#include "Line.h"
#include <algorithm>


Line::Line(Direction ld) 
	: direction(ld)
{
}


Line::~Line() = default;

inline std::shared_ptr<Point> Line::operator[] (int index)
{
	return line[index];
}

void Line::analyseLine()
{
	if (line.size() < 5)
		return;
	//清空上次分析的结果
	parts.clear();
	partialLines.clear();

	for (auto it = line.cbegin(); it != line.cend();)
	{
		auto last = std::find_if(it, line.cend(), [&](std::shared_ptr<Point> point){return point->PointColor != (*it)->PointColor; });
		parts.push_back(std::make_shared<Part>(it, last, it - line.cbegin()));
		it = last;
	}

	for (auto it = parts.cbegin(); it != parts.cend();)
	{
		auto colorIt = std::find_if(it, parts.cend(), [&](std::shared_ptr<Part> part){return part->PartColor != Empty; });
		if (colorIt == parts.cend())
		{
			partialLines.push_back(std::make_shared<PartialLine>(it++, parts.cend(), direction, Empty));
		}
		else
		{
			auto endIt = std::find_if(colorIt, parts.cend(), [&](std::shared_ptr<Part> part){return part->PartColor != (*colorIt)->PartColor && part->PartColor != Empty; });
			partialLines.push_back(std::make_shared<PartialLine>(it, endIt, direction, (*colorIt)->PartColor));
			it = endIt;
			if ((*(--endIt))->PartColor != Empty)
				++it;
		}
	}
}

void Line::Evaluate()
{
	if (line.size() < 5)
		return;
	analyseLine();
	for (auto &partialLine : partialLines)
		partialLine->Evaluate();
}

void Line::AddPoint(std::shared_ptr<Point> point)
{
	line.push_back(point);
}

Color Line::CheckWin()
{
	auto it = std::find_if(parts.begin(), parts.end(), [=](std::shared_ptr<Part> part){return part->PartColor != Empty && part->Length >= 5; });
	return it == parts.end() ? Empty : (*it)->PartColor;
}