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
	//���ְ�
public:
	int*GetshoterRank();//
private:
	int Getshot(int p_id);//��ȡ��Ա������
public:
	//���ְ�
	int GetPoint(int t_id);//���ĳ���һ���
	Team** GetPointRank(int group);//���ĳС���������
	//�������
public:
	int GetMatch(int t_id,int n);//���ĳ���ҵ�n������id
	int GetHomeTeam(int m_id);
	int GeVisitingTeam(int m_id);
	//UI�ӿ�
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
	Map<int,int> gamemap;//С����
	queue<int> knockour;//��̭��
	Team*team;//[]������ȫ�����32
	Player*player;//[]������ȫ����Ա32*23
	Match*match;//[]���б���64
	Algorithm sort;
public:
	//test
	void show_gamemap();
	void show_match_result();
	void show_team();
};

