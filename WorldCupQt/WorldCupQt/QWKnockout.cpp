#include "QWKnockout.h"
#include<QPainter>
#include<QVector>
#include<queue>
#include<string>
#include<sstream>

QWKnockout::QWKnockout(QWidget * parent) :QWidget(parent),time(0), data(nullptr)
{
	match = new QPushButton*[32];
	for (int i = 0; i < 32; i++) 
	{
		match[i] = new QPushButton(this);
		std::ostringstream s;
		s << i;
		match[i]->setObjectName(QString::fromStdString(s.str()));
		if (i >= 16) 
		{
			QObject::connect(match[i],&QPushButton::clicked,this, &QWKnockout::send);
		}
	}
}

QWKnockout::~QWKnockout()
{
	delete[] match;
}

void QWKnockout::SetTime(time_t t)
{
	time = t;
}

void QWKnockout::SetData(DataBase *d)
{
	data = d;
}

void QWKnockout::SetPadding(double left, double top, double right, double bottom)
{
	padding_right=right;
	padding_top=top;
	padding_left=left;
	padding_bottom=bottom;
}

void QWKnockout::paintEvent(QPaintEvent * event)
{
	draw_knockout_tree();
}

void QWKnockout::draw_knockout_tree()
{
	QPainter painter(this);
	QPen pen;
	QRectF rect(width()*padding_left, height()*padding_top, width()*(1 - padding_left - padding_right), height()*(1 - padding_top - padding_bottom));
	double board = 0.05*rect.height();
	double rh = (rect.height() - 7 * board) / 8;
	double rw = (rect.width()) / 15;
	QVector<QRectF>vect_r;
	QVector<QLineF>vect_l;
	QVector<QLineF>vect_l2;
	std::queue<QRectF>q1;
	std::queue<QRectF>q2;
	
#define L_LENGTH 1.5
	for (int i = 0; i < 8; i++)
	{
		QRectF r1(rect.left(), rect.top() + i * (rh + board), rw, rh);
		q1.push(r1);
		QRectF r2(rect.right() - rw, rect.top() + i * (rh + board), rw, rh);
		q2.push(r2);
	}
	while (!q1.empty())
	{
		if (q1.size() > 1)
		{
			QRectF r1 = q1.front();
			q1.pop();
			QRectF r2 = q1.front();
			q1.pop();
			QRectF r_new(r1.left() + L_LENGTH * rw, (r1.top() + r2.top()) / 2, rw, rh);
			q1.push(r_new);
			vect_r.push_back(r1);
			vect_r.push_back(r2);
			QPointF p1;
			QPointF p2;
			QPointF p3;
			p1 = QPointF(r1.right(), r1.top() + 0.5*rh);
			p2 = QPointF(r1.right() + (L_LENGTH - 0.5)  * rw, r1.top() + 0.5*rh);
			p3 = QPointF(r1.right() + (L_LENGTH - 0.5)  * rw, (r1.top() + r2.top()) / 2);
			vect_l.push_back(QLineF(p1, p2));
			vect_l.push_back(QLineF(p2, p3));
			p1 = QPointF(r2.right(), r2.top() + 0.5*rh);
			p2 = QPointF(r2.right() + (L_LENGTH - 0.5)  * rw, r2.top() + 0.5*rh);
			p3 = QPointF(r2.right() + (L_LENGTH - 0.5)  * rw, (r1.top() + r2.top()) / 2);
			vect_l.push_back(QLineF(p1, p2));
			vect_l.push_back(QLineF(p2, p3));
		}
		else
		{
			QRectF r1 = q1.front();
			q1.pop();
			vect_r.push_back(r1);
		}
		if (q2.size() > 1) 
		{
			QRectF r1 = q2.front();
			q2.pop();
			QRectF r2 = q2.front();
			q2.pop();
			QRectF r_new(r1.left() - L_LENGTH * rw, (r1.top() + r2.top()) / 2, rw, rh);
			q2.push(r_new);
			vect_r.push_back(r1);
			vect_r.push_back(r2);
			QPointF p1;
			QPointF p2;
			QPointF p3;
			p1 = QPointF(r1.left(), r1.top() + 0.5*rh);
			p2 = QPointF(r1.left() - (L_LENGTH - 0.5)  * rw, r1.top() + 0.5*rh);
			p3 = QPointF(r1.left() - (L_LENGTH - 0.5)  * rw, (r1.top() + r2.top()) / 2);
			vect_l.push_back(QLineF(p1, p2));
			vect_l.push_back(QLineF(p2, p3));
			p1 = QPointF(r2.left(), r2.top() + 0.5*rh);
			p2 = QPointF(r2.left() - (L_LENGTH - 0.5)  * rw, r2.top() + 0.5*rh);
			p3 = QPointF(r2.left() - (L_LENGTH - 0.5)  * rw, (r2.top() + r1.top()) / 2);
			vect_l.push_back(QLineF(p1, p2));
			vect_l.push_back(QLineF(p2, p3));
		}
		else
		{
			QRectF r1 = q2.front();
			q2.pop();
			vect_r.push_back(r1);
		}
	}
	QRectF r1((vect_r[28].left()+ vect_r[29].left())/2,vect_r[26].top()+rh,rw,rh);
	QRectF r2((vect_r[28].left() + vect_r[29].left()) / 2, vect_r[27].top()- rh, rw, rh);
	vect_r.push_back(r1);
	vect_r.push_back(r2);
	for (int i = 0; i < vect_r.size(); i++) 
	{
		std::ostringstream s;
		match[i]->setGeometry(vect_r[i].left(), vect_r[i].top(), vect_r[i].width(), vect_r[i].height());
		if (i < 16) 
		{
			int t = -1;
			switch (i)
			{
			case 0:	case 1:
				t = data->Predict(48, i % 2 == 0);
				break;
			case 2:	case 3:
				t = data->Predict(50, i % 2 == 0);
				break;
			case 4:	case 5:
				t = data->Predict(49, i % 2 == 0);
				break;
			case 6:	case 7:
				t = data->Predict(51, i % 2 == 0);
				break;
			case 8:	case 9:
				t = data->Predict(52, i % 2 == 0);
				break;
			case 10:case 11:
				t = data->Predict(54, i % 2 == 0);
				break;
			case 12:case 13:
				t = data->Predict(53, i % 2 == 0);
				break;
			case 14:case 15:
				t = data->Predict(55, i % 2 == 0);
				break;
			default:
				break;
			}
			//s << i;
			//match[i]->setText(QString::fromStdString(s.str()));
			match[i]->setText(QString::fromStdString(data->team[t].GetName()));
			//ÉèÖÃ±ß¿òÑÕÉ«
			switch (i)
			{
				case 0:	case 1:
					if (data->TeamDetermined(48, i % 2 == 0))
					{
						QPen pen(Qt::red, 3);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					else
					{
						QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					break;
				case 2:	case 3:
					if (data->TeamDetermined(50, i % 2 == 0))
					{
						QPen pen(Qt::red, 3);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					else
					{
						QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					break;
				case 4:	case 5:
					if (data->TeamDetermined(49, i % 2 == 0))
					{
						QPen pen(Qt::red, 3);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					else
					{
						QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					break;
				case 6:	case 7:
					if (data->TeamDetermined(51, i % 2 == 0))
					{
						QPen pen(Qt::red, 3);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					else
					{
						QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					break;
				case 8:	case 9:
					if (data->TeamDetermined(52, i % 2 == 0))
					{
						QPen pen(Qt::red, 3);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					else
					{
						QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					break;
				case 10:case 11:
					if (data->TeamDetermined(54, i % 2 == 0))
					{
						QPen pen(Qt::red, 3);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					else
					{
						QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					break;
				case 12:case 13:
					if (data->TeamDetermined(53, i % 2 == 0))
						{
							QPen pen(Qt::red, 3);
							painter.setPen(pen);
							painter.drawRect(vect_r[i]);
						}
					else
					{
						QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					break;
				case 14:case 15:
					if (data->TeamDetermined(55, i % 2 == 0))
					{
						QPen pen(Qt::red, 3);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					else
					{
						QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawRect(vect_r[i]);
					}
					break;
				default:
					break;
			}
			
		}
		else 
		{
			int n=data->TreeToMatch(i);
			s<<"m"<<n+1;
			match[i]->setText(QString::fromStdString(s.str()));
			if (data->match[n].GetStatus(0) == completed) 
			{
				QPen pen(Qt::red, 3);
				painter.setPen(pen);
				painter.drawRect(vect_r[i]);
			}
			else
			{
				QPen pen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
				painter.setPen(pen);
				painter.drawRect(vect_r[i]);
			}
			//»­Ïß
			if (i < 30) 
			{
				if (data->match[n].GetStatus(0) == completed)
				{
					if (data->match[n].GetTeamID(HOME) == data->match[n].GetWinner()&&n!=56) 
					{
						pen=QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(vect_l[4 * (i - 16)]);
						painter.drawLine(vect_l[4 * (i - 16) + 1]);
						pen= QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(vect_l[4 * (i - 16) + 2]);
						painter.drawLine(vect_l[4 * (i - 16) + 3]);
					}
					else if(data->match[n].GetTeamID(HOME) == data->match[n].GetWinner() && n == 56)
					{
						pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(vect_l[4 * (i - 16)]);
						painter.drawLine(vect_l[4 * (i - 16) + 1]);
						pen = QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(vect_l[4 * (i - 16) + 2]);
						painter.drawLine(vect_l[4 * (i - 16) + 3]);
					}
					else if	(data->match[n].GetTeamID(AWAY) == data->match[n].GetWinner() && n != 56)
					{
						pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(vect_l[4 * (i - 16)]);
						painter.drawLine(vect_l[4 * (i - 16) + 1]);
						pen = QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(vect_l[4 * (i - 16) + 2]);
						painter.drawLine(vect_l[4 * (i - 16) + 3]);
					}
					else 
					{
						pen = QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(vect_l[4 * (i - 16)]);
						painter.drawLine(vect_l[4 * (i - 16) + 1]);
						pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(vect_l[4 * (i - 16) + 2]);
						painter.drawLine(vect_l[4 * (i - 16) + 3]);
					}
				}
				else 
				{
					pen = QPen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
					painter.setPen(pen);
					painter.drawLine(vect_l[4 * (i - 16)]);
					painter.drawLine(vect_l[4 * (i - 16) + 1]);
					painter.drawLine(vect_l[4 * (i - 16) + 2]);
					painter.drawLine(vect_l[4 * (i - 16) + 3]);
				}
			}
			if (i == 30) 
			{
				QPointF p1, p2, p3, p4, p5, p6;
				p1 = QPointF(vect_r[i - 2].right(), vect_r[i - 2].top()+0.5 * rh - 2);
				p2 = QPointF(vect_r[i - 1].left(), vect_r[i - 1].top() + 0.5 * rh - 2);
				p3 = QPointF((vect_r[i - 2].right() + vect_r[i - 1].left()) / 2 - 2, vect_r[i].bottom());
				p4 = QPointF((vect_r[i - 2].right() + vect_r[i - 1].left()) / 2 + 2, vect_r[i].bottom());
				p5 = QPointF((vect_r[i - 2].right() + vect_r[i - 1].left()) / 2 - 2, vect_r[i - 2].top() + 0.5 * rh - 2);
				p6 = QPointF((vect_r[i - 2].right() + vect_r[i - 1].left()) / 2 + 2, vect_r[i - 1].top() + 0.5 * rh - 2);
				if (data->match[i+33].GetStatus(0) == completed)
				{
					if (data->match[i + 33].GetWinner() == data->match[i + 30].GetWinner())
					{
						pen = QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(p1, p5);
						painter.drawLine(p5, p3);
						pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(p2, p6);
						painter.drawLine(p6, p4);
					}
					else 
					{
						pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(p1, p5);
						painter.drawLine(p5, p3);
						pen = QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(p2, p6);
						painter.drawLine(p6, p4);
					}
				}
				else 
				{
					pen = QPen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
				    painter.setPen(pen);
					painter.drawLine(p1, p5);
					painter.drawLine(p5, p3);
					painter.drawLine(p2, p6);
					painter.drawLine(p6, p4);
				}				
			}
			if (i == 31) 
			{
				QPointF p1,p2,p3,p4,p5,p6;
				p1 = QPointF(vect_r[i - 3].right(), vect_r[i - 3].top() + 0.5 * rh + 2);
				p2 = QPointF(vect_r[i - 2].left(), vect_r[i - 2].top() + 0.5 * rh + 2);
				p3 = QPointF((vect_r[i - 3].right() + vect_r[i - 2].left()) / 2 - 2, vect_r[i].top());
				p4 = QPointF((vect_r[i - 3].right() + vect_r[i - 2].left()) / 2 + 2, vect_r[i].top());
				p5 = QPointF((vect_r[i - 3].right() + vect_r[i - 2].left()) / 2 - 2, vect_r[i - 3].top() + 0.5 * rh + 2);
				p6 = QPointF((vect_r[i - 3].right() + vect_r[i - 2].left()) / 2 + 2, vect_r[i - 2].top() + 0.5 * rh + 2);
				if (data->match[i + 32].GetStatus(0) == completed)
				{
					if (data->match[i + 31].GetWinner() == data->match[i + 29].GetLoser())
					{
						pen = QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(p1, p5);
						painter.drawLine(p5, p3);
						pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(p2, p6);
						painter.drawLine(p6, p4);
					}
					else
					{
						pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(p1, p5);
						painter.drawLine(p5, p3);
						pen = QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						painter.setPen(pen);
						painter.drawLine(p2, p6);
						painter.drawLine(p6, p4);
					}
				}
				else
				{
					pen = QPen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
					painter.setPen(pen);
					painter.drawLine(p1, p5);
					painter.drawLine(p5, p3);
					painter.drawLine(p2, p6);
					painter.drawLine(p6, p4);
				}
			}
		}
	}
	pen = QPen(Qt::gray, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
	painter.setPen(pen);
}

void QWKnockout::send()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	int i = btn->objectName().toInt();
	int m = data->TreeToMatch(i);
	emit bm_clicked(m);
}