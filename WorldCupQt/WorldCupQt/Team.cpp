#include "Team.h"



Team::Team()
{
}


Team::~Team()
{
}

Team::JudgePoint Team::GetJudgePoint()
{
	return jp;
}

string Team::GetName()
{
	return name;
}

void Team::SetName(string name)
{
	this->name = name;
}


