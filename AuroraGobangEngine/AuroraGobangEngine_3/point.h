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

	double get_value(Color _color) const
	{
		return accumulate(value[BLACK].cbegin(), value[BLACK].cend(), 0.0)+
			   accumulate(value[WHITE].cbegin(), value[WHITE].cend(), 0.0);
	}
	void clear_value()
	{
		fill(value[BLACK].begin(), value[BLACK].end(), 0);
		fill(value[WHITE].begin(), value[WHITE].end(), 0);
	}
	void change_value(Orientation _orientation, double _value)
	{
		change_value(BLACK, _orientation, _value);
		change_value(WHITE, _orientation, _value);
	}
	void change_value(Color _color, Orientation _orientation, double _value)
	{
		assert(_color != EMPTY);
		value[_color][_orientation] += _value;
	}
};

