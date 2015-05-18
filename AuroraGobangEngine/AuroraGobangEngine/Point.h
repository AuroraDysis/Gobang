#pragma once

#include "stdafx.h"

class Point
{
public:
	Point(int row, int column);
	//用于获取这一点的价值，当前或得的值是所在四条线上的值加起来
	double get_value(Color &color);
	//设置对应颜色的价值
	void set_value(Color &color, LineDirection ld, double value);
	Axis axis;
	int Row;
	int Column;
	int left_oblique;
	int right_oblique;
	Color State = Empty;
private: 
	//0是黑的，1是白的，0123横竖左斜右斜
	double value[2][4];

	//重要性，离中间越近的地方重要性越大
	double weight;

	
};

