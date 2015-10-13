#pragma once
#include <stack>
#include "stdafx.h"

class Boundary
{
public:
	Boundary();
	~Boundary();
	void change_boundary(Axis axis);
	void undo_change_boundary();
	int get_range(Orientation ori);
private:
	std::stack<int> up;
	std::stack<int> down;
	std::stack<int> left;
	std::stack<int> right;
};
