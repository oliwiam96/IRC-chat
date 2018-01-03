#include "chatroom.h"
#include "ui_chatroom.h"
#include "hashcolour.h"

#include <QScrollBar>
#include <QCloseEvent>
#include <string.h>
#include <QMessageBox>
using namespace std;

ChatRoom::ChatRoom(QWidget *parent, QString roomName, Server *server) :
    QMainWindow(parent),
    ui(new Ui::ChatRoom)
{
    qDebug() << "Konstruktor ChatRoomu";
    ui->setupUi(this);
    this->server = server;
    setRoomName(roomName);

    QPalette pal = palette();

    // set black background
    ui->textBrowser->setStyleSheet("background-color:black;");
    ui->textBrowser->show();
}

ChatRoom::~ChatRoom()
{
    qDebug() << "Destruktor ChatRoomu";
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
        QString styledString = "<span style=\" font-weight:800; color:#FFFFFF;\" >";
        styledString += +"[ja] </span>";
        styledString += "<span style=\" color:#FFFFFF;\" >";
        styledString += ui->lineEdit->text() + "</span>";
        styledString += "\n";


        ui->textBrowser->setHtml(ui->textBrowser->toHtml() + styledString);
        ui->lineEdit->setText("");
        QScrollBar *sb = ui->textBrowser->verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}



void ChatRoom::receiveMsg(QString userName, QString msg)
{
    QString html = ui->textBrowser->toHtml();

    HashColour *hashcolour = new HashColour();
    QString colorString = QString::fromUtf8((hashcolour->hashColour(userName)).c_str());

    QString styledString = "<span style=\" font-weight:800; color:" + colorString + ";\" >";
    styledString += +"[" + userName + "] " + "</span>";
    styledString += "<span style=\" color:" + colorString + ";\" >";
    styledString += msg + "</span>";
    styledString += "\n";

    ui->textBrowser->setHtml(html + styledString);
    QScrollBar *sb = ui->textBrowser->verticalScrollBar();
    sb->setValue(sb->maximum());
    delete hashcolour;
}



void ChatRoom::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Wyjście z czatu",
                                                                tr("Czy pewno chcesz opuścić czat?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
    server->leaveRoom(roomName);
    qDebug() << "Close event - zamykanie okna";
}

