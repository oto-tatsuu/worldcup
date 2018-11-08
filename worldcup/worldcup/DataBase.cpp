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
	ReadTeamBaseInfo();
	CreateGameMap();
	//Update(0);
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
		ClearPoint();
		for (unsigned int i = 0; i < 48; i++) 
		{	
			match[i].ClearRecord();
			time_t match_start=match[i].start_time;
			int time = match[i].time;
			if (now < match_start)
			{
				match[i].status = not_beginning;
				continue;
			}
			else 
			{
				if (now < match_start + time)
				{
					match[i].status = in_the_game;
				}
				else 
				{
					match[i].status = completed;
				}
				for (unsigned int j = 0; !root[i]["home_team_events"][j].empty(); j++)
				{
					int p_id = root[i]["home_team_events"][j]["id"].asInt();
					int event_time = root[i]["home_team_events"][j]["time"].asInt();
					if (now < match_start + event_time * 60)
						continue;
					else 
					{
						Match::Event *event = new Match::Event();
						event->SetTime(event_time);
						string str = root[i]["home_team_events"][j]["type_of_event"].asString();
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
						match[i].AddEvent(p_id, event, HOME);
					}						
				}
				for (unsigned int j = 0; !root[i]["away_team_events"][j].empty(); j++)
				{
					int p_id = root[i]["away_team_events"][j]["id"].asInt();
					int event_time = root[i]["away_team_events"][j]["time"].asInt();
					if (now < match_start + event_time * 60)
						continue;
					else 
					{
						Match::Event *event = new Match::Event();
						event->SetTime(event_time);
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
				}
			}
			match[i].Update(now);			
		}
		for (int i = 0; i < 8; i++) 
		{
			for(int j=0;j<4;j++)
			UpdateTeam(i*4+j);			
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
				match[i].match_id = i;
				match[i].home_name = Match[i]["home_team_country"].asString();
				match[i].away_name = Match[i]["away_team_country"].asString();
				match[i].start_time = strTotime(Match[i]["datetime"].asString());
			}
		}
	}
}

void DataBase::ReadTeamBaseInfo()
{
	Reader reader;
	Value tm;
	ifstream ifs;
	ifs.open("team.json");
	bool a = reader.parse(ifs, tm);
	if (a) 
	{
		ifs.close();
		for (unsigned int j = 0; j < 32; j++) 
		{
			int i= tm[j]["id"].asInt() - 1;
			team[i].t_id=i;
			team[i].name=tm[j]["country"].asString();
			team[i].group=tm[j]["group_id"].asInt()-1;
		}
	}
}

void DataBase::CreateGameMap()
{
	for (int i = 0; i < 32; i++) 
	{
		gamemap.AddVertice(i);
	}
		for (unsigned int i = 0; i < 48; i++)
		{
			int home, away;
			for (unsigned int j = 0; j < 32; j++)
			{

				if (team[j].name == match[i].home_name)
					home = team[j].t_id;
				if (team[j].name == match[i].away_name)
					away = team[j].t_id;
			}
			AddGame(home, away, i);
		}	
}

void DataBase::UpdateTeam(int t_id)
{
	int lose_goal = 0, goal = 0, card=0,m=0;
	for (Edge<int>edge = gamemap.FirstEdge(t_id); m<3; ++edge,m++) 
	{
		Match*m=&match[*edge];
		if (m->status == completed)
		{
			if (m->winner == -1)
				team[t_id].jp.point += 1;
			else 
			{
				if(t_id==m->winner)
					team[t_id].jp.point += 3;
				else
					team[t_id].jp.point += 0;
			}
			if (t_id == m->home_id)
			{
				goal += m->home_score;
				lose_goal += m->away_score;
				card += m->home_card;
			}
			else if (t_id == m->away_id) 
			{
				goal += m->away_score;
				lose_goal += m->home_score;
				card += m->away_card;
			}
		}		
		m = nullptr;
	}
	team[t_id].jp.net_victory=goal-lose_goal;
	team[t_id].jp.total_goal=goal;
	team[t_id].jp.card = card;
}



void DataBase::ClearPoint()
{
	for(int i=0;i<32;i++)
	team[i].jp.point = 0;
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

void DataBase::show_team()
{
	for (int i = 0; i < 32; i++) 
	{
		std::cout << "team_id:" << team[i].t_id << "\tcountry:" << team[i].name << "\tpoint:"<<team[i].jp.point<<std::endl;
	}
}

Team ** DataBase::GetPointRank(int group)
{
	Team** point_rank=sort.InsertSort(team+group * 4, &Team::GetJudgePoint,4);
	return point_rank;
}
