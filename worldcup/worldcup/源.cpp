#pragma  comment(lib, "json_vc71_libmtd.lib")

#include<iostream>
#include<list>

#include"List.h"
#include<string>
#include"json/json.h"
#include<fstream>
#include"time.h"
#include"GameRecord.h"
#include"DataBase.h"
#include"Map.h"
#include"Algorithm.h"
using std::ifstream;
using std::ofstream;
using Json::Value;
using Json::Reader;
using Json::Writer;
using std::string;

int main()
{
	DataBase d;
	std::cout << "����ʱ��:";
	string str;
	std::cin >> str;
	time_t time = d.strTotime(str);
	d.Update(time);
	bool out = false;
	while (true) 
	{
		std::cout << "����0�˳���1���ְ�2���ְ�3������Ϣ";
		int a;
		std::cin >> a;
		switch (a)
		{
			case 0: {out = true; break; }
			case 1: 
			{
				for (int i = 0; i < 8; i++)
				{
					Team**t = d.GetPointRank(i);
					char c = 'A';
					c += i;
					std::cout << "group:" << c << std::endl;
					for (int j = 0; j < 4; j++)
					{
						int t_id = t[j]->GetID();
						int win = d.GetWin(t_id);
						int lose = d.GetLose(t_id);
						int draw = d.GetDraw(t_id);
						std::cout << j << ":" << t[j]->GetName() <<  std::endl;
						std::cout << "���֣�" << t[j]->GetJudgePoint().point << "\tʤ��"<<win << "\t����"<<lose << "ƽ��"<<draw << std::endl;
					}
					d.sort.DeleteArray(t, 4);
				}
			}
		}
		if (out)break;
	}
	Player**p=d.GetshoterRank();
	for (int i = 0; i < 736; i++) 
	{
		std::cout << p[i]->GetName() << ":" << p[i]->GetGoal_num() << std::endl;
	}
	d.sort.DeleteArray(p,736);
	

	system("pause");
	
	
}





