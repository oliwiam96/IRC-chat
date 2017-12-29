#include "chatroom.h"
#include "ui_chatroom.h"

#include <QScrollBar>

ChatRoom::ChatRoom(QWidget *parent, QString roomName, Server *server) :
    QMainWindow(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    this->server = server;
    setRoomName(roomName);
}

ChatRoom::~ChatRoom()
{
    delete ui;
}

void ChatRoom::setRoomName(QString roomName)
{
    this->roomName = roomName;
    this->setWindowTitle(roomName);
}
QString ChatRoom::getRoomName()
{
    return this->roomName;
}

void ChatRoom::on_pushButtonSend_clicked()
{
    if(ui->lineEdit->text() != "")
    {
        server->sendMsg(ui->lineEdit->text(), roomName);

        ui->textBrowser->setText(ui->textBrowser->toPlainText() +"[ja] " + ui->lineEdit->text() + "\n");
        ui->lineEdit->setText("");
        QScrollBar *sb = ui->textBrowser->verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}
void ChatRoom::receiveMsg(QString userName, QString msg)
{

    ui->textBrowser->setText(ui->textBrowser->toPlainText() +"[" + userName + "] " + msg + "\n");
    QScrollBar *sb = ui->textBrowser->verticalScrollBar();
    sb->setValue(sb->maximum());
}
