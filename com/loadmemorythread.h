#ifndef LOADMEMORYTHREAD_H
#define LOADMEMORYTHREAD_H
#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include "modeltreenode.h"

class LoadMemoryThread : public QThread
{
    Q_OBJECT
public:
    LoadMemoryThread();
    bool stopped;

protected:
    void run();
    void stop();

};

#endif // LOADMEMORYTHREAD_H
