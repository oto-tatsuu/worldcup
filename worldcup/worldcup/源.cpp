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
//int main()
//{
//	//const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";
//
//	Json::Value jsonRoot;
//	Json::Value wroot;
//	Value jteam;
//	ifstream ifs; //标准输入流
//	ifs.open("wc.json");
//	jsonRoot.clear();
//	
//	Json::Reader reader;
//	
//	bool a = reader.parse(ifs,jsonRoot);
//	ifs.close();
//	ifs.open("team.json");
//	a = a & reader.parse(ifs, jteam);
//	if (a) //从ifs中读取数据到jsonRoot
//	{
//		for (uint16_t i = 0; i < 64; i++) 
//		{
//			Value game_events;
//			uint16_t j = 0;
//			while (!jsonRoot[i]["home_team_events"][j].empty())
//			{
//				int t_id;
//				for (uint16_t k = 0; k < 32; k++)
//				{
//					if (jteam[k]["country"].asString() == jsonRoot[i]["home_team_country"].asString())
//					{
//						t_id = jteam[k]["id"].asInt();
//					}
//				}
//				string name = jsonRoot[i]["home_team_events"][j]["player"].asString();
//				int s_n;
//				for (uint16_t k = 0; k < 11; k++) 
//				{
//					if (name == jsonRoot[i]["home_team_statistics"]["starting_eleven"][k]["name"].asString())
//						s_n = jsonRoot[i]["home_team_statistics"]["starting_eleven"][k]["shirt_number"].asInt();
//				}
//				for (uint16_t k = 0; k < 12; k++)
//				{
//					if (name == jsonRoot[i]["home_team_statistics"]["substitutes"][k]["name"].asString())
//						s_n = jsonRoot[i]["home_team_statistics"]["substitutes"][k]["shirt_number"].asInt();
//				}
//				jsonRoot[i]["home_team_events"][j]["id"] = (t_id - 1) * 23 + (s_n - 1);
//				j++;
//			}
//			j = 0;
//			while (!jsonRoot[i]["away_team_events"][j].empty())
//			{
//				int t_id;
//				for (uint16_t k = 0; k < 32; k++)
//				{
//					if (jteam[k]["country"].asString() == jsonRoot[i]["away_team_country"].asString())
//					{
//						t_id = jteam[k]["id"].asInt();
//					}
//				}
//				string name = jsonRoot[i]["away_team_events"][j]["player"].asString();
//				int s_n;
//				for (uint16_t k = 0; k < 11; k++)
//				{
//					if (name == jsonRoot[i]["away_team_statistics"]["starting_eleven"][k]["name"].asString())
//					{
//						s_n = jsonRoot[i]["away_team_statistics"]["starting_eleven"][k]["shirt_number"].asInt();
//						break;
//					}
//						
//				}
//				for (uint16_t k = 0; k < 12; k++)
//				{
//					string str = jsonRoot[i]["away_team_statistics"]["substitutes"][k]["name"].asString();
//					if (name == str) 
//					{
//						s_n = jsonRoot[i]["away_team_statistics"]["substitutes"][k]["shirt_number"].asInt();
//						break;
//					}
//						
//				}
//				jsonRoot[i]["away_team_events"][j]["id"] = (t_id - 1) * 23 + (s_n - 1);
//				j++;
//			}
//			game_events["home_team_events"]= jsonRoot[i]["home_team_events"];
//			game_events["away_team_events"]= jsonRoot[i]["away_team_events"];
//			wroot.append(game_events);
//		}
//	}
//	std::ofstream fcout;
//	Json::StyledWriter sw;
//	fcout.open("record.json");
//	std::cout << "start write";
//	fcout << sw.write(wroot);
//	fcout.close();
//	return 0;
//}
//
//int main() 
//{
//	Value root;
//	Json::Reader reader;
//	ifstream ifs;
//	ifs.open("rec2.json");
//	bool a = reader.parse(ifs, root);
//	ifs.close();
//	if (a) 
//	{
//		GameRecord r;
//		for (unsigned int i = 0; !root[(unsigned int)0]["home_team_events"][i].empty(); i++)
//		{
//			int p_id = root[(unsigned int)0]["home_team_events"][i]["id"].asInt();
//			Event *event = new Event();
//			event->SetTime( root[(unsigned int)0]["home_team_events"][i]["time"].asInt());
//			string str = root[(unsigned int)0]["home_team_events"][i]["type_of_event"].asString();
//			if (str == "goal")
//				event->SetType(goal);
//			else if (str == "goal-penalty")
//				event->SetType(goal_penalty);
//			else if (str == "goal-own")
//				event->SetType(goal_own);
//			else if(str == "yellow-card")
//				event->SetType(yellowcard);
//			else if (str == "red-card")
//				event->SetType(redcard);
//			r.AddEvent(p_id, event, HOME);
//		}
//		for (unsigned int i = 0; !root[(unsigned int)0]["away_team_events"][i].empty(); i++)
//		{
//			int p_id = root[(unsigned int)0]["away_team_events"][i]["id"].asInt();
//			Event *event = new Event();
//			event->SetTime(root[(unsigned int)0]["away_team_events"][i]["time"].asInt());
//			string str = root[(unsigned int)0]["away_team_events"][i]["type_of_event"].asString();
//			if (str == "goal")
//				event->SetType(goal);
//			else if (str == "goal-penalty")
//				event->SetType(goal_penalty);
//			else if (str == "goal-own")
//				event->SetType(goal_own);
//			else if (str == "yellow-card")
//				event->SetType(yellowcard);
//			else if (str == "red-card")
//				event->SetType(redcard);
//			r.AddEvent(p_id, event, AWAY);
//		}
//	}
//	return 0;
//}
//int strTotime(string str);
//int main() 
//{
//	
//		
//		Value root;
//		Json::Reader reader;
//		ifstream ifs;
//		ifs.open("rec2.json");
//		bool a = reader.parse(ifs, root);
//		ifs.close();
//		if (a)
//		{
//			for (uint16_t i = 1; i < 64; i++)
//						{
//							for (unsigned int j = 0; !root[i]["home_team_events"][j].empty(); j++) 
//							{
//								string str = root[i]["home_team_events"][j]["time"].asString();
//								Value a = strTotime(str);
//								root[i]["home_team_events"][j]["time"] = a;
//							}
//							for (unsigned int j = 0; !root[i]["away_team_events"][j].empty(); j++)
//							{
//								string str = root[i]["away_team_events"][j]["time"].asString();
//								Value a = strTotime(str);
//								root[i]["away_team_events"][j]["time"] = a;
//							}
//						}
//		}
//		std::ofstream fcout;
//			Json::StyledWriter sw;
//			fcout.open("record2.json");
//			std::cout << "start write";
//			fcout << sw.write(root);
//			fcout.close();

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
	d.Update(d.match[63].GetStartTime()+10000);
	//d.show_match_result();
	//d.show_team();
	Player**p=d.GetshoterRank();
	for (int i = 0; i < 736; i++) 
	{
		std::cout << p[i]->GetName() << ":" << p[i]->GetGoal_num() << std::endl;
	}
	d.sort.DeleteArray(p,736);
	/*for (int i = 0; i < 8; i++) 
	{
		Team**point_rank = d.GetPointRank(i);
		char c = 'A';
		c += i;
		std::cout << "group:" << c << std::endl;
		for (int j = 0; j < 4; j++)
		{
			std::cout<<j<<":"<< point_rank[j]->GetName()<< point_rank[j]->GetJudgePoint().point<<std::endl;
		}
	}*/

	system("pause");
	
	
}




B::B()
{
}
