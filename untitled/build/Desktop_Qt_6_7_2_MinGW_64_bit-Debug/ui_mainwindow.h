/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QCustomPlot *graphic;
    QPushButton *btn_volt;
    QPushButton *btn_current;
    QLineEdit *irms;
    QLineEdit *pot;
    QLineEdit *vrms;
    QPushButton *btn_dat;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphic = new QCustomPlot(centralwidget);
        graphic->setObjectName("graphic");
        graphic->setGeometry(QRect(30, 20, 731, 381));
        btn_volt = new QPushButton(centralwidget);
        btn_volt->setObjectName("btn_volt");
        btn_volt->setGeometry(QRect(660, 430, 80, 24));
        btn_current = new QPushButton(centralwidget);
        btn_current->setObjectName("btn_current");
        btn_current->setGeometry(QRect(660, 470, 80, 24));
        irms = new QLineEdit(centralwidget);
        irms->setObjectName("irms");
        irms->setGeometry(QRect(30, 470, 91, 24));
        pot = new QLineEdit(centralwidget);
        pot->setObjectName("pot");
        pot->setGeometry(QRect(30, 510, 91, 24));
        vrms = new QLineEdit(centralwidget);
        vrms->setObjectName("vrms");
        vrms->setGeometry(QRect(30, 430, 91, 24));
        btn_dat = new QPushButton(centralwidget);
        btn_dat->setObjectName("btn_dat");
        btn_dat->setGeometry(QRect(140, 470, 80, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_volt->setText(QCoreApplication::translate("MainWindow", "plot voltaje", nullptr));
        btn_current->setText(QCoreApplication::translate("MainWindow", "plot corriente", nullptr));
        btn_dat->setText(QCoreApplication::translate("MainWindow", "Ver datos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
