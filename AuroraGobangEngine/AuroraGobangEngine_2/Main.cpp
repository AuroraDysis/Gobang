// AuroraGobangEngine_2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AutoMachine.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


std::shared_ptr<AutoMachine> autoMachine;
std::string fileName;
bool isHistory = false;

void inputChess();
void outputHistory(Point point);
void outputHistoryWin(Color color);
void output();
void deleteLastHistory(int count);

int _tmain(int argc, _TCHAR* argv[])
{
	//输入自己的颜色
	std::string strMColor;
	do	{
		std::cin >> strMColor;
	} while (strMColor != "Black" && strMColor != "White");
	Color color = strMColor == "Black" ? Black : White;

	//利用获得的自己的颜色初始化自动机
	autoMachine = std::make_shared<AutoMachine>(color);

	//输入是否记录历史
	std::string outputHistory;
	do	{
		std::cin >> outputHistory;
	} while (outputHistory != "True" && outputHistory != "False");
	isHistory = outputHistory == "True" ? true : false;

	//如果记录历史则找到文件名
	if (isHistory)
	{
		int count = 0;
		while (++count)
		{
			std::fstream file;
			std::stringstream ss;
			ss << "history" << count << ".txt";
			file.open(ss.str());
			if (!file)
			{
				fileName = ss.str();
				break;
			}
		}
	}

	//如果是黑棋则先输出下一步
	if (color == Black)
		output();

	do
	{
		inputChess();
		output();
	} while (autoMachine->JudgeWin() == Empty);


	return 0;
}

void inputChess()
{
	std::string input;
	while (true)
	{
		std::cin >> input;
		if (input == "UNDO")
		{
			int count = autoMachine->UndoInputAxis();
			std::cout << count << std::endl;
			if (isHistory)
			{
				deleteLastHistory(count);
			}
			continue;
		}
		int x = -1, y = -1;
		std::stringstream ss;
		ss << input;
		ss >> x;
		std::cin >> y;
		if (x < 0 || y < 0 || x >= range || y >= range)
			continue;
		autoMachine->InputAxis(x, y);
		if (isHistory)
		{
			outputHistory(*(autoMachine->GetPoint(x, y)));
		}
		break;
	}
}

void outputHistory(Point point)
{
	std::fstream fout(fileName, std::ios::app);
	fout << (point.PointColor == Black ? "Black" : "White") << " " << point.Axis.row << "," << point.Axis.column << std::endl;
	fout.flush();
	fout.close();
}

void outputHistoryWin(Color color)
{
	std::fstream fout(fileName, std::ios::app);
	fout << (color == Black ? "Black" : "White") << " Win" << std::endl;
	fout.flush();
	fout.close();
}

void output()
{
	Color color = autoMachine->JudgeWin();
	if (color == Empty)
	{
		std::cout << autoMachine->NextStep->Axis.row << " " << autoMachine->NextStep->Axis.column << std::endl;
		outputHistory(*autoMachine->NextStep);
	}
	else if (color == autoMachine->MColor)
	{
		std::cout << (color == Black ? "BlackWin" : "WhiteWin") << " " << autoMachine->NextStep->Axis.row << " " << autoMachine->NextStep->Axis.column << std::endl;
		outputHistory(*autoMachine->NextStep);
		outputHistoryWin(color);
	}
	else
	{
		std::cout << (color == Black ? "BlackWin" : "WhiteWin") << std::endl;
		outputHistoryWin(color);
	}
}

void deleteLastHistory(int count)
{
	std::fstream fin(fileName, std::ios::in);
	int lineCount = 0;
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(fin, line))
	{
		lines.push_back(line);
		lineCount++;
	}
	for (int i = 0; i < count; i++)
		lines.erase(lines.end() - 1);

	std::fstream fout(fileName, std::ios::out);
	for (auto _line : lines)
		fout << _line << std::endl;
	fout.flush();
	fout.close();
}