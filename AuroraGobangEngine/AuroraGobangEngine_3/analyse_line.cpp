#include "stdafx.h"
#include "line.h"

void Line::analyse_line()
{
	if (line.size() < 5)
		return;

	parts.clear();
	partial_lines.clear();

	auto parts_bi = std::back_inserter(parts);
	for (auto it = line.begin(); it != line.end();)
	{
		auto last = std::find_if(it, line.end(), [&](std::shared_ptr<Point> point){return point->color != (*it)->color; });
		parts_bi = std::make_shared<Part>(it, last, it - line.begin());
		it = last;
	}

	auto partial_lines_bi = std::back_inserter(partial_lines);
	for (auto it = parts.begin(); it != parts.end();)
	{
		auto colorIt = std::find_if(it, parts.end(), [&](std::shared_ptr<Part> part){return part->color != EMPTY; });
		if (colorIt == parts.end())
		{
			partial_lines_bi = std::make_shared<PartialLine>(it++, parts.end(), orientation, EMPTY);
		}
		else
		{
			auto endIt = std::find_if(colorIt, parts.end(), [&](std::shared_ptr<Part> part){return part->color != (*colorIt)->color && part->color != EMPTY; });
			partial_lines_bi = std::make_shared<PartialLine>(it, endIt, orientation, (*colorIt)->color);
			it = endIt;
			if ((*(--endIt))->color != EMPTY)
				++it;
		}
	}
}