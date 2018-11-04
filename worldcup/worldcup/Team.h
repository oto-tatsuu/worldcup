#pragma once
#include<string>
using std::string;
class Team
{
	struct JudgePoint 
	{
		int point;//����
		int net_victory;//��ʤ��
		int total_goal;//�ܽ���
		int card;//�����
		bool operator <(JudgePoint&&rhs) 
		{
			if (point < rhs.point)
				return true;
			else if (point == rhs.point)
			{
				if (net_victory < rhs.net_victory)
					return true;
				else if (net_victory == rhs.net_victory)
				{
					if (total_goal < rhs.total_goal)
						return true;
					else if (total_goal == rhs.total_goal)
					{
						if (card > rhs.card)
							return true;
					}
				}
			}
			return false;
		}
		bool operator >(JudgePoint&&rhs)
		{
			if (point > rhs.point)
				return true;
			else if (point == rhs.point)
			{
				if (net_victory > rhs.net_victory)
					return true;
				else if (net_victory == rhs.net_victory)
				{
					if (total_goal > rhs.total_goal)
						return true;
					else if (total_goal == rhs.total_goal)
					{
						if (card < rhs.card)
							return true;
					}
				}
			}
			return false;
		}
	};
	friend class DataBase;
public:
	Team();
	~Team();
	JudgePoint GetJudgePoint();
	string GetName();
	void SetName(string name);
private:
	string name;
	int t_id;
	int group;

	JudgePoint jp;
};

