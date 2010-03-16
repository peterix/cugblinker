#ifndef CONTHREAD_H
#define CONTHREAD_H

#include <QThread>

class ConThread : public QThread
{
Q_OBJECT
public:
    explicit ConThread(QObject *parent = 0);
    void run();

signals:

public slots:
    void connect();
    void disconnect();

};

#endif // CONTHREAD_H
