#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial.setPortName(QString("COM5"));
    serial.open(QIODevice::ReadWrite);
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ui->sendCmd, SIGNAL(clicked()), this, SLOT(onSendCmd()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSendCmd(){
    QByteArray test;
    test.append("test", 4);
    sendCommand(test);
}

void MainWindow::sendCommand(QByteArray cmd)
{
    serialLock.lock();

    currentCmd = cmd;
    serial.write(cmd);
    qDebug() << "msg sent";
    waiter.wait(&serialLock);


    currentCmd.clear();
    serialLock.unlock();
}

void MainWindow::readData(){

    QByteArray buff = serial.readAll();
    inputArray.append(buff);

    if (!currentCmd.isEmpty() && inputArray.startsWith(currentCmd)){
        inputArray.remove(0, currentCmd.size());
        qDebug() << "response:" << inputArray;
        waiter.wakeAll();
    } else {
        qDebug() << "Unexpected response";
    }



}
