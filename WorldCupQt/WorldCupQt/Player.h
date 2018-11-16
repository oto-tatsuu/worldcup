#pragma once
#include<string>
using std::string;
class Player
{
	friend class DataBase;
	struct Goal 
	{
		int shot;
		int penalties;
		Goal() :shot(0), penalties(0) {}
		bool operator <(Goal&&rhs);
		bool operator >(Goal&&rhs);
	};
public:
	Player();
	~Player();
	int GetGoal_num();
	int GetID() { return p_id; };
	Goal GetGoal();
	string GetName();
private:
	bool captain;
	int p_id;
	string name;
	string position;

	Goal goal;
	
};

