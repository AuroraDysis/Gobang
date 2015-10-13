// AuroraGobangEngine.cpp : Main��ڵ�
//

#include "stdafx.h"
#include "Board.h"
#include "AutoMachine.h"

#include <iostream>
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	int _color = -1;
	//������Ե���ɫ(����0������1),���������ʽ��row column
	do
	{
		std::cin >> _color;
	} while (_color != -1 && (_color == 0 || _color == 1));
	std::shared_ptr<AutoMachine> auto_machine = std::make_shared<AutoMachine>(static_cast<Color>(_color));
	do
	{
		int x = -1, y = -1;
		do
		{
			std::cin >> x >> y;
		} while (x >= 0 && y >= 0 && x <= range && y <= range);
		Axis axis(auto_machine->output_axis());
		std::cout << axis.x << " " << axis.y << std::endl;
	} while (auto_machine->judge_win() == Empty);
	return 0;
}

