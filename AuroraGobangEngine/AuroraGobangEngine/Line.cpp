#include "stdafx.h"
#include "Line.h"


Line::Line(LineDirection ld)
{
	direction = ld;
}

void Line::analyse_line()
{
	Color last = line.front().State;
	int start = 0;
	int count = 0;
	for (auto i = line.cbegin(); i != line.cend(); i++)
	{
		if (i->State == last)
			count++;
		else
		{
			parts.push_back(Part(start, start + count - 1, count, last));
			start = start + count;
			last = i->State;
			count = 1;
		}
	}
}

void Line::evaluate()
{
	//to do
}

void Line::add_point(Point &point)
{
	line.push_back(point);
}

Color Line::check_win()
{
	return White;
}