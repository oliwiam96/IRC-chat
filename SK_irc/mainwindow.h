#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readData();

    void on_buttonNewRoom_clicked();

    void on_buttonEnterRoom_clicked();

    void on_buttonSend_clicked();

    void on_buttonConnect_clicked();

    void on_buttonDisconnect_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
};

#endif // MAINWINDOW_H
