#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>
#include<QDebug>


class Server : public QObject
{
    Q_OBJECT
public:
    Server();
    virtual ~Server();
private:
    QTcpSocket *tcpSocket;
private slots:
    void readData();
};

#endif // SERVER_H
