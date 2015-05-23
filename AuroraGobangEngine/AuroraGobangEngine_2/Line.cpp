#include "stdafx.h"
#include "Line.h"


Line::Line(Direction ld) : direction(ld)
{
}


Line::~Line() = default;

inline std::shared_ptr<Point> Line::operator[] (int index)
{
	return line[index];
}

void Line::analyseLine()
{
	//清空上次分析的结果
	parts.clear();
	partialLines.clear();

	for (auto it = line.cbegin(); it != line.cend(); it++)
	{
		if (parts.size() == 0 || parts.back()->PartColor != (*it)->PointColor)
			parts.push_back(std::make_shared<Part>(*it, it - line.cbegin()));
		else if (parts.back()->PartColor == (*it)->PointColor)
			parts.back()->AddPoint(*it);
	}

	for (auto it = parts.cbegin(); it != parts.cend(); it++)
	{
		if (partialLines.size() == 0 || (partialLines.back()->PartialLineColor != Empty && (*it)->PartColor != Empty && partialLines.back()->PartialLineColor != (*it)->PartColor))
			partialLines.push_back(std::make_shared<PartialLine>(direction, *it));
		else
			partialLines.back()->AddPart(*it);
	}
}

void Line::Evaluate()
{
	if (line.size() < 5)	return;
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