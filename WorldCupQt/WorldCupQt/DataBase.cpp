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
	knockout_team = new Team*[16];
	knockout_tree = new KnockOutTree[16];
	ifstream ifs;
	Reader reader;
	Value value;
	ifs.open("info.json");
	bool ok=reader.parse(ifs, value);
	ifs.close();
	if (ok) 
	{
		ReadMatchBaseInfo(value["match"]);
		ReadTeamBaseInfo(value["team"]);
		ReadPlayerBaseIndo(value["player"]);
		CreateGameMap();
		CreateKnockoutTree();
		Update(0,value["match"]);
	}
	
	
}


DataBase::~DataBase()
{
	delete[] team;
	delete[] player;
	delete[] match;
	delete[] knockout_tree;
	sort.DeleteArray(knockout_team,16);
}

Player ** DataBase::GetshoterRank()
{
	return sort.MergeSort(player, &Player::GetGoal, 736);
}

string DataBase::GetTeamName(int t_id)
{
	return team[t_id].name;
}

queue<DataBase::eve_data> DataBase::GetEvents(int m_id, int &cnt, bool t_type)
{
	queue<DataBase::eve_data> r;
	if (t_type)
	{
		for (auto p_it = match[m_id].home_player_events.begin(); p_it != match[m_id].home_player_events.end(); ++p_it)
		{
			auto play = (*p_it).events;
			for (auto e_it = play.begin(); e_it != play.end(); ++e_it)
			{
				eve_data eve;
				switch ((*e_it).event_type)
				{
					case goal:eve.type = "goal"; break;
					case goal_penalty:eve.type = "penalty"; break;
					case goal_own:eve.type = "own"; break;
					case yellowcard:eve.type = "yellow card"; break;
					case redcard:eve.type = "red card"; break;
				}
				int p_id = (*p_it).p_id;
				eve.player = player[p_id].name;
				eve.time = std::to_string((*e_it).time)+"min";
				r.push(eve);
				cnt++;
			}
		}
	}
	else 
	{
		for (auto p_it = match[m_id].away_player_events.begin(); p_it != match[m_id].away_player_events.end(); ++p_it)
		{
			auto play = (*p_it).events;
			for (auto e_it = play.begin(); e_it != play.end(); ++e_it)
			{
				eve_data eve;
				switch ((*e_it).event_type)
				{
					case goal:eve.type = "goal"; break;
					case goal_penalty:eve.type = "penalty"; break;
					case goal_own:eve.type = "own"; break;
					case yellowcard:eve.type = "yellow card"; break;
					case redcard:eve.type = "red card"; break;
				}
				int p_id = (*p_it).p_id;
				eve.player = player[p_id].name;
				eve.time = std::to_string((*e_it).time) + "min";
				r.push(eve);
				cnt++;
			}
		}
	}
	return r;
}

void DataBase::Update(time_t now)
{
	Reader reader;
	Value value;
	ifstream ifs;
	ifs.open("info.json");
	bool ok = reader.parse(ifs,value);
	Value root = value["match"];
	if (ok) 
	{
		ifs.close();
		Update(now, root);
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

void DataBase::CreateKnockoutTree()
{
	for (int i = 0; i < 8; i++) 
	{
		knockout_tree[i].src_from = false;
	}
	knockout_tree[0].home_last_match = 37;
	knockout_tree[0].away_last_match = 39;
	knockout_tree[0].tree = 16;
	knockout_tree[1].home_last_match = 33;
	knockout_tree[1].away_last_match = 35;
	knockout_tree[1].tree = 17;
	knockout_tree[2].home_last_match = 35;
	knockout_tree[2].tree = 18;
	knockout_tree[2].away_last_match = 33;
	knockout_tree[3].home_last_match = 39;
	knockout_tree[3].away_last_match = 37;
	knockout_tree[3].tree = 19;
	knockout_tree[4].home_last_match = 43;
	knockout_tree[4].away_last_match = 41;
	knockout_tree[4].tree = 20;
	knockout_tree[5].home_last_match = 47;
	knockout_tree[5].away_last_match = 45;
	knockout_tree[5].tree = 21;
	knockout_tree[6].home_last_match = 41;
	knockout_tree[6].away_last_match = 43;
	knockout_tree[6].tree = 22;
	knockout_tree[7].home_last_match = 45;
	knockout_tree[7].away_last_match = 47; 
	knockout_tree[7].tree = 23;
	knockout_tree[8].home_last_match = 49;
	knockout_tree[8].away_last_match = 48;
	knockout_tree[8].tree = 24;
	knockout_tree[9].home_last_match = 52;
	knockout_tree[9].away_last_match = 53;
	knockout_tree[9].tree = 25;
	knockout_tree[10].home_last_match = 54;
	knockout_tree[10].away_last_match = 55;
	knockout_tree[10].tree = 26;
	knockout_tree[11].home_last_match = 50;
	knockout_tree[11].away_last_match = 51;
	knockout_tree[11].tree = 27;
	knockout_tree[12].home_last_match = 56;
	knockout_tree[12].away_last_match = 57;
	knockout_tree[12].tree = 28;
	knockout_tree[13].home_last_match = 59;
	knockout_tree[13].away_last_match = 58;
	knockout_tree[13].tree = 29;
	knockout_tree[14].home_last_match = 60;
	knockout_tree[14].away_last_match = 61;
	knockout_tree[14].tree = 31;
	knockout_tree[15].home_last_match = 60;
	knockout_tree[15].away_last_match = 61;
	knockout_tree[15].tree = 30;
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

void DataBase::Update(time_t now, Json::Value & root)
{
	ClearPoint();
	for (int i = 0; i < 736; i++) 
	{
		player[i].goal.shot=0;
		player[i].goal.penalties = 0;
	}
	for (unsigned int i = 0; i < 48; i++)
	{
		match[i].ClearRecord();
		time_t match_start = match[i].start_time;
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
					{
						event->SetType(goal);
						player[p_id].goal.shot++;
					}						
					else if (str == "goal-penalty")
					{
						event->SetType(goal_penalty);
						player[p_id].goal.shot++;
						player[p_id].goal.penalties++;
					}						
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
					{
						event->SetType(goal);
						player[p_id].goal.shot++;
					}						
					else if (str == "goal-penalty")
					{
						event->SetType(goal_penalty);
						player[p_id].goal.shot++;
						player[p_id].goal.penalties++;
					}						
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
		for (int j = 0; j<4; j++)
			UpdateTeam(i * 4 + j);
		Team**tm = sort.InsertSort(&team[i * 4], &Team::GetJudgePoint, 4);
		knockout_team[i * 2] = tm[0];
		knockout_team[i * 2 + 1] = tm[1];
		sort.DeleteArray(tm, 4);
	}
	for (int i = 48; i < 64; i++)
	{
		int j = i - 48;
		match[i].ClearRecord();
		int home_m = knockout_tree[j].home_last_match;
		int away_m = knockout_tree[j].away_last_match;
		int home = -1, away = -1;
		if (match[home_m].status == completed)
		{
			if (knockout_tree[j].src_from)
				switch (i)
				{
				case 62:
					if (match[home_m].home_id == match[home_m].winner)home = match[home_m].away_id;
					else match[home_m].home_id;
					break;
				case 63:home = match[home_m].winner; break;
				default:home = match[home_m].winner;
				}
			else
			{
				int g = match[home_m].home_id / 4;
				home = knockout_team[g * 2]->t_id;
			}
		}
		if (match[away_m].status == completed)
		{
			if (knockout_tree[j].src_from)
				switch (i)
				{
				case 62:away = (match[away_m].home_id == match[away_m].winner) ? match[away_m].away_id : match[away_m].home_id; break;
				case 63:away = match[away_m].winner; break;
				default:away = match[away_m].winner;
				}
			else
			{
				int g = match[away_m].away_id / 4;
				away = knockout_team[g * 2 + 1]->t_id;
			}
		}
		match[i].home_id = home;
		match[i].away_id = away;
		if (home != -1)
			match[i].home_name = team[home].name;
		else
			match[i].home_name = "?";
		if (away != -1)
			match[i].away_name = team[away].name;
		else
			match[i].away_name = "?";
		time_t match_start = match[i].start_time;
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
				match[i].home_penalties = root[i]["home_penalties"].asInt();
				match[i].away_penalties = root[i]["away_penalties"].asInt();
			}
			if (team[home].name != root[i]["home_team_country"].asString() || team[away].name != root[i]["away_team_country"].asString())
				continue;
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
					{
						event->SetType(goal);
						player[p_id].goal.shot++;
					}						
					else if (str == "goal-penalty")
					{
						event->SetType(goal_penalty);
						player[p_id].goal.shot++;
						player[p_id].goal.penalties++;
					}
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
					{
						event->SetType(goal);
						player[p_id].goal.shot++;
					}
					else if (str == "goal-penalty")
					{
						event->SetType(goal_penalty);
						player[p_id].goal.shot++;
						player[p_id].goal.penalties++;
					}
					else if (str == "goal-own")
						event->SetType(goal_own);
					else if (str == "yellow-card")
						event->SetType(yellowcard);
					else if (str == "red-card")
						event->SetType(redcard);
					match[i].AddEvent(p_id, event, AWAY);
				}
			}
			match[i].Update(now);
			if (match[i].status == completed)
			{
				int win = match[i].winner;
			}
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
	if (temp.size() > sz) 
	{
		temp = temp.substr(++sz);
		time.tm_hour = std::stoi(temp, &sz);
		if (temp.size() > sz) 
		{
			temp = temp.substr(++sz);
			time.tm_min = std::stoi(temp, &sz);
			if (temp.size() > sz) 
			{
				temp = temp.substr(++sz);
				time.tm_sec = std::stoi(temp, &sz);
			}
			else 
			{
				time.tm_sec = 0;
			}
		}
		else 
		{
			time.tm_min = time.tm_sec = 0;
		}
	}
	else 
	{
		time.tm_hour = time.tm_min = time.tm_sec = 0;
	}
	return mktime(&time);
}

void DataBase::ReadMatchBaseInfo(Json::Value & m)
{
	for (unsigned int i = 0; i < 64; i++)
	{

		match[i].home_name = m[i]["home_team_country"].asString();
		match[i].away_name =m[i]["away_team_country"].asString();

		match[i].m_id = i;
		match[i].start_time = strTotime(m[i]["datetime"].asString());
	}
}

void DataBase::ReadTeamBaseInfo(Json::Value & t)
{
	for (unsigned int j = 0; j < 32; j++)
	{
		int i = t[j]["id"].asInt() - 1;
		team[i].t_id = i;
		team[i].name = t[j]["country"].asString();
		team[i].group = t[j]["group_id"].asInt() - 1;
	}
}

void DataBase::ReadPlayerBaseIndo(Json::Value & p)
{
	for (unsigned i = 0; i < 736; i++) 
	{
		int p_id = p[i]["id"].asInt();
		player[p_id].captain=p[i]["captain"].asBool();
		player[p_id].p_id = p_id;
		player[p_id].name = p[i]["name"].asString();
		player[p_id].position = p[i]["position"].asString();		
	}
		
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
	for (int i = 0; i < 64; i++) 
	{
		std::cout <<"match_id:"<<i<<"\t"<< match[i].toString()<<std::endl;
	}
}

void DataBase::show_match(int m_id)
{
	
}

void DataBase::show_team()
{
	for (int i = 0; i < 32; i++) 
	{
		std::cout << "team_id:" << team[i].t_id << "\tcountry:" << team[i].name << "\tpoint:"<<team[i].jp.point<<std::endl;
	}
}

int DataBase::GetWin(int t_id)
{
	int i = 0,r = 0;
	for (auto e = gamemap.FirstEdge(t_id);i < 3; ++e) 
	{
		int m = *e;
		if (match[m].winner == t_id)
			r++;
		i++;
	}
	return r;
}

int DataBase::GetLose(int t_id)
{
	int i = 0, r = 0;
	for (auto e = gamemap.FirstEdge(t_id); i < 3; ++e)
	{
		int m = *e;
		if (match[m].winner != t_id&&match[m].winner != -1)
			r++;
		i++;
	}
	return r;
}

int DataBase::GetDraw(int t_id)
{
	int i = 0, r = 0;
	for (auto e = gamemap.FirstEdge(t_id); i < 3; ++e)
	{
		int m = *e;
		if (match[m].winner == -1)
			r++;
		i++;
	}
	return r;
}


Team ** DataBase::GetPointRank(int group)
{
	return sort.InsertSort(team + group * 4, &Team::GetJudgePoint, 4);
}

int DataBase::TreeToMatch(int n)
{
	if (n < 30)
		return n + 32;
	else if (n == 30)
		return 63;
	else if (n == 31)
		return 62;
	else
		return - 1;
}

int DataBase::Predict(int m_id, bool t_type)
{
	int r=-1;
	if (m_id >= 48 && m_id < 56) {
		if (t_type == HOME)
		{
			int m=knockout_tree[m_id - 48].home_last_match;
			int g_id = match[m].home_id / 4;
			Team**t= sort.InsertSort(team + g_id * 4, &Team::GetJudgePoint, 4);
			r = t[0]->t_id;
			sort.DeleteArray(t,4);
			return r;
		}
		else
		{
			int m = knockout_tree[m_id - 48].away_last_match;
			int g_id = match[m].home_id / 4;
			Team**t = sort.InsertSort(team + g_id * 4, &Team::GetJudgePoint, 4);
			r = t[1]->t_id;
			sort.DeleteArray(t, 4);
			return r;
		}
	}
	else
		return r;
}

bool DataBase::TeamDetermined(int m_id, bool t_type)
{
	if (m_id >= 48 && m_id < 56) {
		if (t_type)
		{
			int m = knockout_tree[m_id-48].home_last_match;
			return match[m].status == completed;
		}
		else
		{
			int m = knockout_tree[m_id - 48].away_last_match;
			if (m < 0 || m>63)
				throw std::runtime_error("?");
			return match[m].status == completed;
		}
	}
	return false;
}


DataBase::KnockOutTree::KnockOutTree():src_from(true),home_last_match(-1),away_last_match(-1)
{
}

DataBase::KnockOutTree::~KnockOutTree()
{
}
