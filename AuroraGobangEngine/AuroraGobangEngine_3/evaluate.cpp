#include "stdafx.h"
#include "partial_line.h"

using std::array;

const double 靠两边的点 = 0;
const array<array<double, 3>, 5> 靠墙的子的另一边 = { {
	{ -15, -5, 0 },
	{ -170, -80, 0 },
	{ -290, -45, 0 },
	{ 0, 0, 0 },
	{ 0, 0, 0 }
	} };
const array<array<double, 3>, 5> value_matrix = { {
	{ 20, 10, 1 },
	{ 200, 100, 0 },
	{ 500, 250, 0 },
	{ 5000, 250, 0 },
	{ 100000, 250, 0 }
	} };

void PartialLine::Evaluate()
{
	if (color != EMPTY && length > 4)//可能有错
	{
		for (auto beg = parts.begin(); beg != parts.end(); beg++)
		{
			if (beg == parts.begin() && beg + 1 == parts.end())
			{
				continue;
			}
			else if (beg == parts.begin())
			{
				if ((*beg)->color == EMPTY)
				{
					(*beg)->points.front()->ChangeValue(orientation, 靠两边的点);
				}
				else
				{
					for (int i = 0; i < MIN((*(beg + 1))->length, 3); i++)
					{
						(*(beg + 1))->points[i]->ChangeValue(color, orientation, 靠墙的子的另一边[(*beg)->points.size() - 1][i]);
					}

					for (int i = 0; i < MIN(3, (*(beg + 1))->length); i++)
					{
						(*(beg + 1))->points[i]->ChangeValue(color, orientation, value_matrix[(*beg)->length - 1][i]);
					}
				}
			}
			else if (beg + 1 == parts.end())
			{
				if ((*beg)->color == EMPTY)
				{
					(*beg)->points.back()->ChangeValue(orientation, 靠两边的点);
				}
				else
				{
					for (int i = 0; i < MIN((*(beg - 1))->length, 3); i++)
					{
						(*(beg - 1))->points[(*(beg - 1))->length - 1 - i]->ChangeValue(color, orientation, 靠墙的子的另一边[(*beg)->points.size() - 1][i]);
					}

					for (int i = 0; i < MIN(3, (*(beg - 1))->length); i++)
					{
						(*(beg - 1))->points[(*(beg - 1))->length - 1 - i]->ChangeValue(color, orientation, value_matrix[(*beg)->length - 1][i]);
					}
				}
			}
			else
			{
				if ((*beg)->color != EMPTY)
				{
					for (int i = 0; i < MIN(3, (*(beg - 1))->length); i++)
					{
						(*(beg - 1))->points[(*(beg - 1))->length - 1 - i]->ChangeValue(color, orientation, value_matrix[(*beg)->length - 1][i]);
					}

					for (int i = 0; i < MIN(3, (*(beg + 1))->length); i++)
					{
						(*(beg + 1))->points[i]->ChangeValue(color, orientation, value_matrix[(*beg)->length - 1][i]);
					}
				}
			}
		}//for
	}
}