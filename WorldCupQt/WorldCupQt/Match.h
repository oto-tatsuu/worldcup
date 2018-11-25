#pragma once
#include"List.h"
#include<string>
#include<sstream>
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
		friend class DataBase;
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
		friend class DataBase;
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
	int m_id;
	int home_id;
	int away_id;
	string home_name;
	string away_name;
	time_t start_time;
	unsigned int time;

	int home_score;
	int away_score;
	int home_penalties;
	int away_penalties;
	int home_card;
	int away_card;
	int winner;
	game_status status;
	List<PlayerEvent>home_player_events;
	List<PlayerEvent>away_player_events;
private:
	int JudgeWinner();
public:
	void AddPlayer(PlayerEvent * newplayer, bool team);
	void AddEvent(int p_id, Event * event, bool team);
	int GetID();
	int GetWinner();
	int GetTeamID(bool t_type);
	int GetScore(bool t_type);
	int GetPenalties(bool t_type);
	string GetStatus();
	game_status  GetStatus(int n);
	string GetStartTime();
	string GetTeamName(bool t_type);
	string GetWinnerName();
	void SetHomeID(int t_id);
	void SetAwayID(int t_id);
	void ClearRecord();
	void Update(time_t now);
	bool HavePenalty();
	string toString();
};

