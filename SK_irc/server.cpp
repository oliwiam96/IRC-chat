#include "server.h"
#include<QMessageBox>

Server::Server():
    tcpSocket(new QTcpSocket())
{
    QObject::connect(tcpSocket, &QIODevice::readyRead, this, &Server::readData);

}

Server::~Server()
{
    delete tcpSocket;
}

void Server::connectToServer(QString ipAddress, qint32 portAddress)
{
    tcpSocket->connectToHost(ipAddress, portAddress);
}

void Server::disconnectFromServer()
{
    tcpSocket->disconnectFromHost();
}

void Server::readData()
{
    char buf[1024];
    while (tcpSocket->canReadLine())
    {
        if( tcpSocket->readLine(buf, 1024)> 0)
        {
            wykonaj_polecenie(buf);
        }
    }

}

void Server::wykonaj_polecenie(char *msg)
{
    char *pch; //a pointer to the beginning of the token
    msg[strlen(msg) -1 ] = '\0'; // usun \n
    printf ("Splitting string \"%s\" into tokens:\n", msg);
    pch = strtok(msg, " ");
    /** MOZLIWE WIADOMOSCI OD SERWERA DO KLIENTA **/
    printf("Pierwszy token: %s\n", pch);
    if(!strcmp(pch, "\\LOGINSUCCESSFUL"))
    {
        QMessageBox::information(0, "Komunikat", "Nastapilo poprawne zalogowanie");
        this->updateRoomsList();
    }
    else if(!strcmp(pch, "\\WRONGPASSWORD"))
    {
        QMessageBox::information(0, "Blad", "Niepoprawny login lub haslo");
    }
    else if(!strcmp(pch, "\\USERNAMEALREADYTAKEN"))
    {
        QMessageBox::information(0, "Blad", "Login zajety, wybierz inny");
    }
    else if(!strcmp(pch, "\\SIGNUPSUCCESSFUL"))
    {
        QMessageBox::information(0, "Komunikat", "Konto utworzone");
        this->updateRoomsList();
    }
    else if(!strcmp(pch, "\\ROOMS"))
    {
        emit clearAllRoomsNames();
        pch = strtok(NULL, " ");
        while(pch != NULL)
        {
            QString *roomName = new QString(pch);
            //mainWindow->addRoomItem(*roomName);
            emit roomNameReceived(*roomName);
            pch = strtok(NULL, " ");
        }


    }
    else if(!strcmp(pch, "\\MSG"))
    {

        pch = strtok(NULL, " ");
        QString *roomName = new QString(pch);
        pch = strtok(NULL, " ");
        QString *userName = new QString(pch);
        pch = strtok(NULL, " ");
        QString msg = pch;
        pch = strtok(NULL, " ");
        while(pch != NULL)
        {
            msg += " ";
            msg += pch;
            pch = strtok(NULL, " ");
        }


        emit msgToRoomReceived(*roomName, *userName, msg);
    }
    else if(!strcmp(pch, "\\CREATEROOMSUCCESSFUL"))
    {
        QMessageBox::information(0, "Komunikat", "Pokoj utworzony");
    }
    else if(!strcmp(pch, "\\ROOMNAMEALREADYTAKEN"))
    {
        QMessageBox::information(0, "Blad", "Istnieje juz pokoj o tej nazwie, wybierz inna");
    }
}

void Server::writeToServer(QString msg)
{
    tcpSocket->write((msg + ";").toLocal8Bit());
}


void Server::updateRoomsList()
{
    writeToServer("\\SHOWROOMS");
}

void Server::login(QString name, QString password)
{
    this->userName = name;
    writeToServer("\\LOGIN " + name + " " + password);
}

void Server::signUp(QString name, QString password)
{
    writeToServer("\\SIGNUP " + name + " " + password);
}

void Server::logout()
{
    writeToServer("\\LOGOUT");
}

void Server::sendMsg(QString msg, QString roomName)
{
    writeToServer("\\MSG " + roomName + " " + msg); //TU BYL BLAD, NIE TRZEBA WYSYLAC USERNAME
}

void Server::enterRoom(QString roomName)
{
    writeToServer("\\ENTERROOM " + roomName);
}

void Server::createRoom(QString roomName)
{
    writeToServer("\\CREATEROOM " + roomName);
}

void Server::leaveRoom(QString roomName)
{
    writeToServer("\\LEAVEROOM " + roomName);
}

void Server::deleteRoom(QString roomName)
{
    writeToServer("\\DELETEROOM " + roomName);
}
