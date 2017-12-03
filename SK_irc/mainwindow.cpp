#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    /*

    int rb =0;
    char buf[1024];

    if( tcpSocket->readLine(buf, 1024)> 0)
    {
        cout<<buf<<endl;
        QString czas = buf;
        ui->etykieta_godzina->setText(czas);
    }
    */

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
        ui->textBrowser->setText(ui->textBrowser->toPlainText() +"[ktos] " +ui->lineEdit->text() + "\n");
        ui->lineEdit->setText("");
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
