#include "stdafx.h"
#include "Boundary.h"


Boundary::Boundary()
{
}


Boundary::~Boundary() = default;

void Boundary::ChangeBoundary(Axis axis)
{
	if (up.size() != 0)
	{
		up.push(_min(axis.row, up.top()));
		down.push(_max(axis.row, down.top()));
		left.push(_min(axis.column, left.top()));
		right.push(_max(axis.column, right.top()));
	}
	else
	{
		up.push(axis.row);
		down.push(axis.row);
		left.push(axis.column);
		right.push(axis.column);
	}
	
}

void Boundary::UndoChangeBoundary()
{
	up.pop();
	down.pop();
	left.pop();
	right.pop();
}

int Boundary::GetUp()
{
	return this->up.top();
}

int Boundary::GetDown()
{
	return this->down.top();
}

int Boundary::GetLeft()
{
	return this->left.top();
}

int Boundary::GetRight()
{
	return this->right.top();
}