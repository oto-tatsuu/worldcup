/********************************************************************************
** Form generated from reading UI file 'WorldCupQt.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORLDCUPQT_H
#define UI_WORLDCUPQT_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WorldCupQtClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *head;
    QPushButton *B_match;
    QPushButton *B_score;
    QPushButton *B_shooter;
    QLineEdit *search;
    QToolButton *toolButton;
    QDateTimeEdit *now;
    QToolButton *toolButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WorldCupQtClass)
    {
        if (WorldCupQtClass->objectName().isEmpty())
            WorldCupQtClass->setObjectName(QStringLiteral("WorldCupQtClass"));
        WorldCupQtClass->resize(598, 419);
        centralWidget = new QWidget(WorldCupQtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        head = new QHBoxLayout();
        head->setSpacing(6);
        head->setObjectName(QStringLiteral("head"));
        B_match = new QPushButton(centralWidget);
        B_match->setObjectName(QStringLiteral("B_match"));

        head->addWidget(B_match);

        B_score = new QPushButton(centralWidget);
        B_score->setObjectName(QStringLiteral("B_score"));

        head->addWidget(B_score);

        B_shooter = new QPushButton(centralWidget);
        B_shooter->setObjectName(QStringLiteral("B_shooter"));

        head->addWidget(B_shooter);

        search = new QLineEdit(centralWidget);
        search->setObjectName(QStringLiteral("search"));

        head->addWidget(search);

        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        head->addWidget(toolButton);

        now = new QDateTimeEdit(centralWidget);
        now->setObjectName(QStringLiteral("now"));
        now->setDate(QDate(2018, 6, 14));

        head->addWidget(now);

        toolButton_2 = new QToolButton(centralWidget);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));

        head->addWidget(toolButton_2);


        verticalLayout->addLayout(head);

        WorldCupQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WorldCupQtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 598, 23));
        WorldCupQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WorldCupQtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WorldCupQtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WorldCupQtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WorldCupQtClass->setStatusBar(statusBar);

        retranslateUi(WorldCupQtClass);
        QObject::connect(B_match, SIGNAL(clicked()), WorldCupQtClass, SLOT(show_match()));
        QObject::connect(toolButton_2, SIGNAL(clicked()), WorldCupQtClass, SLOT(time_change()));
        QObject::connect(B_score, SIGNAL(clicked()), WorldCupQtClass, SLOT(show_score()));
        QObject::connect(toolButton, SIGNAL(clicked()), WorldCupQtClass, SLOT(search()));
        QObject::connect(B_shooter, SIGNAL(clicked()), WorldCupQtClass, SLOT(show_shooter()));

        QMetaObject::connectSlotsByName(WorldCupQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *WorldCupQtClass)
    {
        WorldCupQtClass->setWindowTitle(QApplication::translate("WorldCupQtClass", "WorldCupQt", nullptr));
        B_match->setText(QApplication::translate("WorldCupQtClass", "Match", nullptr));
        B_score->setText(QApplication::translate("WorldCupQtClass", "ScoreBoard", nullptr));
        B_shooter->setText(QApplication::translate("WorldCupQtClass", "ShooterBoard", nullptr));
        toolButton->setText(QApplication::translate("WorldCupQtClass", "...", nullptr));
        now->setDisplayFormat(QApplication::translate("WorldCupQtClass", "yyyy-M-d HH:mm", nullptr));
        toolButton_2->setText(QApplication::translate("WorldCupQtClass", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorldCupQtClass: public Ui_WorldCupQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORLDCUPQT_H
