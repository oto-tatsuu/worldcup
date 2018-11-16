#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WorldCupQt.h"

class WorldCupQt : public QMainWindow
{
	Q_OBJECT

public:
	WorldCupQt(QWidget *parent = Q_NULLPTR);

private:
	Ui::WorldCupQtClass ui;
};
