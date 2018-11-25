#include "Match.h"



Match::Match():m_id(-1),home_id(-1),away_id(-1),home_score(0),away_score(0),status(not_beginning),winner(-1), home_penalties(0), away_penalties(0)
{
	time = 120 * 60;
}


Match::~Match()
{
	home_player_events.clear();
	away_player_events.clear();
}

int Match::JudgeWinner()
{
	if (home_score > away_score)
		return home_id;
	else if (home_score < away_score)
		return away_id;
	else if (home_penalties > away_penalties)
		return home_id;
	else if (home_penalties < away_penalties)
		return away_id;
	else
		return -1;

}


void Match::AddPlayer(PlayerEvent * newplayer, bool team)
{
	if (team)
		home_player_events.push_back(*newplayer);
	else
		away_player_events.push_back(*newplayer);
}

void Match::AddEvent(int p_id, Event * event, bool team)
{
	List_iter<PlayerEvent>iter;
	List_iter<PlayerEvent>begin, end;
	if (team)
	{
		begin = home_player_events.begin();
		end = home_player_events.end();
	}
	else
	{
		begin = away_player_events.begin();
		end = away_player_events.end();
	}
	for (iter = begin; iter != end; ++iter)
	{
		if ((*iter).p_id == p_id)
		{
			(*iter).AddEvent(event);
		}
	}
	PlayerEvent*p = new PlayerEvent();
	p->p_id = p_id;
	p->AddEvent(event);
	AddPlayer(p, team);

}




int Match::GetID()
{
	return m_id;
}

int Match::GetWinner()
{
	return winner;
}

int Match::GetTeamID(bool t_type)
{
	if (t_type)
		return home_id;
	else
		return away_id;
}

int Match::GetScore(bool t_type)
{
	if (t_type)
		return home_score;
	else
		return away_score;
}

int Match::GetPenalties(bool t_type)
{
	if (t_type)
		return home_penalties;
	else
		return away_penalties;
}



string Match::GetStatus()
{
	switch (status)
	{
		case not_beginning:return "not_beginning";
		case in_the_game:return "in_the_game"; 
		case completed:return "completed";
		default:break;
	}
	return "";
}

game_status Match::GetStatus(int n)
{
	return status;
}
#include<iomanip>
string Match::GetStartTime()
{
		std::ostringstream oss;
		string r;
		tm t;
		localtime_s(&t,&start_time);
		oss << t.tm_year + 1900 << "-" <<t.tm_mon << "-" << t.tm_mday << " " << t.tm_hour << ":" << t.tm_min;
		r = oss.str();
		return r;
}

string Match::GetTeamName(bool t_type)
{
	if (t_type)
		return home_name;
	else
		return away_name;
}

string Match::GetWinnerName()
{
	if (winner == home_id && winner != -1)
		return home_name;
	else if (winner == away_id && winner != -1)
		return away_name;
	else if (winner == -1)
		return "Draw";
}


	

void Match::SetHomeID(int t_id)
{
	home_id = t_id;
}

void Match::SetAwayID(int t_id)
{
	away_id = t_id;
}

void Match::ClearRecord()
{
	home_player_events.clear();
	away_player_events.clear();
	winner = -1;
	home_score = 0;
	away_score = 0; 
	home_card = 0;
	away_card = 0;
	home_penalties = 0;
	away_penalties = 0;
	status = not_beginning;
}


void Match::Update(time_t now)
{
	for (List_iter<PlayerEvent>i= home_player_events.begin();i!=home_player_events.end(); ++i)
	{
		auto p = *i;
		int cnt = 0;
		for (auto j=p.events.begin(); j != (*i).events.end(); ++j) 
		{
			switch ((*j).event_type)
			{
			case goal:case goal_penalty: {home_score++; break; }
			case goal_own: {away_score++; break; }
			case yellowcard:
			{
				if (!cnt) 
				{
					home_card += 1;
					cnt++;
				}
				else home_card += 3;
				break;
			}
			case redcard:
			{
				if (!cnt)home_card += 4;
				else home_card += 5;
				break;
			}
			default:break;
			}
		}
	}
	for (List_iter<PlayerEvent>i = away_player_events.begin(); i != away_player_events.end(); ++i)
	{
		auto p = *i;
		int cnt=0;
		for (auto j = p.events.begin(); j != (*i).events.end(); ++j)
		{
			switch ((*j).event_type)
			{
			case goal:case goal_penalty: {away_score++; break; }
			case goal_own: {home_score++; break; }
			case yellowcard: 
			{
				if (!cnt) 
				{
					away_card += 1; 
					cnt++;
				}
				else away_card += 3;
				break;
			}
			case redcard: 
			{
				if (!cnt)away_card += 4;
				else away_card += 5;
				break;
			}
			default:break;
			}
		}
	}
	if (status == completed)
	{
		winner = JudgeWinner();
	}
	else
		winner = -1;
}

bool Match::HavePenalty()
{
	return status == completed && m_id >= 48 && home_score == away_score;
}

string Match::toString()
{
	string r;
	std::ostringstream oss;
	
	oss << "比赛编号：" << m_id +1<< "\t主队：" << home_name << "\t客队：" << away_name << "\n";
	oss << "比分：\t" << home_score << ":" << away_score<<"\n";
	if (status == completed && m_id >= 48 && home_score == away_score) 
	{
		oss << "点球：\t" << home_penalties << ":" << away_penalties << "\n";
	}
		string win;
	if (status == completed)
	{
		if (winner == home_id&& winner != -1)
			win += "胜者："+home_name;
		else if (winner == away_id&& winner != -1)
			win += "胜者："+away_name;
		else if (winner == -1)
			win = "平局";
	}
	else
	{
		win = "敬请期待";
	}
	oss << "比赛结果:" << win<<"\n";
	if (status != not_beginning) 
	{
		std::ostringstream home, away;
		home << "主队事件:\n";
		away << "客队事件:\n";
		for (auto p_it = home_player_events.begin(); p_it != home_player_events.end(); ++p_it)
		{
			auto play = (*p_it).events;
			for (auto e_it = play.begin(); e_it != play.end(); ++e_it) 
			{
				string eve;
				switch ((*e_it).event_type) 
				{
				case goal:eve = "进球"; break;
				case goal_penalty:eve = "点球"; break; 
				case goal_own:eve = "乌龙"; break;
				case yellowcard:eve = "黄牌"; break; 
				case redcard:eve = "红牌"; break;
				}
				home << (*p_it).p_id << ":" << eve << "\t时间" << (*e_it).time << "min\n";
			}
		}
		for (auto p_it = away_player_events.begin(); p_it != away_player_events.end(); ++p_it)
		{
			auto play = (*p_it).events;
			for (auto e_it = play.begin(); e_it != play.end(); ++e_it)
			{
				string eve;
				switch ((*e_it).event_type)
				{
				case goal:eve = "进球"; break;
				case goal_penalty:eve = "点球"; break;
				case goal_own:eve = "乌龙"; break;
				case yellowcard:eve = "黄牌"; break;
				case redcard:eve = "红牌"; break;
				}
				away << (*p_it).p_id << ":" << eve << "\t时间" << (*e_it).time << "min\n";
			}
		}
		oss << home.str();
		oss << away.str();
	}
	r = oss.str();
	return r;
}

Match::PlayerEvent::PlayerEvent():p_id(-1)
{
}

Match::PlayerEvent::PlayerEvent(PlayerEvent & src)
{
	p_id = src.p_id;
	events = src.events;
}

Match::PlayerEvent::PlayerEvent(PlayerEvent && src)
{
	p_id = src.p_id;
	events = src.events;
}

Match::PlayerEvent::~PlayerEvent()
{
}

void Match::PlayerEvent::AddEvent(Event * event)
{
	if (event->event_type == yellowcard || event->event_type == redcard)
		events.push_back(*event);
	else
		events.push_front(*event);
}

void Match::PlayerEvent::SetID(int id)
{
	p_id = id;
}

int Match::PlayerEvent::GetID()
{
	return p_id;
}

Match::Event::Event():event_type(non)
{
}

Match::Event::~Event()
{
}
void Match::Event::SetTime(int time)
{
	this->time = time;
}
void Match::Event::SetType(type event_type)
{
	this->event_type = event_type;
}

string GetStartTime()
{
	return string();
}
