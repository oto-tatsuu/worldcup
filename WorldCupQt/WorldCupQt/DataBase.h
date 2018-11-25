#pragma once
#include"Map.h"
#include"Team.h"
#include"Match.h"
#include<time.h>
#include<queue>
#include"Player.h"
#include"Algorithm.h"
#include"json/json.h"
using std::queue;
class DataBase
{
public:
	struct eve_data 
	{
		friend class DataBase;
		string player;
		string type;
		string time;
	};
	class KnockOutTree 
	{
		friend class DataBase;
	private:
		int home_last_match;
		int away_last_match;
		bool src_from;//true来自淘汰赛,false来自小组赛
	public:
		KnockOutTree();
		~KnockOutTree();
	};
public:
	DataBase();
	~DataBase();
	//射手榜
public:
	Player**GetshoterRank();
	string GetTeamName(int t_id);
private:
	int Getshot(int p_id);//获取球员射门数
public:
	//积分榜
	int GetWin(int t_id);
	int GetLose(int t_id);
	int GetDraw(int t_id);
	Team** GetPointRank(int group);//获得某小组积分排名
	//比赛结果
public:
	int GetMatch(int t_id,int n);//获得某国家第n场比赛id
	int GetHomeTeam(int m_id);
	int GeVisitingTeam(int m_id);
	queue<DataBase::eve_data> GetEvents(int m_id,int &cnt, bool t_type);
	//UI接口
public:
	void Update(time_t now);
	time_t strTotime(string str);
private:
	void ReadMatchBaseInfo(Json::Value & match);
	void ReadTeamBaseInfo(Json::Value & team);
	void ReadPlayerBaseIndo(Json::Value & player);
	void CreateGameMap();
	void CreateKnockoutTree();
	void UpdateTeam(int t_id);
	void ClearPoint();
	void Update(time_t now, Json::Value & match);
	void AddGame(int home, int away, int num);
private:
public:
	Map<int,int> gamemap;//小组赛
	Team*team;//[]参赛的全部球队32
	Team**knockout_team;//16强
	KnockOutTree*knockout_tree;//16强比赛分布
	Player*player;//[]参赛的全部球员32*23
	Match*match;//[]所有比赛64
	Algorithm sort;
public:
	//test
	void show_gamemap();
	void show_match_result();
	void show_match(int m_id);
	void show_team();
};

