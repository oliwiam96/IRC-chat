#include "server.h"

Server::Server():
    tcpSocket(new QTcpSocket())
{
    QObject::connect(tcpSocket, &QIODevice::readyRead, this, &Server::readData);

}

Server::~Server()
{
    delete tcpSocket;
}

void Server::readData()
{
    char buf[1024];
    while (tcpSocket->canReadLine())
    {
        if( tcpSocket->readLine(buf, 1024)> 0)
        {


            /*
            ui->textBrowser->setText(ui->textBrowser->toPlainText() +"[ktos] " +buf);
            QScrollBar *sb = ui->textBrowser->verticalScrollBar();
            //ui->textBrowser->setLineWrapMode(QTextBrowser::NoWrap);
            sb->setValue(sb->maximum());
            //ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());
            */
        }
    }

}
