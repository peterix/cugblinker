#include "conthread.h"

ConThread::ConThread(QObject *parent) :
    QThread(parent)
{
}

void ConThread::run()
{
    sleep(5);
}

void ConThread::connect()
{
    start();
}

void ConThread::disconnect()
{
    start();
}
