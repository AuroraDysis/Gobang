#pragma once

#include "stdafx.h"

class Point
{
public:
	Point(int row, int column);
	//���ڻ�ȡ��һ��ļ�ֵ����ǰ��õ�ֵ�������������ϵ�ֵ������
	double get_value(Color &color);
	//���ö�Ӧ��ɫ�ļ�ֵ
	void set_value(Color &color, LineDirection ld, double value);
	Axis axis;
	int Row;
	int Column;
	int left_oblique;
	int right_oblique;
	Color State = Empty;
private: 
	//0�Ǻڵģ�1�ǰ׵ģ�0123������б��б
	double value[2][4];

	//��Ҫ�ԣ����м�Խ���ĵط���Ҫ��Խ��
	double weight;

	
};

