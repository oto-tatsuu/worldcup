#include "Match.h"



Match::Match():home_id(-1),away_id(-1),home_score(0),away_score(0),status(not_beginning),winner(-1)
{
	
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
	else return -1;
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

void Match::Update(time_t now)
{
	for (List_iter<PlayerEvent>i= home_player_events.begin();i!=home_player_events.end(); ++i)
	{
		auto p = *i;
		for (auto j=p.events.begin(); j != (*i).events.end(); ++j) 
		{
			switch ((*j).event_type)
			{
			case goal:case goal_penalty: {home_score++; break; }
			case goal_own: {away_score++; break; }
			default:break;
			}
		}
	}
	for (List_iter<PlayerEvent>i = away_player_events.begin(); i != away_player_events.end(); ++i)
	{
		auto p = *i;
		for (auto j = p.events.begin(); j != (*i).events.end(); ++j)
		{
			switch ((*j).event_type)
			{
			case goal:case goal_penalty: {away_score++; break; }
			case goal_own: {home_score++; break; }
			default:break;
			}
		}
	}
	//test
	status = completed;
	if (status == completed)
	{
		winner = JudgeWinner();
	}
	else
		winner = -1;
}

string Match::toString()
{
	string r;
	r += home_name;	
	r += ":";
	r +=std::to_string(home_score);
	r += "\t";
	r += away_name;
	r += ":";
	r += std::to_string(away_score);
	r += "\twinner:";
	r += std::to_string(winner);
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