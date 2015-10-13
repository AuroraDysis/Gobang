#pragma once
#include "stdafx.h"
class Line
{
public:
	Line(Direction ld);
	~Line();

	//��鱾���Ƿ���ʤ����
	Color CheckWin();
	//���������������λ��
	void AddPoint(std::shared_ptr<Point> point);
	//���������ߣ������������������parts�ڣ�ÿ��������ö�Ӧ���к��У�б�����·���
	void Evaluate();
	std::shared_ptr<Point> operator[] (int index);

private:
	Direction direction;
	std::vector<std::shared_ptr<Point>> line;
	std::vector<std::shared_ptr<Part>> parts;
	std::vector<std::shared_ptr<PartialLine>> partialLines;

	void analyseLine();
	//����ÿ����ļ�ֵ
};
