#include "stdafx.h"
#include "Line.h"
#include <algorithm>

using std::shared_ptr;
using std::find_if;

Line::Line(LineDirection ld)
{
	direction = ld;
}

void Line::analyse_line()
{
	Color last = line.front()->State;
	int start = 0;
	int count = 0;

	parts.clear();
	parts.push_back(std::make_shared<Part>());
	for (auto i = line.cbegin(); i != line.cend(); i++)
	{
		if ((*i)->State == last)
		{
			count++;
		}
		else
		{
			parts.back()->set_value(start, start + count - 1, count, last);
			parts.push_back(std::make_shared<Part>());
			start += count;
			last = (*i)->State;
			count = 1;
		}
		parts.back()->points.push_back(*i);
		if (i + 1 == line.cend())
			parts.back()->set_value(start, start + count - 1, count, last);
	}

	part_lines.clear();
	part_lines.push_back(std::make_shared<PartLine>(direction));
	for (auto it = parts.begin(); it != parts.end(); it++)
	{
		if (it != parts.begin())
		{
			if ((*it)->color != Empty && (*(it - 1))->color != Empty && (*it)->color != (*(it - 1))->color)
			{
				part_lines.push_back(std::make_shared<PartLine>(direction));
				if ((*(it - 1))->color == Empty)
					part_lines.back()->add_part(*(it - 1));
			}
		}
		part_lines.back()->add_part(*it);
	}
}


void Line::evaluate()//to do
{
	analyse_line();
	if (line.size() < 5)
		return;
	for (auto &part_line : part_lines)
		part_line->evaluate();
}

void Line::add_point(std::shared_ptr<Point> point)
{
	line.push_back(point);
}

Color Line::check_win()
{
	auto it = find_if(parts.begin(), parts.end(), [=](shared_ptr<Part> part){return part->color != Empty && part->length >= 5; });
	return it == parts.end() ? Empty : (*it)->color;
}