#include "stdafx.h"
#include "state_machine.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::shared_ptr<StateMachine> state_machine;
std::string file_name;

bool is_record_history = false;
Color my_color;

void InputChess();
void OutputHistory(Point point);
void OutputHistoryWin(Color color);
void output();
void DeleteLastHistory(int count);

std::istream &operator>>(std::istream &is,Color color)
{
	std::string s;
	is >> s;
	color = (s == "Black" ? BLACK : WHITE);
	return is;
}

using std::string;
using std::istream_iterator;
using std::ostream_iterator;

int _tmain(int argc, _TCHAR* argv[])
{
	//得到自己的颜色
	std::cin >> my_color;
	//输入是否记录历史
	string history;
	std::cin >> history;
	is_record_history = history == "True" ? true : false;

	//利用获得的自己的颜色初始化自动机
	state_machine = std::make_shared<StateMachine>(my_color);

	if (is_record_history)
	{
		int count = 0;
		while (++count)
		{
			std::stringstream ss;
			ss << "history" << count << ".txt";
			std::fstream file(ss.str());
			if (!file)
			{
				file_name = ss.str();
				break;
			}
		}
	}
	
	if (my_color == BLACK)
		output();

	do
	{
		InputChess();
		output();
	} while (state_machine->JudgeWin() == EMPTY);

	return 0;
}

void InputChess()
{
	std::string input;
	while (true)
	{
		std::cin >> input;
		if (input == "UNDO")
		{
			int count = state_machine->UndoInputAxis();
			std::cout << count << std::endl;
			if (is_record_history)
				DeleteLastHistory(count);
			continue;
		}
		int x = -1, y = -1;
		std::stringstream ss(input);
		ss >> x;
		std::cin >> y;
		if (x < 0 || y < 0 || x >= RANGE || y >= RANGE)
			continue;
		state_machine->InputAxis(Axis(x, y));
		if (is_record_history)
			OutputHistory(*((*state_machine)[Axis(x, y)]));
		break;
	}
}

void OutputHistory(Point point)
{
	std::fstream fout(file_name, std::ios::app);
	fout << COLOR(point.color) << " " << point.row << "," << point.column << std::endl;
	fout.flush();
	fout.close();
}

void OutputHistoryWin(Color color)
{
	std::fstream fout(file_name, std::ios::app);
	fout << COLOR_WIN(color) << std::endl;
	fout.flush();
	fout.close();
}

void output()
{
	Color color = state_machine->JudgeWin();
	if (color == EMPTY)
	{
		std::cout << state_machine->GetNextStep()->axis.row << " " << state_machine->GetNextStep()->axis.column << std::endl;
		OutputHistory(*state_machine->GetNextStep());
	}
	else if (color == my_color)
	{
		std::cout << COLOR_WIN(color) << " " << state_machine->GetNextStep()->axis.row << " " << state_machine->GetNextStep()->axis.column << std::endl;
		OutputHistory(*state_machine->GetNextStep());
		OutputHistoryWin(color);
	}
	else
	{
		std::cout << COLOR_WIN(color) << std::endl;
		OutputHistoryWin(color);
	}
}

void DeleteLastHistory(int count)
{
	std::fstream fin(file_name, std::ios::in);

	std::vector<std::string> lines;
	auto lines_bi = std::back_inserter(lines);

	std::string line;
	while (std::getline(fin, line))
		lines_bi = line + "\n";

	for (int i = 0; i < count; i++)
		lines.pop_back();

	std::fstream fout(file_name, std::ios::out);
	ostream_iterator<string> out_iter(fout);

	std::copy(lines.cbegin(), lines.cend(), out_iter);
	fout.flush();
	fout.close();
}