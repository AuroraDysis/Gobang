// AuroraGobangEngine.cpp : Main入口点
//

#include "stdafx.h"
#include "Board.h"
#include "AutoMachine.h"

#include <iostream>
#include <string>
#include <sstream>

using std::string;

shared_ptr<AutoMachine> auto_machine;

int _tmain(int argc, _TCHAR* argv[])
{
	int _color = -1;
	//输入电脑的颜色(黑是0，白是1),输入坐标格式是row column
	do
	{
		std::cin >> _color;
	} while (_color != 0 && _color != 1);

	auto_machine = std::make_shared<AutoMachine>(static_cast<Color>(_color));


	int count = 1;
	while (count)
	{
		std::fstream file;
		std::stringstream ss;
		ss << "history" << count++ << ".txt";
		file.open(ss.str());
		if (!file)
		{
			auto_machine->file_name = ss.str();
			break;
		}
	}


	if (_color == 0)
	{
		std::ofstream fout;
		fout.open(auto_machine->file_name, std::ios::app);
		fout << "7,7" << "\t" << "Black" << std::endl;
		fout.flush();
		fout.close();
		Axis axis(auto_machine->output_axis());
		std::cout << axis.x << " " << axis.y << std::endl;
	}

	do
	{
		int x = -1, y = -1;
		do
		{
			std::cin >> x >> y;
		} while (x < 0 || y < 0 || x >= range || y >= range);
		auto_machine->input_axis(x, y);
		if (auto_machine->judge_win() == Empty)
		{
			Axis axis(auto_machine->output_axis());
			std::cout << axis.x << " " << axis.y << std::endl;
		}
		else
		{
			Axis axis(auto_machine->output_axis());
			std::cout << (auto_machine->judge_win() == Black ? "BlackWin" : "WhiteWin") << " " << axis.x << " " << axis.y << std::endl;
		}
	} while (auto_machine->judge_win() == Empty);

	Axis axis(auto_machine->output_axis());
	std::cout << axis.x << " " << axis.y << std::endl;

	std::ofstream fout;
	fout.open(auto_machine->file_name, std::ios::app);
	fout << axis.x << " " << axis.y << (auto_machine->judge_win() == Black ? "BlackWin" : "WhiteWin") << std::endl;
	fout << (auto_machine->judge_win() == Black ? "BlackWin" : "WhiteWin") << std::endl;
	fout.flush();
	fout.close();
	return 0;
}

