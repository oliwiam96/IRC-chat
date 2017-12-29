#ifndef CHATROOM_H
#define CHATROOM_H

#include <QMainWindow>
#include <QString>
#include "server.h"
namespace Ui {
class ChatRoom;
}

class ChatRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = 0, QString roomName = "", Server *server = 0);
    ~ChatRoom();
    QString getRoomName();
    void setRoomName(QString roomName);
    void receiveMsg(QString userName, QString msg);

private slots:
    void on_pushButtonSend_clicked();

private:
    Ui::ChatRoom *ui;
    QString roomName;
    Server *server;

};

#endif // CHATROOM_H
