#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>
#include<QDebug>
#include<QList>
#include<QString>
#include<QObject>


class Server : public QObject
{
    Q_OBJECT
public:
    Server();
    virtual ~Server();
    void connectToServer(QString ipAddress, qint32 portAddress);
    void disconnectFromServer();
    void updateRoomsList();
    void login(QString name, QString password);
    void signUp(QString name, QString password);
    void logout();
    void sendMsg(QString msg, QString roomName);
    void enterRoom(QString roomName);
    void createRoom(QString roomName);
    void leaveRoom(QString roomName);
    void deleteRoom(QString roomName);

private:
    QTcpSocket *tcpSocket;
    QString userName;
    void wykonaj_polecenie(char *msg);
    void writeToServer(QString msg);

private slots:
    void readData();

signals:
    void roomNameReceived(QString roomName);
    void clearAllRoomsNames();
    void msgToRoomReceived(QString roomName, QString userName, QString msg);

};

#endif // SERVER_H
