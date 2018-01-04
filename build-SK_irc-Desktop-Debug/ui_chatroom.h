/********************************************************************************
** Form generated from reading UI file 'chatroom.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOM_H
#define UI_CHATROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatRoom
{
public:
    QWidget *centralwidget;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QPushButton *pushButtonSend;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChatRoom)
    {
        if (ChatRoom->objectName().isEmpty())
            ChatRoom->setObjectName(QStringLiteral("ChatRoom"));
        ChatRoom->resize(539, 326);
        centralwidget = new QWidget(ChatRoom);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 511, 191));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 230, 361, 29));
        pushButtonSend = new QPushButton(centralwidget);
        pushButtonSend->setObjectName(QStringLiteral("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(410, 230, 85, 29));
        ChatRoom->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChatRoom);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 539, 26));
        ChatRoom->setMenuBar(menubar);
        statusbar = new QStatusBar(ChatRoom);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ChatRoom->setStatusBar(statusbar);

        retranslateUi(ChatRoom);

        QMetaObject::connectSlotsByName(ChatRoom);
    } // setupUi

    void retranslateUi(QMainWindow *ChatRoom)
    {
        ChatRoom->setWindowTitle(QApplication::translate("ChatRoom", "MainWindow", 0));
        pushButtonSend->setText(QApplication::translate("ChatRoom", "Wyslij", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatRoom: public Ui_ChatRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOM_H
