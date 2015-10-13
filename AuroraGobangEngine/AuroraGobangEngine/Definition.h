//��ͷ�ļ��������徭����Ҫʹ�õ����ͼ���ز���
#pragma once
#include "stdafx.h"
#include <tuple>
#include <stack>

#define _max(a,b) ((a) > (b) ? (a) : (b))
#define _min(a,b) ((a) < (b) ? (a) : (b))
#define _abs(x) ((x) > 0 ? (x) : (-(x)))

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
	operator int()
	{
		return x * 100 + y;
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

//��Ҫ��������Empty
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

enum LineDirection
{
	Row,
	Column,
	Left_oblique,
	Right_oblique
};

