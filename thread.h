#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
protected:
    virtual void run();
};

#endif
