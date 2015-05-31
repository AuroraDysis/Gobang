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

void input_chess();
void output_history(Point point);
void output_history_win(Color color);
void output();
void delete_last_history(int count);

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
		input_chess();
		output();
	} while (state_machine->judge_win() == EMPTY);

	return 0;
}

void input_chess()
{
	std::string input;
	while (true)
	{
		std::cin >> input;
		if (input == "UNDO")
		{
			int count = state_machine->undo_input_axis();
			std::cout << count << std::endl;
			if (is_record_history)
				delete_last_history(count);
			continue;
		}
		int x = -1, y = -1;
		std::stringstream ss(input);
		ss >> x;
		std::cin >> y;
		if (x < 0 || y < 0 || x >= RANGE || y >= RANGE)
			continue;
		state_machine->input_axis(Axis(x, y));
		if (is_record_history)
			output_history(*((*state_machine)[Axis(x, y)]));
		break;
	}
}

void output_history(Point point)
{
	std::fstream fout(file_name, std::ios::app);
	fout << COLOR(point.color) << " " << point.row << "," << point.column << std::endl;
	fout.flush();
	fout.close();
}

void output_history_win(Color color)
{
	std::fstream fout(file_name, std::ios::app);
	fout << COLOR_WIN(color) << std::endl;
	fout.flush();
	fout.close();
}

void output()
{
	Color color = state_machine->judge_win();
	if (color == EMPTY)
	{
		std::cout << state_machine->get_next_step()->axis.row << " " << state_machine->get_next_step()->axis.column << std::endl;
		output_history(*state_machine->get_next_step());
	}
	else if (color == my_color)
	{
		std::cout << COLOR_WIN(color) << " " << state_machine->get_next_step()->axis.row << " " << state_machine->get_next_step()->axis.column << std::endl;
		output_history(*state_machine->get_next_step());
		output_history_win(color);
	}
	else
	{
		std::cout << COLOR_WIN(color) << std::endl;
		output_history_win(color);
	}
}

void delete_last_history(int count)
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