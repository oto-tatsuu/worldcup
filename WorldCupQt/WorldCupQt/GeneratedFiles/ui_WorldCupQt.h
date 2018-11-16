/********************************************************************************
** Form generated from reading UI file 'WorldCupQt.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORLDCUPQT_H
#define UI_WORLDCUPQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WorldCupQtClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WorldCupQtClass)
    {
        if (WorldCupQtClass->objectName().isEmpty())
            WorldCupQtClass->setObjectName(QStringLiteral("WorldCupQtClass"));
        WorldCupQtClass->resize(600, 400);
        menuBar = new QMenuBar(WorldCupQtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        WorldCupQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WorldCupQtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WorldCupQtClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(WorldCupQtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        WorldCupQtClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(WorldCupQtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WorldCupQtClass->setStatusBar(statusBar);

        retranslateUi(WorldCupQtClass);

        QMetaObject::connectSlotsByName(WorldCupQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *WorldCupQtClass)
    {
        WorldCupQtClass->setWindowTitle(QApplication::translate("WorldCupQtClass", "WorldCupQt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorldCupQtClass: public Ui_WorldCupQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORLDCUPQT_H
