#pragma once
#include<QWidget>
#include<time.h>
#include<QPushButton>
#include"DataBase.h"
class QWKnockout:public QWidget
{
	Q_OBJECT
public:
	QWKnockout(QWidget *parent = Q_NULLPTR);
	~QWKnockout();
	void SetTime(time_t t);
	void SetData(DataBase *d);
	void SetPadding(double left,double top,double right,double bottom);
signals:
	void bm_clicked(int);
private slots:
	void send();
private:
	time_t time;
	DataBase * data;
	double padding_right;
	double padding_top;
	double padding_left;
	double padding_bottom;
	void paintEvent(QPaintEvent * event)override;
	void draw_knockout_tree();
	QPushButton**match;
};

