#pragma once
#include"Map.h"
#include"Team.h"
#include"Match.h"
#include<time.h>
#include<queue>
#include"Player.h"
#define GROUP_A -1
#define GROUP_B 3
#define GROUP_C 7
#define GROUP_D 11
#define GROUP_E 15
#define GROUP_F 19
#define GROUP_G 23
#define GROUP_H 27
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
	int* GetPointRank(int group);//获得某小组积分排名
	//比赛结果
public:
	int GetMatch(int t_id,int n);//获得某国家第n场比赛id
	tm GetMatchStartTime(int m_id);//获得比赛开始时间
	int GetHomeTeam(int m_id);
	int GeVisitingTeam(int m_id);
	void SetHomeTeam(int m_id,int t_id);
	void SetVisitingTeam(int m_id,int t_id);
	//UI接口
public:
	void Update(time_t now);
private:
	void ReadMatchBaseInfo();
	void CreateGameMap();
	time_t strTotime(string str);
	void AddGame(int home, int away, int num);
//private:
private:
	Map<int,int> gamemap;//小组赛
	queue<int> knockour;//淘汰赛
	Team*team;//[]参赛的全部球队32
	Player*player;//[]参赛的全部球员32*23
	Match*match;//[]所有比赛64
	Match * latest_match;//最后一场已发生的比赛
public:
	//test
	void show_gamemap();
	void show_match_result();
};

