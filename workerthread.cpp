#include "workerthread.h"


WorkerThread::WorkerThread(QObject *parent ) : QObject(parent)
{

    serial = new QSerialPort();
    serial->setPortName(QString("COM5"));
    if (serial->open(QIODevice::ReadWrite)){
        qDebug() << "opened";
    }
    bool success = serial->setBaudRate(115200) &
                serial->setStopBits(QSerialPort::OneStop) &
                serial->setDataBits(QSerialPort::Data8) &
                serial->setParity(QSerialPort::NoParity) &
                serial->setFlowControl(QSerialPort::NoFlowControl);
    qDebug() << success;

    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));


}

WorkerThread::~WorkerThread()
{

}

void WorkerThread::sendCommand(QByteArray cmd)
{
    serialLock.lock();

    currentCmd = cmd;
    serial->write(cmd);

    qDebug() << "msg sent" << QThread::currentThreadId() ;
    //waiter.wait(&serialLock);


    currentCmd.clear();
    serialLock.unlock();
}

void WorkerThread::readData(){
    qDebug() << "before lock read"  << QThread::currentThreadId();
    serialLock.lock();

    qDebug() << "read";
    QByteArray buff = serial->readAll();
    inputArray.append(buff);

    if (!currentCmd.isEmpty() && inputArray.startsWith(currentCmd)){
        inputArray.remove(0, currentCmd.size());
        qDebug() << "response:" << inputArray;
        waiter.wakeAll();
    } else {
        qDebug() << "Unexpected response" << buff;
    }

    serialLock.unlock();


}

