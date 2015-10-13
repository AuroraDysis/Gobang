#pragma once
#include "stdafx.h"
#include <vector>
#include "PartLine.h"
using std::shared_ptr;


class Line
{
public:
	Line(LineDirection ld);
	//��鱾���Ƿ���ʤ����
	Color check_win();
	//���������������λ��
	void add_point(shared_ptr<Point> point);
	//���������ߣ������������������parts�ڣ�ÿ��������ö�Ӧ���к��У�б�����·���
	void analyse_line();
	//����ÿ����ļ�ֵ
	void evaluate();
	shared_ptr<Point> operator[] (int index)
	{
		return line[index];
	}
private:
	LineDirection direction;
	std::vector<shared_ptr<Point>> line;
	std::vector<shared_ptr<Part>> parts;
	std::vector<PartLine> part_lines;
};