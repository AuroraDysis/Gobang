#pragma once
#include "stdafx.h"
#include <array>

class Point
{
public:
	Point(int row, int column);
	//用于获取这一点的价值，当前或得的值是所在四条线上的值加起来
	double GetValue(Color color);
	//改变对应颜色的价值
	void ChangeValue(Color color, Direction ld, double value);
	//清空这一点的价值
	void ClearValue();
	//同时改变这一点两个颜色的值
	void ChangeTwoValue(Direction ld, double value);

	Axis Axis;

	int Row;
	int Column;
	int LeftOblique;
	int RightOblique;

	Color PointColor;
private:
	//0是黑的，1是白的，0123横竖左斜右斜
	std::array<std::array<double, 4>, 2> value;
};
