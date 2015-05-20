#pragma once

#include "stdafx.h"
#include <array>

class Point
{
public:
	Point(int row, int column);
	//用于获取这一点的价值，当前或得的值是所在四条线上的值加起来
	double get_value(Color color);
	//改变对应颜色的价值
	void change_value(Color color, LineDirection ld, double value);
	void clear_value();
	void change_two_value(LineDirection ld, double value);
	Axis axis;
	int Row;
	int Column;
	int Left_oblique;
	int Right_oblique;
	Color State = Empty;
private: 
	//0是黑的，1是白的，0123横竖左斜右斜
	std::array<std::array<double, 4>, 2> value;
	//重要性，离中间越近的地方重要性越大
	double weight;
};

