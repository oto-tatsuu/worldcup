#pragma once
#include"GameRecord.h"
#include"List.h"
#include<string>
#include<time.h>
#define HOME true
#define AWAY false
using std::string;
enum type { goal, goal_penalty, goal_own, yellowcard, redcard ,non};
enum game_status {not_beginning,in_the_game,completed};
class Match
{
public:
	friend class DataBase;
	class Event
	{
		friend class PlayerEvent;
		friend class Match;
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
		friend class Match;
	private:
		int p_id;
		List<Event>events;
	public:
		PlayerEvent();
		PlayerEvent(PlayerEvent&src);
		PlayerEvent(PlayerEvent&&src);
		~PlayerEvent();
		void AddEvent(Event* event);
		void SetID(int id);
		int GetID();
	};
public:
	Match();
	~Match();
private:
	int home_id;
	int away_id;
	int home_score;
	int away_score;
	int start_time;
	int	time;
	int winner;
	game_status status;
	string home_name;
	string away_name;
	List<PlayerEvent>home_player_events;
	List<PlayerEvent>away_player_events;
	int JudgeWinner();
public:
	void AddPlayer(PlayerEvent * newplayer, bool team);
	void AddEvent(int p_id, Event * event, bool team);
	void Update(time_t now);
	string toString();
};

