// AuroraGobangEngine_2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "AutoMachine.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


std::shared_ptr<AutoMachine> autoMachine;
std::string fileName;

void inputChess();
void outputHistory(Point point);
void outputHistoryWin(Color color);
void output();
void deleteLastHistory(int count);

int _tmain(int argc, _TCHAR* argv[])
{
	//�����Լ�����ɫ
	std::string strMColor;
	do	{
		std::cin >> strMColor;
	} while (strMColor != "Black" && strMColor != "White");
	Color color = strMColor == "Black" ? Black : White;

	//���û�õ��Լ�����ɫ��ʼ���Զ���
	autoMachine = std::make_shared<AutoMachine>(color);

	//�����Ƿ��¼��ʷ
	std::string outputHistory;
	do	{
		std::cin >> outputHistory;
	} while (outputHistory != "True" && outputHistory != "False");
	bool isHistory = outputHistory == "True" ? true : false;

	//�����¼��ʷ���ҵ��ļ���
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

	//����Ǻ������������һ��
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
	std::cin >> input;
	while (true)
	{
		if (input == "Undo")
			deleteLastHistory(autoMachine->UndoInputAxis());
		int x = -1, y = -1;
		std::stringstream ss;
		ss << input;
		ss >> x;
		std::cin >> y;
		if (x < 0 || y < 0 || x >= range || y >= range)
			continue;
		autoMachine->InputAxis(x, y);
		break;
	}
}

void outputHistory(Point point)
{
	std::fstream fout(fileName, std::ios::app);
	fout << (point.PointColor == Black ? "Black" : "White") << " " << point.Axis.row << "," << point.Axis.column;
	fout.flush();
	fout.close();
}

void outputHistoryWin(Color color)
{
	std::fstream fout(fileName, std::ios::app);
	fout << (color == Black ? "Black" : "White") << " Win";
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
		std::cout << (color == Black ? "BlackWin" : "WhiteWin") << autoMachine->NextStep->Axis.row << " " << autoMachine->NextStep->Axis.column << std::endl;
		outputHistory(*autoMachine->NextStep);
		outputHistoryWin(color);
	}
	else
	{
		std::cout << (color == Black ? "BlackWin" : "WhiteWin");
		outputHistoryWin(color);
	}
}

void deleteLastHistory(int count)
{
	std::fstream fin(fileName, std::ios::in);
	std::string result;
	int lineCount = 0;
	std::string line;
	while (std::getline(fin, line))
	{
		result += line;
		lineCount++;
	}
	result.replace(result.begin() + result.find_last_of('\n'), result.end(), "");
	result.replace(result.begin() + result.find_last_of('\n'), result.end(), "");
	fin.close();

	std::fstream fout(fileName, std::ios::out);
	fout << result;
	fout.flush();
	fout.close();
}