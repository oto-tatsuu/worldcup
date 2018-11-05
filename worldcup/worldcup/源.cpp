#pragma  comment(lib, "json_vc71_libmtd.lib")

#include<iostream>
#include<list>
#include"Team.h"
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
class B 
{
public:
	B();
	
private:
	int b;
public:
	int get() { return b; }
	void set(int d) { b = d; }
};
int main()
{
	DataBase d;
	std::cout << "输入时间";
	string str;
	std::cin >> str;
	time_t time = d.strTotime(str);
	d.Update(time);
	bool out = false;
	while (true) 
	{

		std::cout << "输入0退出，1积分榜，2射手榜，3比赛结果";
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
						
						int t_id =t[j]->GetID();
						int win = d.GetWin(t_id);
						int lose = d.GetLose(t_id);
						int draw = d.GetDraw(t_id);
						std::cout << j << ":" << t[j]->GetName() <<  std::endl;
						std::cout << "积分：" << t[j]->GetJudgePoint().point << "\t胜：" << win << "\t负：" << lose << "\t平：" << draw << std::endl;
					}
					d.sort.DeleteArray(t, 4);
				}
				break;
			}
			case 2: 
			{
				Player**p = d.GetshoterRank();
			}
		}
			if (out)break;
	}
	
	
	system("pause");
	
}




B::B()
{
}
