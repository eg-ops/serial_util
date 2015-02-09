#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QSerialPort>
#include <QMutex>
#include <QWaitCondition>


class WorkerThread : public QObject
{
    Q_OBJECT
private:

protected:


public:
    explicit WorkerThread(QObject *parent = 0);
    ~WorkerThread();

    QSerialPort * serial;
    QMutex serialLock;
    QWaitCondition waiter;
    QByteArray currentCmd;
    QByteArray inputArray;
public slots:
    void readData();

    void sendCommand(QByteArray cmd);

};

#endif // WORKERTHREAD_H
