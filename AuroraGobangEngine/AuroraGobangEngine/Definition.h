//此头文件用来定义经常需要使用的类型及相关操作
#pragma once
#include "stdafx.h"
#include <tuple>
#include <stack>

#define _max(a,b) ((a) > (b)) ? (a) : (b)
#define _min(a,b) ((a) < (b)) ? (a) : (b)
#define _abs(x) ((x) > 0) ? (x) : (-(x))

const unsigned int range = 14;

class Axis
{
private:
	std::tuple<int, int> axis;
public:
	Axis(int row, int column);
	int x;
	int y;
	operator std::tuple<int, int>()
	{
		return axis;
	}
};

inline Axis::Axis(int _row, int _column)
{
	std::tie(x, y) = axis;
}


enum Color
{
	Black,
	White,
	Empty = -1
};

//不要将它用作Empty
inline Color operator!(Color& color)
{
	return static_cast<Color>(_abs(color - 1));
}

enum Orientation
{
	Up,
	Down,
	Left,
	Right
};

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
Boundary::Boundary()
{
	up.push(7);
	down.push(7);
	left.push(7);
	right.push(7);
}

Boundary::~Boundary() = default;

inline int Boundary::get_range(Orientation ori)
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
}

inline void Boundary::change_boundary(Axis axis)
{
	up.push(_min(axis.y, up.top()));
	down.push(_max(axis.y, down.top()));
	left.push(_min(axis.x, left.top()));
	right.push(_max(axis.x, right.top()));
}

inline void Boundary::undo_change_boundary()
{
	up.pop();
	down.pop();
	left.pop();
	right.pop();
}

enum LineDirection
{
	Row,
	Column,
	left_oblique,
	right_oblique
};

