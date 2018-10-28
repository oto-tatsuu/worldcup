#include "DataBase.h"
#include"json/json.h"
#include<fstream>
using std::ifstream;
using Json::Reader;
using Json::Value;


DataBase::DataBase():gamemap(32)
{
	team = new Team[32];
	player = new Player[32 * 23];
	match = new Match[64];
	ReadMatchBaseInfo();
	CreateGameMap();
	Update(0);
}


DataBase::~DataBase()
{
	delete[] team;
	delete[] player;
	delete[] match;
}

void DataBase::Update(time_t now)
{
	Reader reader;
	Value root;
	ifstream ifs;
	ifs.open("record2.json");
	bool ok = reader.parse(ifs,root);
	if (ok) 
	{
		ifs.close();
		for (unsigned int i = 0; i < 48; i++) 
		{
			for (unsigned int j = 0; !root[i]["home_team_events"][j].empty(); j++)
			{
				int p_id = root[i]["home_team_events"][j]["id"].asInt();
				Match::Event *event = new Match::Event();
				event->SetTime( root[i]["home_team_events"][j]["time"].asInt());
				string str = root[i]["home_team_events"][j]["type_of_event"].asString();
				if (str == "goal") 
					event->SetType(goal);				
				else if (str == "goal-penalty")
					event->SetType(goal_penalty);				
				else if (str == "goal-own")
					event->SetType(goal_own);
				else if(str == "yellow-card")
					event->SetType(yellowcard);
				else if (str == "red-card")
					event->SetType(redcard);
				match[i].AddEvent(p_id, event, HOME);
			}
			for (unsigned int j = 0; !root[i]["away_team_events"][j].empty(); j++)
			{
				int p_id = root[i]["away_team_events"][j]["id"].asInt();
				Match::Event *event = new Match::Event();
				event->SetTime(root[i]["away_team_events"][j]["time"].asInt());
				string str = root[i]["away_team_events"][j]["type_of_event"].asString();
				if (str == "goal")
					event->SetType(goal);
				else if (str == "goal-penalty")
					event->SetType(goal_penalty);		
				else if (str == "goal-own") 
					event->SetType(goal_own);		
				else if (str == "yellow-card")
					event->SetType(yellowcard);
				else if (str == "red-card")
					event->SetType(redcard);
				match[i].AddEvent(p_id, event, AWAY);
			}
			match[i].Update(now);
		}
	}
}

void DataBase::ReadMatchBaseInfo()
{
	Reader reader;
	Value Match;
	ifstream ifs;
	ifs.open("match_info.json");
	bool a = reader.parse(ifs, Match);
	if (a) 
	{
		for (unsigned int i = 0; i < 64; i++) 
		{
			if (i < 48) 
			{
				match[i].home_name = Match[i]["home_team_country"].asString();
				match[i].away_name = Match[i]["away_team_country"].asString();
			}
		}
	}
}

void DataBase::CreateGameMap()
{
	for (int i = 0; i < 32; i++) 
	{
		gamemap.AddVertice(i);
	}
	Reader reader;
	Value team;
	ifstream ifs;
	ifs.open("team.json");
	bool a=reader.parse(ifs,team);
	if (a)
	{
		ifs.close();
		for (unsigned int i = 0; i < 48; i++)
		{
			int home, away;
			for (unsigned int j = 0; j < 32; j++)
			{
				if (team[j]["country"].asString() == match[i].home_name)
					home = team[j]["id"].asInt() - 1;
				if (team[j]["country"].asString() == match[i].away_name)
					away = team[j]["id"].asInt() - 1;
			}
			AddGame(home, away, i);
		}
	}	
}

time_t DataBase::strTotime(string str)
{
	tm time;
	string temp;
	string::size_type sz;
	time.tm_year = std::stoi(str, &sz) - 1900;
	temp = str.substr(++sz);
	time.tm_mon = std::stoi(temp, &sz);
	temp = temp.substr(++sz);
	time.tm_mday = std::stoi(temp, &sz);
	temp = temp.substr(++sz);
	time.tm_hour = std::stoi(temp, &sz);
	temp = temp.substr(++sz);
	time.tm_min = std::stoi(temp, &sz);
	temp = temp.substr(++sz);
	time.tm_sec = std::stoi(temp, &sz);
	return mktime(&time);
}

void DataBase::AddGame(int home, int away, int num)
{
	gamemap.AddEdge(home, away, num);
	gamemap.AddEdge(away, home, num);
	match[num].home_id = home;
	match[num].away_id = away;
}

void DataBase::show_gamemap()
{
	for (int i = 0; i < 32; i++) 
	{
		for (Edge<int> e = gamemap.FirstEdge(i); !e.empty(); ++e) 
		{
			std::cout << "team1:" << e.from <<" \tteam2:" << e.to<<" \tM_ID:"<<*e<< std::endl;
		}
	}
	
}

void DataBase::show_match_result()
{
	for (int i = 0; i < 48; i++) 
	{
		std::cout <<"match_id:"<<i<<"\t"<< match[i].toString()<<std::endl;
	}
}
