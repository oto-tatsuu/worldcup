#include "WorldCupQt.h"
#include<QHeaderView>
#include<QLabel>
#include<QString>
#include<QHBoxLayout>
WorldCupQt::WorldCupQt(DataBase*data, QWidget *parent)
	: data(data),QMainWindow(parent)
{
	status = new bool[5];
	for (int i = 0; i < 5; i ++ ) 
	{
		status[i] = true;
	}
	ui.setupUi(this);

	body=new QStackedLayout;
	body->setSpacing(6);
	ui.verticalLayout->addLayout(body);
	
	err = new QWidget;
	QLabel *err_info = new QLabel("input err please input again!");
	//err
	{
		QHBoxLayout*l_err = new QHBoxLayout;
		auto hspacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		l_err->addItem(hspacer1);
		l_err->addWidget(err_info);
		auto hspacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		l_err->addItem(hspacer2);
		err->setLayout(l_err);
	}
	t_match = new QTableWidget;
	t_score = new QTableWidget;
	t_shooter = new QTableWidget;
	t_match_detail = new QTableWidget;
	body->addWidget(err);
	body->addWidget(t_match);
	body->addWidget(t_score);
	body->addWidget(t_shooter);
	body->addWidget(t_match_detail);
	body->setCurrentIndex(1);
	p_num= new QSpinBox;
	p_num->setRange(1,736);
	p_num->setValue(736);
	void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
	QObject::connect(p_num, spinBoxSignal,this,&WorldCupQt::print_shooter);
	p_num->setAlignment(Qt::AlignCenter);
}
#include<sstream>
void WorldCupQt:: show_match()
{
	status[match] = false;
	status[score] = true;
	status[shooter] = true;
	ui.B_match->setEnabled(false);
	ui.B_score->setEnabled(true);
	ui.B_shooter->setEnabled(true);
	t_match->setColumnCount(6);
	int row = 0;
	for (int i = 0; i < 64; i++)
	{
		row += 2;
		t_match->setRowCount(row);
		int home = data->match[i].GetTeamID(HOME);
		int away = data->match[i].GetTeamID(AWAY);
		int f_row = 2 * i;
		t_match->setItem(f_row, 0, new QTableWidgetItem("Match NO."));
		std::ostringstream s;
		s << i + 1;
		QTableWidgetItem*item = new QTableWidgetItem(QString::fromStdString(s.str()));
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 1, item);
		item = new QTableWidgetItem("Start Time");
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 2, item);
		item = new QTableWidgetItem(QString::fromStdString(data->match[i].GetStartTime()));
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 3, item);
		item = new QTableWidgetItem("Match Status");
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 4, item);
		item = new QTableWidgetItem(QString::fromStdString(data->match[i].GetStatus()));
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 5, item);
		f_row++;
		item = new QTableWidgetItem("Home Team");
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 0, item);
		item = new QTableWidgetItem(QString::fromStdString(data->match[i].GetTeamName(HOME)));
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 1, item);
		item = new QTableWidgetItem("Away Team");
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 2,item);
		item = new QTableWidgetItem(QString::fromStdString(data->match[i].GetTeamName(AWAY)));
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 3, item);
		item = new QTableWidgetItem("Score");
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 4, item);
		s.str("");
		s << data->match[i].GetScore(HOME);
		s << ":";
		s<<data->match[i].GetScore(AWAY);
		item = new QTableWidgetItem(QString::fromStdString(s.str()));
		item->setTextAlignment(Qt::AlignCenter);
		t_match->setItem(f_row, 5, item);
	}
	t_match->resizeColumnsToContents();//列宽自适应
	t_match->verticalHeader()->setVisible(false);   //隐藏列表头  
	t_match->horizontalHeader()->setVisible(false); //隐藏行表头
	t_match->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改内容
	body->setCurrentIndex(1);
}
void WorldCupQt::time_change() 
{
	QDate date = ui.now->date();  // 日期
	QTime time = ui.now->time();
	tm now;
	now.tm_year = date.year() - 1900;
	now.tm_mon = date.month();
	now.tm_mday = date.day();
	now.tm_hour = time.hour();
	now.tm_min = time.minute();
	now.tm_sec = time.second();
	time_t t=mktime(&now);
	update(t);
}

void WorldCupQt::show_score()
{
	status[match] = true;
	status[score] = false;
	status[shooter] = true;
	ui.B_match->setEnabled(true);
	ui.B_score->setEnabled(false);
	ui.B_shooter->setEnabled(true);
	
	t_score->setColumnCount(9);
	int row = 0;
	for (int i = 0; i < 8; i++) 
	{
		row += 5;
		int f_row = i * 5;
		t_score->setRowCount(row);
		Team**t = data->GetPointRank(i);
		QTableWidgetItem*item = new QTableWidgetItem("Group");
		item->setTextAlignment(Qt::AlignCenter);
		t_score->setItem(f_row, 0, item);
		char c = 'A';
		c = c+i;
		QChar ch=QChar(c);
		item = new QTableWidgetItem(QString(ch));
		item->setTextAlignment(Qt::AlignCenter);
		t_score->setItem(f_row+1, 0, item);
		t_score->setSpan(f_row+1, 0, 4, 1);
		{
			item = new QTableWidgetItem("Team");
			item->setTextAlignment(Qt::AlignCenter);
			t_score->setItem(f_row, 1, item);
			item = new QTableWidgetItem("Win");
			item->setTextAlignment(Qt::AlignCenter);
			t_score->setItem(f_row, 2, item);
			item = new QTableWidgetItem("Lose");
			item->setTextAlignment(Qt::AlignCenter);
			t_score->setItem(f_row, 3, item);
			item = new QTableWidgetItem("Draw");
			item->setTextAlignment(Qt::AlignCenter);
			t_score->setItem(f_row, 4, item);
			item = new QTableWidgetItem("Net");
			item->setTextAlignment(Qt::AlignCenter);
			t_score->setItem(f_row, 5, item);
			item = new QTableWidgetItem("Total");
			item->setTextAlignment(Qt::AlignCenter);
			t_score->setItem(f_row, 6, item);
			item = new QTableWidgetItem("Card");
			item->setTextAlignment(Qt::AlignCenter);
			t_score->setItem(f_row, 7, item);
			item = new QTableWidgetItem("Point");
			item->setTextAlignment(Qt::AlignCenter);
			t_score->setItem(f_row, 8, item);
		}
		for (int j = 0; j < 4; j++) 
		{
			std::ostringstream s;
			int t_id = t[j]->GetID();
			int win = data->GetWin(t_id);
			int lose = data->GetLose(t_id);
			int draw = data->GetDraw(t_id);
			item = new QTableWidgetItem(QString::fromStdString(t[j]->GetName()));
			item->setTextAlignment(Qt::AlignCenter);
			if(j<2)
			item->setBackgroundColor(QColor(102, 204, 255));
			t_score->setItem(f_row+j+1, 1, item);
			s << win;
			item = new QTableWidgetItem(QString::fromStdString(s.str()));
			item->setTextAlignment(Qt::AlignCenter);
			if (j<2)
				item->setBackgroundColor(QColor(102, 204, 255));
			t_score->setItem(f_row+j+1, 2, item);
			s.str("");
			s << lose;
			item = new QTableWidgetItem(QString::fromStdString(s.str()));
			item->setTextAlignment(Qt::AlignCenter);
			if (j<2)
				item->setBackgroundColor(QColor(102, 204, 255));
			t_score->setItem(f_row+j+1, 3, item);
			s.str("");
			s << draw;
			item = new QTableWidgetItem(QString::fromStdString(s.str()));
			item->setTextAlignment(Qt::AlignCenter);
			if (j<2)
				item->setBackgroundColor(QColor(102, 204, 255));
			t_score->setItem(f_row+j+1, 4, item);
			s.str("");
			s << t[j]->GetJudgePoint().net_victory;
			item = new QTableWidgetItem(QString::fromStdString(s.str()));
			item->setTextAlignment(Qt::AlignCenter);
			if (j<2)
				item->setBackgroundColor(QColor(102, 204, 255));
			t_score->setItem(f_row+j+1, 5, item);
			s.str("");
			s << t[j]->GetJudgePoint().total_goal;
			item = new QTableWidgetItem(QString::fromStdString(s.str()));
			item->setTextAlignment(Qt::AlignCenter);
			if (j<2)
				item->setBackgroundColor(QColor(102, 204, 255));
			t_score->setItem(f_row+j+1, 6, item);
			s.str("");
			s << t[j]->GetJudgePoint().card;
			item = new QTableWidgetItem(QString::fromStdString(s.str()));
			item->setTextAlignment(Qt::AlignCenter);
			if (j<2)
				item->setBackgroundColor(QColor(102, 204, 255));
			t_score->setItem(f_row+j+1, 7, item);
			s.str("");
			s << t[j]->GetJudgePoint().point;
			item = new QTableWidgetItem(QString::fromStdString(s.str()));
			item->setTextAlignment(Qt::AlignCenter);
			if (j<2)
				item->setBackgroundColor(QColor(102, 204, 255));
			t_score->setItem(f_row+j+1, 8, item);
		}
		data->sort.DeleteArray(t, 4);
	}
	t_score->resizeColumnsToContents();//列宽自适应
	t_score->verticalHeader()->setVisible(false);   //隐藏列表头  
	t_score->horizontalHeader()->setVisible(false); //隐藏行表头
	t_score->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改内容
	body->setCurrentIndex(2);
}

void WorldCupQt::show_shooter()
{
	status[match] = true;
	status[score] = true;
	status[shooter] = false;
	ui.B_match->setEnabled(true);
	ui.B_score->setEnabled(true);
	ui.B_shooter->setEnabled(false);
	t_shooter->setColumnCount(5);
	t_shooter->setRowCount(1);
	QTableWidgetItem*item = new QTableWidgetItem("Best of");
	item->setTextAlignment(Qt::AlignCenter);
	t_shooter->setItem(0, 0, item);
	t_shooter->setSpan(0, 0, 1, 3);
	t_shooter->setCellWidget(0, 3, p_num);
	t_shooter->setSpan(0, 3, 1, 2);
	int n = p_num->value();
	print_shooter(n);
	body->setCurrentIndex(3);
}

void WorldCupQt::print_shooter(int n)
{
	t_shooter->setRowCount(n+2);
	QTableWidgetItem*item=nullptr;
	Player**p = data->GetshoterRank();
	{
		item = new QTableWidgetItem("Name");
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(1, 0, item);
		item = new QTableWidgetItem("Team");
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(1, 1, item);
		item = new QTableWidgetItem("Shirt NO.");
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(1, 2, item);
		item = new QTableWidgetItem("Goals");
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(1, 3, item);
		item = new QTableWidgetItem("Penalties");
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(1, 4, item);
	}
	for (int i = 0; i < n; i++)
	{
		int t_id = p[i]->GetID() / 23;
		int shirt = p[i]->GetID() % 23+1;
		std::ostringstream o;
		item = new QTableWidgetItem(QString::fromStdString(p[i]->GetName()));
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(2 + i, 0, item);
		item = new QTableWidgetItem(QString::fromStdString(data->GetTeamName(t_id)));
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(2 + i, 1, item);
		o << shirt;
		item = new QTableWidgetItem(QString::fromStdString(o.str()));
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(2 + i, 2, item);
		o.str("");
		o << p[i]->GetGoal_num();
		item = new QTableWidgetItem(QString::fromStdString(o.str()));
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(2 + i, 3, item);
		o.str("");
		o << p[i]->GetPenalty_num();
		item = new QTableWidgetItem(QString::fromStdString(o.str()));
		item->setTextAlignment(Qt::AlignCenter);
		t_shooter->setItem(2 + i, 4, item);

	}
	data->sort.DeleteArray(p, 736);
	t_shooter->resizeColumnsToContents();//列宽自适应
	t_shooter->verticalHeader()->setVisible(false);   //隐藏列表头  
	t_shooter->horizontalHeader()->setVisible(false); //隐藏行表头
	t_shooter->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改内容
}

void WorldCupQt::search()
{
	QString str=ui.search->displayText();
	QChar ch=str[0];
	if (ch >= '0'&&ch <= '9') 
	{
		int length = str.length();
		int i = 0;
		for (; i < length&&str[i] >= '0'&&str[i] <= '9'; i++);
		if (i = length) 
		{
			int m = str.toInt();
			if (m > 0 && m <= 64) 
			{
				show_match_detail(m-1);
			}
			else
			{
				throw std::runtime_error("输入非法比赛编号");
			}
		}
	}
	else 
	{
		if (str.startsWith("match:")) 
		{
			QString sub = str.right(str.length()-6);
			int m = sub.toInt();
			if (m > 0 && m <= 64)
			{
				show_match_detail(m - 1);
			}
			else
			{
				throw std::runtime_error("输入非法比赛编号");
			}
		}
		
	}
}

void WorldCupQt::update(time_t t)
{
	data->Update(t);
	if (!status[match])
	{
		show_match();
		return;
	}
	else if (!status[score])
	{
		show_score();
		return;
	}
	else if (!status[shooter])
	{
		show_shooter();
		return;
	}
	return;
}

void WorldCupQt::show_match_detail(int m_id)
{
	status[match] = true;
	status[score] = true;
	status[shooter] = true;
	status[m_detail] = false;
	ui.B_match->setEnabled(true);
	ui.B_score->setEnabled(true);
	ui.B_shooter->setEnabled(true);
	std::ostringstream o;
	t_match_detail->setColumnCount(4);
	t_match_detail->setRowCount(3);
	o << "the ";
	o << m_id + 1;
	o << " game";
	int row=0;
	QTableWidgetItem*item=new QTableWidgetItem(QString::fromStdString(o.str()));
	item->setTextAlignment(Qt::AlignCenter);
	t_match_detail->setItem(row, 1, item);
	t_match_detail->setSpan(row, 1, 1, 2);
	item = new QTableWidgetItem(QString::fromStdString(data->match[m_id].GetTeamName(HOME)));
	item->setTextAlignment(Qt::AlignCenter);
	row++;
	t_match_detail->setItem(row, 0, item);
	item = new QTableWidgetItem(QString::fromStdString(data->match[m_id].GetTeamName(AWAY)));
	item->setTextAlignment(Qt::AlignCenter);
	t_match_detail->setItem(row, 3, item);
	item = new QTableWidgetItem(QString::fromStdString(data->match[m_id].GetStartTime()));
	item->setTextAlignment(Qt::AlignCenter);
	t_match_detail->setItem(row, 1, item);
	t_match_detail->setSpan(row, 1, 1, 2);
	row++;
	o.str("");
	o << data->match[m_id].GetScore(HOME);
	o << "   :   ";
	o << data->match[m_id].GetScore(AWAY);
	item = new QTableWidgetItem(QString::fromStdString(o.str()));
	item->setTextAlignment(Qt::AlignCenter);
	t_match_detail->setItem(row, 1, item);
	t_match_detail->setSpan(row, 1, 1, 2);
	if (data->match[m_id].HavePenalty())
	{
		row++;
		t_match_detail->setRowCount(row+1);
		item = new QTableWidgetItem("Penalty");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 0, item);
		item = new QTableWidgetItem("Shootout");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 3, item);
		o.str("");
		o << data->match[m_id].GetPenalties(HOME);
		o << "   :   ";
		o << data->match[m_id].GetPenalties(AWAY);
		item = new QTableWidgetItem(QString::fromStdString(o.str()));
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 1, item);
		t_match_detail->setSpan(row, 1, 1, 2);
	} 
	{
		row++;
		t_match_detail->setRowCount(row + 1);
		item = new QTableWidgetItem("Winner");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 0, item);
		if (data->match[m_id].GetStatus(0) == completed) 
		{
			item = new QTableWidgetItem(QString::fromStdString(data->match[m_id].GetWinnerName()));
		}
			
		else
			item = new QTableWidgetItem("Coming soon");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 1, item);
		t_match_detail->setSpan(row, 1, 1, 3);
	}
	if (data->match[m_id].GetStatus(0) != not_beginning)
	{
		row++;
		row++;
		int cnt=0;
		queue<DataBase::eve_data>r = data->GetEvents(m_id,cnt,HOME);
		t_match_detail->setRowCount(row + cnt + 1);
		item = new QTableWidgetItem("Home Events");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 0, item);
		t_match_detail->setSpan(row, 0, cnt + 1,1);
		item = new QTableWidgetItem("Player");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 1, item);
		item = new QTableWidgetItem("Time");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 2, item);
		item = new QTableWidgetItem("Type");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 3, item);
		row++;
		while (!r.empty())
		{
			DataBase::eve_data eve = r.front();
			r.pop();
			item = new QTableWidgetItem(QString::fromStdString(eve.player));
			item->setTextAlignment(Qt::AlignCenter);
			t_match_detail->setItem(row, 1, item);
			item = new QTableWidgetItem(QString::fromStdString(eve.time));
			item->setTextAlignment(Qt::AlignCenter);
			t_match_detail->setItem(row, 2, item);
			item = new QTableWidgetItem(QString::fromStdString(eve.type));
			item->setTextAlignment(Qt::AlignCenter);
			t_match_detail->setItem(row, 3, item);
			row++;
		}
		row++;
		cnt = 0;
		r = data->GetEvents(m_id, cnt, AWAY);
		t_match_detail->setRowCount(row + cnt + 1);
		item = new QTableWidgetItem("Away Events");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 0, item);
		t_match_detail->setSpan(row, 0, cnt+1, 1);
		item = new QTableWidgetItem("Player");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 1, item);
		item = new QTableWidgetItem("Time");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 2, item);
		item = new QTableWidgetItem("Type");
		item->setTextAlignment(Qt::AlignCenter);
		t_match_detail->setItem(row, 3, item);
		row++;
		while (!r.empty())
		{
			DataBase::eve_data eve = r.front();
			r.pop();
			item = new QTableWidgetItem(QString::fromStdString(eve.player));
			item->setTextAlignment(Qt::AlignCenter);
			t_match_detail->setItem(row, 1, item);
			item = new QTableWidgetItem(QString::fromStdString(eve.time));
			item->setTextAlignment(Qt::AlignCenter);
			t_match_detail->setItem(row, 2, item);
			item = new QTableWidgetItem(QString::fromStdString(eve.type));
			item->setTextAlignment(Qt::AlignCenter);
			t_match_detail->setItem(row, 3, item);
			row++;
		}
	}
	
	
	t_shooter->resizeColumnsToContents();//列宽自适应
	t_match_detail->verticalHeader()->setVisible(false);   //隐藏列表头  
	t_match_detail->horizontalHeader()->setVisible(false); //隐藏行表头
	t_match_detail->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改内容
	body->setCurrentIndex(4);
}
