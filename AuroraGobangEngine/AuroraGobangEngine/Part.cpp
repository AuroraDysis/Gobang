#include "stdafx.h"
#include "Part.h"


Part::Part()
{

}

void Part::set_value(int _start, int _end, int _length, Color _color)
{
	start = _start;
	end = _end;
	length = _length;
	color = _color;
}

Part::~Part() = default;