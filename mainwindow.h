#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void sendCommand(QByteArray cmd);

public slots:
    void onSendCmd();
    void readData();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    QByteArray inputArray;
    QMutex serialLock;
    QWaitCondition waiter;
    QByteArray currentCmd;

};

#endif // MAINWINDOW_H
