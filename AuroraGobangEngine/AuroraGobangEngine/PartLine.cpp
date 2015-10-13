#include "stdafx.h"
#include <array>
#include "PartLine.h"

using std::array;

const double 靠两边的点 = 0;
const array<array<double, 3>, 5> 靠墙的子的另一边 = {{
	{ -15, -5, 0 },
	{ -170, -80, 0 },
	{ -290, -45, 0 } , 
	{ 0, 0, 0 }, 
	{ 0, 0, 0 }
}};

const array<array<double, 3>, 5> value_matrix = {{
	{ 20, 10, 1 },
	{ 200, 100, 0 },
	{ 500, 250, 0 },
	{ 5000, 250, 0 },
	{100000, 250 ,0 }
}};

PartLine::PartLine(LineDirection ld) : color(Empty), direction(ld)
{
}

PartLine::~PartLine() = default;

void PartLine::add_part(std::shared_ptr<Part> part)
{
	parts.push_back(part);
	if (part->color != Empty)
		color = part->color;
}

void PartLine::evaluate()
{
	if (color == Empty)
	{
		for (auto &part : parts)
		{
			part->points.front()->change_two_value(direction, 靠两边的点);
			part->points.back()->change_two_value(direction, 靠两边的点);
		}
	}
	else
	{
		int length = 0;
		for (auto &part : parts)
		{
			length += part->length;
		}
		if (length < 5)
		{
			return;
		}

		for (auto beg = parts.begin(); beg != parts.end(); beg++)
		{
			if (beg == parts.begin() && beg + 1 == parts.end())
			{
				continue;
			}
			else if (beg == parts.begin())
			{
				if ((*beg)->color == Empty)
				{
					(*beg)->points.front()->change_two_value(direction, 靠两边的点);
				}
				else
				{
					for (int i = 0; i < _min((*(beg + 1))->length, 3); i++)
					{
						(*(beg + 1))->points[i]->change_value(color, direction, 靠墙的子的另一边[(*beg)->points.size() - 1][i]);
					}

					for (int i = 0; i < _min(3, (*(beg + 1))->length); i++)
					{
						(*(beg + 1))->points[i]->change_value(color, direction, value_matrix[(*beg)->length - 1][i]);
					}
				}
			}
			else if (beg + 1 == parts.end())
			{
				if ((*beg)->color == Empty)
				{
					(*beg)->points.back()->change_two_value(direction, 靠两边的点);
				}
				else
				{
					for (int i = 0; i < _min((*(beg - 1))->length, 3); i++)
					{
						(*(beg - 1))->points[(*(beg - 1))->length - 1 - i]->change_value(color, direction, 靠墙的子的另一边[(*beg)->points.size() - 1][i]);
					}

					for (int i = 0; i < _min(3, (*(beg - 1))->length); i++)
					{
						(*(beg - 1))->points[(*(beg - 1))->length - 1 - i]->change_value(color, direction, value_matrix[(*beg)->length - 1][i]);
					}
				}
			}
			else
			{
				if ((*beg)->color != Empty)
				{
					for (int i = 0; i < _min(3, (*(beg - 1))->length); i++)
					{
						(*(beg - 1))->points[(*(beg - 1))->length - 1 - i]->change_value(color, direction, value_matrix[(*beg)->length - 1][i]);
					}

					for (int i = 0; i < _min(3, (*(beg + 1))->length); i++)
					{
						(*(beg + 1))->points[i]->change_value(color, direction, value_matrix[(*beg)->length - 1][i]);
					}
				}
			}
		}
	}
}