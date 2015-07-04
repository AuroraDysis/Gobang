#pragma once
#include "stdafx.h"

class Point
{
private:
	std::array<std::array<double, 4>, 2> value;
public:
	int					row;
	int					column;
	Axis				axis;
	Color				color;

	Point(int _row, int _column) 
		: row(_row)
		, column(_column)
		, axis(_row, _column)
		, color(EMPTY)
	{
	}

	double GetValue(Color _color) const
	{
		return accumulate(value[BLACK].cbegin(), value[BLACK].cend(), 0.0)+
			   accumulate(value[WHITE].cbegin(), value[WHITE].cend(), 0.0);
	}
	void ClearValue()
	{
		fill(value[BLACK].begin(), value[BLACK].end(), 0);
		fill(value[WHITE].begin(), value[WHITE].end(), 0);
	}
	void ChangeValue(Orientation _orientation, double _value)
	{
		ChangeValue(BLACK, _orientation, _value);
		ChangeValue(WHITE, _orientation, _value);
	}
	void ChangeValue(Color _color, Orientation _orientation, double _value)
	{
		assert(_color != EMPTY);
		value[_color][_orientation] += _value;
	}
};

