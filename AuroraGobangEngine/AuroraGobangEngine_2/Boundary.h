#pragma once
#include "stdafx.h"
#include <stack>

class Boundary
{
public:
	Boundary();
	~Boundary();
	void ChangeBoundary(Axis axis);
	void UndoChangeBoundary();

	int GetLeft();
	int GetRight();
	int GetUp();
	int GetDown();
private:
	std::stack<int> up;
	std::stack<int> down;
	std::stack<int> left;
	std::stack<int> right;
};

