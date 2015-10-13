#include "stdafx.h"
#include "Boundary.h"


Boundary::Boundary()
{
	up.push(7);
	down.push(7);
	left.push(7);
	right.push(7);
}

Boundary::~Boundary() = default;

int Boundary::get_range(Orientation ori)
{
	switch (ori)
	{
	case Up:
		return _max(up.top() - 2, 0);
	case Down:
		return _min(down.top() + 2, range - 1);
	case Left:
		return _max(left.top() - 2, 0);
	case Right:
		return _min(right.top() + 2, range - 1);
	}
	//不可能路径
	return -1;
}

void Boundary::change_boundary(Axis axis)
{
	up.push(_min(axis.x, up.top()));
	down.push(_max(axis.x, down.top()));
	left.push(_min(axis.y, left.top()));
	right.push(_max(axis.y, right.top()));
}

void Boundary::undo_change_boundary()
{
	up.pop();
	down.pop();
	left.pop();
	right.pop();
}