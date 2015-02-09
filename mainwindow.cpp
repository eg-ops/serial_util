#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    QThread *thread_New = new QThread;

    worker = new WorkerThread;


    worker->moveToThread(thread_New);
    worker->serial->moveToThread(thread_New);


    connect(ui->sendCmd, SIGNAL(clicked()), this, SLOT(onSendCmd()));
    connect(this, SIGNAL(sendCommand(QByteArray)), worker, SLOT(sendCommand(QByteArray)));

    thread_New->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSendCmd(){
    qDebug() << "onClick Send";
    QByteArray test;
    test.append("test", 4);
    sendCommand(test);
}




