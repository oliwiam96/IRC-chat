#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include <QtNetwork>

#include "server.h"
#include "chatroom.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_connect_clicked();

    void on_pushButton_disconnect_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_signup_clicked();

    void on_pushButton_enter_room_clicked();

    void on_pushButton_delete_room_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_new_room_clicked();


    void addRoomItem(QString roomName);
    void deleteAllRommsItems();
    void dispalyMsgInRoom(QString roomName, QString userName, QString msg);

private:
    Ui::MainWindow *ui;
    Server *server;
    QList<ChatRoom*> *rooms;

    void addNewRoomWindow(QString roomName);
    ChatRoom* getRoomWindow(QString roomName);
    void deleteRoomWindow(QString roomName);
    void deleteAllRoomsWindows();
};

#endif // MAINWINDOW_H
