#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "workerthread.h"

#include <QMainWindow>
#include <QSerialPort>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void onSendCmd();


private:
    Ui::MainWindow *ui;
    WorkerThread * worker;



signals:
   void sendCommand(QByteArray cmd);


};

#endif // MAINWINDOW_H
