#pragma once
#include "stdafx.h"
#include <array>

class Point
{
public:
	Point(int row, int column);
	//���ڻ�ȡ��һ��ļ�ֵ����ǰ��õ�ֵ�������������ϵ�ֵ������
	double GetValue(Color color);
	//�ı��Ӧ��ɫ�ļ�ֵ
	void ChangeValue(Color color, Direction ld, double value);
	//�����һ��ļ�ֵ
	void ClearValue();
	//ͬʱ�ı���һ��������ɫ��ֵ
	void ChangeTwoValue(Direction ld, double value);

	Axis Axis;

	int Row;
	int Column;
	int LeftOblique;
	int RightOblique;

	Color PointColor;
private:
	//0�Ǻڵģ�1�ǰ׵ģ�0123������б��б
	std::array<std::array<double, 4>, 2> value;
};
