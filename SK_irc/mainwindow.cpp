#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QScrollBar>
#include <QMessageBox>
#include <QCloseEvent>

#include "server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    server(new Server())
{

    rooms = new QList<ChatRoom*>();
    QObject::connect(server, SIGNAL(roomNameReceived(QString)),
                         this, SLOT(addRoomItem(QString)));

    QObject::connect(server, SIGNAL(clearAllRoomsNames()),
                         this, SLOT(deleteAllRommsItems()));

    QObject::connect(server, SIGNAL(msgToRoomReceived(QString,QString,QString)),
                         this, SLOT(dispalyMsgInRoom(QString,QString,QString)));
    ui->setupUi(this);

    QPixmap myPixmapForNow;
    if(!myPixmapForNow.load("ikona.jpg")){
           qWarning("Failed to load");
    }
    ui->label_picture->setPixmap(myPixmapForNow);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete server;
    deleteAllRoomsWindows();
}


void MainWindow::addRoomItem(QString roomName)
{
    ui->listWidget_rooms->addItem(roomName);
}

void MainWindow::deleteAllRommsItems()
{
    ui->listWidget_rooms->clear();
}

void MainWindow::addNewRoomWindow(QString roomName)
{
    ChatRoom *room = new ChatRoom(this, roomName, server);
    room->show();
    rooms->append(room);

}

ChatRoom* MainWindow::getRoomWindow(QString roomName)
{
    for(int i = 0; i < rooms->size(); i++)
    {
        if((rooms->at(i))->getRoomName() == roomName)
        {
            return rooms->at(i);
        }
    }
    return NULL;
}

void MainWindow::deleteRoomWindow(QString roomName)
{
    ChatRoom *room = getRoomWindow(roomName);
    rooms->removeOne(room);
    delete room;

}

void MainWindow::dispalyMsgInRoom(QString roomName, QString userName, QString msg)
{
    ChatRoom *room = getRoomWindow(roomName);
    room->receiveMsg(userName, msg);

}

void MainWindow::deleteAllRoomsWindows()
{
   while(rooms->size() > 0)
   {
       ChatRoom *room = rooms->at(0);
       rooms->removeAt(0);
       if(room)
        delete room;
   }
}

void MainWindow::on_pushButton_connect_clicked()
{
    ui->label_connection_state->setText("Otwarto połączenie!");
    qint32 port = ui->lineEdit_port->text().toInt();
    server->connectToServer(ui->lineEdit_IP->text(), port);
    qDebug() << ui->lineEdit_IP->text();
    qDebug() << port;
    QMessageBox::information(0, "Komunikat", "Otwarto polaczenie");
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    ui->label_connection_state->setText("Zamknieto połączenie!");
    server->disconnectFromServer();
}

void MainWindow::on_pushButton_login_clicked()
{
    server->login(ui->lineEdit_login->text(), ui->lineEdit_password->text());
}

void MainWindow::on_pushButton_signup_clicked()
{
    server->signUp(ui->lineEdit_login->text(), ui->lineEdit_password->text());
}

void MainWindow::on_pushButton_enter_room_clicked()
{
    // Get the pointer to the currently selected item.
    QListWidgetItem *item = ui->listWidget_rooms->currentItem();
    if(item)
    {
        ui->label_choose->setText("Wejdz: " + item->text());
        server->enterRoom(item->text());
        addNewRoomWindow(item->text());
    }

}

void MainWindow::on_pushButton_delete_room_clicked()
{
    // Get the pointer to the currently selected item.
    QListWidgetItem *item = ui->listWidget_rooms->currentItem();
    if(item)
    {
        ui->label_choose->setText("Usun: " + item->text());
        server->deleteRoom(item->text());
        server->updateRoomsList();
    }
}

void MainWindow::on_pushButton_refresh_clicked()
{
    server->updateRoomsList();
}

void MainWindow::on_pushButton_new_room_clicked()
{
    server->createRoom(ui->lineEdit_new_room->text());
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Potwierdzenie zamknięcia aplikacji",
                                                                tr("Czy pewno chcesz opuścić komunikator?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        qDebug() << "Close event - zamykanie komunikatora";
    }
//    server->leaveRoom(roomName);
}
