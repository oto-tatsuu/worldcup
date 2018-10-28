#if 0
#ifndef GAMERECORD_H
#define GAMERECORD_H
#include"List.h"
#define HOME true
#define AWAY false
enum type {goal,goal_penalty,goal_own,yellowcard,redcard};
using std::wstring;
class Event
{
	friend class GameRecord;
	friend class PlayerEvent;
public:
	Event();
	~Event();
	void SetTime(int time);
	void SetType(type event_type);
private:
	int time;
	type event_type;
};

class PlayerEvent
{
	friend class GameRecord;
private:
	int p_id;
	List<Event>events;
public:
	PlayerEvent();
	~PlayerEvent();
	void AddEvent(Event* event);
	void SetID(int id);
	int GetID();
};

class GameRecord
{
public:
	GameRecord();
	~GameRecord();
private:
	List<PlayerEvent>home_player_events;
	List<PlayerEvent>away_player_events;

public:	
	void AddEvent(int p_id,Event* event,bool team);
private:
	void AddPlayer(PlayerEvent* newplayer,bool team);
};


#endif // GAMERECORD_H
#endif