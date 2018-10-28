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
	//���ְ�
public:
	int*GetshoterRank();//
private:
	int Getshot(int p_id);//��ȡ��Ա������
public:
	//���ְ�
	int GetPoint(int t_id);//���ĳ���һ���
	int* GetPointRank(int group);//���ĳС���������
	//�������
public:
	int GetMatch(int t_id,int n);//���ĳ���ҵ�n������id
	tm GetMatchStartTime(int m_id);//��ñ�����ʼʱ��
	int GetHomeTeam(int m_id);
	int GeVisitingTeam(int m_id);
	void SetHomeTeam(int m_id,int t_id);
	void SetVisitingTeam(int m_id,int t_id);
	//UI�ӿ�
public:
	void Update(time_t now);
private:
	void ReadMatchBaseInfo();
	void CreateGameMap();
	time_t strTotime(string str);
	void AddGame(int home, int away, int num);
//private:
private:
	Map<int,int> gamemap;//С����
	queue<int> knockour;//��̭��
	Team*team;//[]������ȫ�����32
	Player*player;//[]������ȫ����Ա32*23
	Match*match;//[]���б���64
	Match * latest_match;//���һ���ѷ����ı���
public:
	//test
	void show_gamemap();
	void show_match_result();
};

