#include "Player.h"



Player::Player():captain(false),p_id(-1)
{
}


Player::~Player()
{
}

int Player::GetGoal_num()
{
	return goal.shot;
}

int Player::GetPenalty_num()
{
	return goal.penalties;
}



Player::Goal Player::GetGoal()
{
	return goal;
}


string Player::GetName()
{
	return name;
}

bool Player::Goal::operator<(Goal && rhs)
{
	if (shot < rhs.shot)
		return true;
	else if (shot == rhs.shot) 
	{
		if (penalties > rhs.penalties)
			return true;
	}
	return false;
}

bool Player::Goal::operator>(Goal && rhs)
{
	if (shot > rhs.shot)
		return true;
	else if (shot == rhs.shot)
	{
		if (penalties < rhs.penalties)
			return true;
	}
	return false;
}
