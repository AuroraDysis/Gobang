#pragma once
#include "stdafx.h"
#include <vector>

struct Part
{
	Part(int _start, int _end, int _length, Color _color);
	int start;
	int end;
	int length;
	Color color;
};

Part::Part(int _start, int _end, int _length, Color _color)
{
	start = _start;
	end = _end;
	length = _length;
	color = _color;
}

class Line
{
public:
	using line_index_type = std::vector<Point>::size_type;
	using part_index_type = std::vector<Part>::size_type;

	Line(LineDirection ld);
	//��鱾���Ƿ���ʤ����
	Color check_win();
	//���������������λ��
	void add_point(shared_ptr<Point> point);
	//���������ߣ������������������parts�ڣ�ÿ��������ö�Ӧ���к��У�б�����·���
	void analyse_line();
	//����ÿ����ļ�ֵ
	void evaluate();
	shared_ptr<Point> operator[] (line_index_type index)
	{
		return line[index];
	}
private:
	LineDirection direction;
	std::vector<shared_ptr<Point>> line;
	std::vector<Part> parts;
};