#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WorldCupQt.h"
#include"DataBase.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStackedLayout>
#include<QTabWidget>
#include<QSpinBox>
#include<time.h>
#include<QLineF>
#include"QWKnockout.h"
enum state {match,score,shooter,m_detail,m_out};
class WorldCupQt : public QMainWindow
{
	Q_OBJECT
public:
	WorldCupQt(DataBase*data,QWidget *parent = Q_NULLPTR);
public slots:
	void show_match();
	void time_change();
	void show_score();
	void show_shooter();
	void print_shooter(int n = 736);
	void search();
	void detail(int data);
private:
	Ui::WorldCupQtClass ui;
	QStackedLayout *body;
	QWidget *err;
	QTabWidget *tab_match;
	QWKnockout*knockout;
	QTableWidget*t_match;
	QTableWidget*t_score;
	QTableWidget*t_shooter;
	QTableWidget*t_match_detail;
	QSpinBox *p_num;
	DataBase*data;
	void update(time_t t);
	void show_match_detail(int m_id);
	bool *status;
};
