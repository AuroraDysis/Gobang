#include "stdafx.h"
#include "PartialLine.h"

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

PartialLine::PartialLine(Direction dir, std::shared_ptr<Part> part) : PartialLineColor(part->PartColor), LineDirection(dir), Length(part->Length)
{
	AddPart(part);
}

PartialLine::~PartialLine() = default;

void PartialLine::AddPart(std::shared_ptr<Part> part)
{
	parts.push_back(part);
	Length += part->Length;
	if (part->PartColor != Empty)
		PartialLineColor = part->PartColor;
}

void PartialLine::Evaluate()
{
	if (PartialLineColor != Empty && Length > 4)
	{
		for (auto beg = parts.begin(); beg != parts.end(); beg++)
		{
			if (beg == parts.begin() && beg + 1 == parts.end())
			{
				continue;
			}
			else if (beg == parts.begin())
			{
				if ((*beg)->PartColor == Empty)
				{
					(*beg)->Points.front()->ChangeTwoValue(LineDirection, 靠两边的点);
				}
				else
				{
					for (int i = 0; i < _min((*(beg + 1))->Length, 3); i++)
					{
						(*(beg + 1))->Points[i]->ChangeValue(PartialLineColor, LineDirection, 靠墙的子的另一边[(*beg)->Points.size() - 1][i]);
					}

					for (int i = 0; i < _min(3, (*(beg + 1))->Length); i++)
					{
						(*(beg + 1))->Points[i]->ChangeValue(PartialLineColor, LineDirection, value_matrix[(*beg)->Length - 1][i]);
					}
				}
			}
			else if (beg + 1 == parts.end())
			{
				if ((*beg)->PartColor == Empty)
				{
					(*beg)->Points.back()->ChangeTwoValue(LineDirection, 靠两边的点);
				}
				else
				{
					for (int i = 0; i < _min((*(beg - 1))->Length, 3); i++)
					{
						(*(beg - 1))->Points[(*(beg - 1))->Length - 1 - i]->ChangeValue(PartialLineColor, LineDirection, 靠墙的子的另一边[(*beg)->Points.size() - 1][i]);
					}

					for (int i = 0; i < _min(3, (*(beg - 1))->Length); i++)
					{
						(*(beg - 1))->Points[(*(beg - 1))->Length - 1 - i]->ChangeValue(PartialLineColor, LineDirection, value_matrix[(*beg)->Length - 1][i]);
					}
				}
			}
			else
			{
				if ((*beg)->PartColor != Empty)
				{
					for (int i = 0; i < _min(3, (*(beg - 1))->Length); i++)
					{
						(*(beg - 1))->Points[(*(beg - 1))->Length - 1 - i]->ChangeValue(PartialLineColor, LineDirection, value_matrix[(*beg)->Length - 1][i]);
					}

					for (int i = 0; i < _min(3, (*(beg + 1))->Length); i++)
					{
						(*(beg + 1))->Points[i]->ChangeValue(PartialLineColor, LineDirection, value_matrix[(*beg)->Length - 1][i]);
					}
				}
			}
		}//for
	}
}