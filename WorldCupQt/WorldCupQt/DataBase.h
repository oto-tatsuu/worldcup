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
		bool src_from;//true������̭��,false����С����
	public:
		KnockOutTree();
		~KnockOutTree();
	};
public:
	DataBase();
	~DataBase();
	//���ְ�
public:
	Player**GetshoterRank();
	string GetTeamName(int t_id);
private:
	int Getshot(int p_id);//��ȡ��Ա������
public:
	//���ְ�
	int GetWin(int t_id);
	int GetLose(int t_id);
	int GetDraw(int t_id);
	Team** GetPointRank(int group);//���ĳС���������
	//�������
public:
	int GetMatch(int t_id,int n);//���ĳ���ҵ�n������id
	int GetHomeTeam(int m_id);
	int GeVisitingTeam(int m_id);
	queue<DataBase::eve_data> GetEvents(int m_id,int &cnt, bool t_type);
	//UI�ӿ�
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
	Map<int,int> gamemap;//С����
	Team*team;//[]������ȫ�����32
	Team**knockout_team;//16ǿ
	KnockOutTree*knockout_tree;//16ǿ�����ֲ�
	Player*player;//[]������ȫ����Ա32*23
	Match*match;//[]���б���64
	Algorithm sort;
public:
	//test
	void show_gamemap();
	void show_match_result();
	void show_match(int m_id);
	void show_team();
};

