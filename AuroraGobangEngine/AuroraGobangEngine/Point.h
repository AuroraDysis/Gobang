#pragma once

#include "stdafx.h"
#include <array>

class Point
{
public:
	Point(int row, int column);
	//���ڻ�ȡ��һ��ļ�ֵ����ǰ��õ�ֵ�������������ϵ�ֵ������
	double get_value(Color color);
	//�ı��Ӧ��ɫ�ļ�ֵ
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
	//0�Ǻڵģ�1�ǰ׵ģ�0123������б��б
	std::array<std::array<double, 4>, 2> value;
	//��Ҫ�ԣ����м�Խ���ĵط���Ҫ��Խ��
	double weight;
};

