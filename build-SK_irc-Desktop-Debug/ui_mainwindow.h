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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget_tabs;
    QWidget *tab_connect;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_disconnect;
    QLabel *label_connection_state;
    QLineEdit *lineEdit_IP;
    QLabel *label_IP;
    QLineEdit *lineEdit_port;
    QLabel *label_port;
    QWidget *tab_login;
    QLabel *label_picture;
    QLineEdit *lineEdit_login;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_login;
    QPushButton *pushButton_signup;
    QWidget *tab_rooms;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_enter_room;
    QPushButton *pushButton_delete_room;
    QPushButton *pushButton_refresh;
    QLabel *label_choose;
    QListWidget *listWidget_rooms;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_new_room;
    QPushButton *pushButton_new_room;
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
        tabWidget_tabs = new QTabWidget(centralWidget);
        tabWidget_tabs->setObjectName(QStringLiteral("tabWidget_tabs"));
        tabWidget_tabs->setGeometry(QRect(10, 10, 621, 391));
        tab_connect = new QWidget();
        tab_connect->setObjectName(QStringLiteral("tab_connect"));
        pushButton_connect = new QPushButton(tab_connect);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(30, 170, 221, 29));
        pushButton_disconnect = new QPushButton(tab_connect);
        pushButton_disconnect->setObjectName(QStringLiteral("pushButton_disconnect"));
        pushButton_disconnect->setGeometry(QRect(30, 220, 221, 29));
        label_connection_state = new QLabel(tab_connect);
        label_connection_state->setObjectName(QStringLiteral("label_connection_state"));
        label_connection_state->setGeometry(QRect(40, 290, 181, 21));
        lineEdit_IP = new QLineEdit(tab_connect);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(120, 60, 131, 29));
        label_IP = new QLabel(tab_connect);
        label_IP->setObjectName(QStringLiteral("label_IP"));
        label_IP->setGeometry(QRect(30, 60, 81, 21));
        lineEdit_port = new QLineEdit(tab_connect);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(120, 100, 51, 29));
        lineEdit_port->setAutoFillBackground(false);
        label_port = new QLabel(tab_connect);
        label_port->setObjectName(QStringLiteral("label_port"));
        label_port->setGeometry(QRect(30, 100, 81, 21));
        tabWidget_tabs->addTab(tab_connect, QString());
        tab_login = new QWidget();
        tab_login->setObjectName(QStringLiteral("tab_login"));
        label_picture = new QLabel(tab_login);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        label_picture->setGeometry(QRect(160, 20, 131, 111));
        lineEdit_login = new QLineEdit(tab_login);
        lineEdit_login->setObjectName(QStringLiteral("lineEdit_login"));
        lineEdit_login->setGeometry(QRect(30, 60, 113, 29));
        lineEdit_password = new QLineEdit(tab_login);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(30, 100, 113, 29));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        pushButton_login = new QPushButton(tab_login);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        pushButton_login->setGeometry(QRect(30, 160, 201, 29));
        pushButton_signup = new QPushButton(tab_login);
        pushButton_signup->setObjectName(QStringLiteral("pushButton_signup"));
        pushButton_signup->setGeometry(QRect(30, 210, 201, 29));
        tabWidget_tabs->addTab(tab_login, QString());
        tab_rooms = new QWidget();
        tab_rooms->setObjectName(QStringLiteral("tab_rooms"));
        verticalLayoutWidget = new QWidget(tab_rooms);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(350, 10, 201, 128));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_enter_room = new QPushButton(verticalLayoutWidget);
        pushButton_enter_room->setObjectName(QStringLiteral("pushButton_enter_room"));

        verticalLayout->addWidget(pushButton_enter_room);

        pushButton_delete_room = new QPushButton(verticalLayoutWidget);
        pushButton_delete_room->setObjectName(QStringLiteral("pushButton_delete_room"));

        verticalLayout->addWidget(pushButton_delete_room);

        pushButton_refresh = new QPushButton(verticalLayoutWidget);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));

        verticalLayout->addWidget(pushButton_refresh);

        label_choose = new QLabel(verticalLayoutWidget);
        label_choose->setObjectName(QStringLiteral("label_choose"));

        verticalLayout->addWidget(label_choose);

        listWidget_rooms = new QListWidget(tab_rooms);
        listWidget_rooms->setObjectName(QStringLiteral("listWidget_rooms"));
        listWidget_rooms->setGeometry(QRect(10, 10, 301, 321));
        verticalLayoutWidget_2 = new QWidget(tab_rooms);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(350, 230, 201, 66));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_new_room = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_new_room->setObjectName(QStringLiteral("lineEdit_new_room"));

        verticalLayout_2->addWidget(lineEdit_new_room);

        pushButton_new_room = new QPushButton(verticalLayoutWidget_2);
        pushButton_new_room->setObjectName(QStringLiteral("pushButton_new_room"));
        pushButton_new_room->setAutoDefault(true);
        pushButton_new_room->setDefault(false);

        verticalLayout_2->addWidget(pushButton_new_room);

        tabWidget_tabs->addTab(tab_rooms, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 703, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(lineEdit_new_room, SIGNAL(returnPressed()), pushButton_new_room, SLOT(click()));
        QObject::connect(listWidget_rooms, SIGNAL(itemDoubleClicked(QListWidgetItem*)), pushButton_enter_room, SLOT(click()));

        tabWidget_tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "IRC chat", 0));
        pushButton_connect->setText(QApplication::translate("MainWindow", "Po\305\202\304\205cz z serwerem", 0));
        pushButton_disconnect->setText(QApplication::translate("MainWindow", "Roz\305\202\304\205cz z serwerem / Wyloguj", 0));
        label_connection_state->setText(QApplication::translate("MainWindow", "Stan po\305\202\304\205czenia: ", 0));
        lineEdit_IP->setText(QApplication::translate("MainWindow", "127.0.0.1", 0));
        label_IP->setText(QApplication::translate("MainWindow", "IP serwera:", 0));
        lineEdit_port->setText(QApplication::translate("MainWindow", "1234", 0));
        label_port->setText(QApplication::translate("MainWindow", "port:", 0));
        tabWidget_tabs->setTabText(tabWidget_tabs->indexOf(tab_connect), QApplication::translate("MainWindow", "Po\305\202\304\205cz z serwerem", 0));
        label_picture->setText(QString());
        lineEdit_login->setText(QApplication::translate("MainWindow", "login", 0));
        lineEdit_password->setText(QApplication::translate("MainWindow", "password", 0));
        pushButton_login->setText(QApplication::translate("MainWindow", "Zaloguj", 0));
        pushButton_signup->setText(QApplication::translate("MainWindow", "Utw\303\263rz nowe konto", 0));
        tabWidget_tabs->setTabText(tabWidget_tabs->indexOf(tab_login), QApplication::translate("MainWindow", "Zaloguj", 0));
        pushButton_enter_room->setText(QApplication::translate("MainWindow", "Wejd\305\272 do pokoju", 0));
        pushButton_delete_room->setText(QApplication::translate("MainWindow", "Usun pokoj", 0));
        pushButton_refresh->setText(QApplication::translate("MainWindow", "Od\305\233wie\305\274 liste", 0));
        label_choose->setText(QApplication::translate("MainWindow", "Wybrano:", 0));
        pushButton_new_room->setText(QApplication::translate("MainWindow", "Utw\303\263rz nowy pok\303\263j", 0));
        tabWidget_tabs->setTabText(tabWidget_tabs->indexOf(tab_rooms), QApplication::translate("MainWindow", "Pokoje", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
