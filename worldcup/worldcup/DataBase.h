#pragma once
#include"Map.h"
#include"Team.h"
#include"Match.h"
#include<time.h>
#include<queue>
#include"Player.h"
#include"Algorithm.h"
using std::queue;
class DataBase
{
public:
	DataBase();
	~DataBase();
	//射手榜
public:
	int*GetshoterRank();//
private:
	int Getshot(int p_id);//获取球员射门数
public:
	//积分榜
	int GetPoint(int t_id);//获得某国家积分
	Team** GetPointRank(int group);//获得某小组积分排名
	//比赛结果
public:
	int GetMatch(int t_id,int n);//获得某国家第n场比赛id
	int GetHomeTeam(int m_id);
	int GeVisitingTeam(int m_id);
	//UI接口
public:
	void Update(time_t now);
	time_t strTotime(string str);
private:
	void ReadMatchBaseInfo();
	void ReadTeamBaseInfo();
	void CreateGameMap();
	void UpdateTeam(int t_id);
	void ClearPoint();
	void AddGame(int home, int away, int num);

private:
public:
	Map<int,int> gamemap;//小组赛
	queue<int> knockour;//淘汰赛
	Team*team;//[]参赛的全部球队32
	Player*player;//[]参赛的全部球员32*23
	Match*match;//[]所有比赛64
	Algorithm sort;
public:
	//test
	void show_gamemap();
	void show_match_result();
	void show_team();
};

