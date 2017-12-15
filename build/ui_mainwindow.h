/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget_2;
    QWidget *tabWidget_2Page1;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonNewRoom;
    QPushButton *buttonEnterRoom;
    QListWidget *listWidget;
    QLabel *label_3;
    QWidget *tab;
    QListWidget *listWidget_2;
    QWidget *tab_2;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_login;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_2;
    QPushButton *buttonSend;
    QTextBrowser *textBrowser;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *buttonConnect;
    QPushButton *buttonDisconnect;
    QLabel *labelConnection;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(703, 472);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget_2 = new QTabWidget(centralWidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(10, 10, 441, 241));
        tabWidget_2Page1 = new QWidget();
        tabWidget_2Page1->setObjectName(QStringLiteral("tabWidget_2Page1"));
        verticalLayoutWidget = new QWidget(tabWidget_2Page1);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(250, 10, 160, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        buttonNewRoom = new QPushButton(verticalLayoutWidget);
        buttonNewRoom->setObjectName(QStringLiteral("buttonNewRoom"));

        verticalLayout->addWidget(buttonNewRoom);

        buttonEnterRoom = new QPushButton(verticalLayoutWidget);
        buttonEnterRoom->setObjectName(QStringLiteral("buttonEnterRoom"));

        verticalLayout->addWidget(buttonEnterRoom);

        buttonEnterRoom->raise();
        buttonNewRoom->raise();
        listWidget = new QListWidget(tabWidget_2Page1);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 211, 191));
        label_3 = new QLabel(tabWidget_2Page1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(240, 140, 171, 31));
        tabWidget_2->addTab(tabWidget_2Page1, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        listWidget_2 = new QListWidget(tab);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(10, 10, 221, 191));
        tabWidget_2->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 20, 81, 21));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(270, 20, 131, 111));
        lineEdit_login = new QLineEdit(tab_2);
        lineEdit_login->setObjectName(QStringLiteral("lineEdit_login"));
        lineEdit_login->setGeometry(QRect(30, 60, 113, 29));
        lineEdit_password = new QLineEdit(tab_2);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(30, 100, 113, 29));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 150, 85, 29));
        tabWidget_2->addTab(tab_2, QString());
        buttonSend = new QPushButton(centralWidget);
        buttonSend->setObjectName(QStringLiteral("buttonSend"));
        buttonSend->setGeometry(QRect(50, 350, 86, 29));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(310, 280, 341, 111));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 260, 191, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 250, 161, 21));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 310, 211, 31));
        buttonConnect = new QPushButton(centralWidget);
        buttonConnect->setObjectName(QStringLiteral("buttonConnect"));
        buttonConnect->setGeometry(QRect(500, 70, 171, 29));
        buttonDisconnect = new QPushButton(centralWidget);
        buttonDisconnect->setObjectName(QStringLiteral("buttonDisconnect"));
        buttonDisconnect->setGeometry(QRect(500, 120, 171, 29));
        labelConnection = new QLabel(centralWidget);
        labelConnection->setObjectName(QStringLiteral("labelConnection"));
        labelConnection->setGeometry(QRect(470, 180, 181, 21));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(500, 20, 171, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 703, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "IRC chat", 0));
        buttonNewRoom->setText(QApplication::translate("MainWindow", "Utw\303\263rz nowy pok\303\263j", 0));
        buttonEnterRoom->setText(QApplication::translate("MainWindow", "Wejd\305\272 do pokoju", 0));
        label_3->setText(QApplication::translate("MainWindow", "Wybrano:", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tabWidget_2Page1), QApplication::translate("MainWindow", "Pokoje", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QApplication::translate("MainWindow", "U\305\274ytkownicy", 0));
        label_4->setText(QApplication::translate("MainWindow", "Tw\303\263j profil", 0));
        label_5->setText(QString());
        lineEdit_login->setText(QApplication::translate("MainWindow", "login", 0));
        lineEdit_password->setText(QApplication::translate("MainWindow", "password", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Zaloguj", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QApplication::translate("MainWindow", "Profil", 0));
        buttonSend->setText(QApplication::translate("MainWindow", "Wy\305\233lij", 0));
        label->setText(QApplication::translate("MainWindow", "Wprowad\305\272 tekst wiadomo\305\233ci", 0));
        label_2->setText(QApplication::translate("MainWindow", "Czat ka\305\274dy z ka\305\274dym", 0));
        buttonConnect->setText(QApplication::translate("MainWindow", "Po\305\202\304\205cz z serwerem", 0));
        buttonDisconnect->setText(QApplication::translate("MainWindow", "Roz\305\202\304\205cz z serwerem", 0));
        labelConnection->setText(QApplication::translate("MainWindow", "Stan po\305\202\304\205czenia: ", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Od\305\233wie\305\274", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
