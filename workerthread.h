#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QSerialPort>

class WorkerThread : public QThread
{
    Q_OBJECT
private:

protected:

    virtual void run();

public:
    WorkerThread();
    ~WorkerThread();
};

#endif // WORKERTHREAD_H
