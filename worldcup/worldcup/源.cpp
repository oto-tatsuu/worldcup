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
	std::cout << "输入时间:";
	string str="2018-7-16";
	//std::cin >> str;
	time_t time = d.strTotime(str);
	d.Update(time);
	bool out = false;
	while (true) 
	{
		std::cout << "输入0退出，1积分榜，2射手榜，3比赛信息";
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
						std::cout << "积分：" << t[j]->GetJudgePoint().point << "\t胜："<<win << "\t负："<<lose << "平："<<draw << std::endl;
					}
					d.sort.DeleteArray(t, 4);
				}
				break;
			}
			case 2: 
			{
				Player**p = d.GetshoterRank();
				for (int i = 0; i < 50; i++)
				{
					int t_id = p[i]->GetID()/23;
					std::cout << p[i]->GetName() << ":" <<  std::endl;
					std::cout << "球队：\t" << d.team[t_id].GetID()<<"\t编号：\t"<< p[i]->GetID() % 23<<"\t射门:\t"<<p[i]->GetGoal_num()<<std::endl;
				
				}
				d.sort.DeleteArray(p, 736);
				break;
			}
			case 3:
			{
				/*for (int i = 0; i < 64; i++) 
				{
					int home = d.match[i].GetTeamID(HOME);
					int away = d.match[i].GetTeamID(AWAY);
					std::cout <<"编号：" << i+1<<"\t状态："<<d.match[i].GetStatus() <<std::endl;
					std::cout << "主队：" << d.team[home].GetName() << std::endl;
					std::cout << "客队：" << d.team[away].GetName() << std::endl;
					std::cout << "比分：" << d.match[i].GetScore(HOME)<<":"<< d.match[i].GetScore(AWAY)<<"\n" << std::endl;
				}*/
				std::cout << "输入0退出，输入比赛编号查看详细信息";
				int b;
				std::cin >> b;
				if (b) 
				{
					std::cout<<d.match[b-1].toString();
				}
				else
				{
					break;
				}
				break;
			}
			default:break;
		}
		if (out)break;
	}
	
	

	system("pause");
	
	
}





