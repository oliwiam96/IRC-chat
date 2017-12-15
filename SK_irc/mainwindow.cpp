#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
 #include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    QPixmap myPixmapForNow;
    if(!myPixmapForNow.load("ikona.jpg")){
           qWarning("Failed to load");
    }
    ui->label_5->setPixmap(myPixmapForNow);

    for(int i = 0; i < 15; i++)
    {
        ui->listWidget->addItem("Pokój " + QString::number(i));
        ui->listWidget_2->addItem("Użytkownik " + QString::number(i));

    }
    connect(tcpSocket, &QIODevice::readyRead, this, &MainWindow::readData);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readData()
{
    char buf[1024];
    while (tcpSocket->canReadLine())
    {
        if( tcpSocket->readLine(buf, 1024)> 0)
        {

            ui->textBrowser->setText(ui->textBrowser->toPlainText() +"[ktos] " +buf);
            QScrollBar *sb = ui->textBrowser->verticalScrollBar();
            //ui->textBrowser->setLineWrapMode(QTextBrowser::NoWrap);
            sb->setValue(sb->maximum());
            //ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());


        }

    }



}
void MainWindow::on_buttonNewRoom_clicked()
{
    ui->listWidget->addItem("Nowy pokój");
}

void MainWindow::on_buttonEnterRoom_clicked()
{
    // Get the pointer to the currently selected item.
    QListWidgetItem *item = ui->listWidget->currentItem();
    ui->label_3->setText("Wybrano: " + item->text());

}

void MainWindow::on_buttonSend_clicked()
{
    if(ui->lineEdit->text() != "")
    {
        //ui->lineEdit->text()
        tcpSocket->write((ui->lineEdit->text() + ";").toLocal8Bit());
        ui->textBrowser->setText(ui->textBrowser->toPlainText() +"[Ty] " + ui->lineEdit->text() + "\n");

        ui->lineEdit->setText("");
        QScrollBar *sb = ui->textBrowser->verticalScrollBar();
        //ui->textBrowser->setLineWrapMode(QTextBrowser::NoWrap);
        sb->setValue(sb->maximum());
    }

}

void MainWindow::on_buttonConnect_clicked()
{
    tcpSocket->connectToHost("127.0.0.1", 1234);
    ui->labelConnection->setText("Otwarto połączenie!");
}

void MainWindow::on_buttonDisconnect_clicked()
{
    tcpSocket->disconnectFromHost();
    ui->labelConnection->setText("Zamknięto połączenie!");
}

void MainWindow::on_pushButton_2_clicked()
{
    QString wiadomosc_logowania = "\\LOGIN ";
    wiadomosc_logowania += ui->lineEdit_login->text() + " ";
    wiadomosc_logowania += ui->lineEdit_password->text() + ";";
    tcpSocket->write(wiadomosc_logowania.toLocal8Bit());

}
