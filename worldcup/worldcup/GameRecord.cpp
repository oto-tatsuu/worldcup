#include "GameRecord.h"
#if 0
GameRecord::GameRecord()
{
}

GameRecord::~GameRecord()
{
}

void GameRecord::AddPlayer(PlayerEvent * newplayer, bool team)
{
	if (team)
		home_player_events.push_back(*newplayer);
	else
		away_player_events.push_back(*newplayer);
}

void GameRecord::AddEvent(int p_id, Event * event, bool team)
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
	AddPlayer(p,team);
}

PlayerEvent::PlayerEvent()
{
}

PlayerEvent::~PlayerEvent()
{
}

void PlayerEvent::AddEvent(Event * event)
{
	if (event->event_type == yellowcard || event->event_type == redcard)
		events.push_back(*event);
	else
		events.push_front(*event);
}

void PlayerEvent::SetID(int id)
{
	p_id = id;
}

int PlayerEvent::GetID()
{
	return p_id;
}

Event::Event()
{
}

Event::~Event()
{
}
void Event::SetTime(int time)
{
	this->time = time;
}
void Event::SetType(type event_type)
{
	this->event_type = event_type;
}
#endif