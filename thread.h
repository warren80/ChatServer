#ifndef THREAD_H
#define THREAD_H

#include <QThread>

/**
 * The thread that will hold the client or server. This will prevent freezing of
 * the GUI.
 */

class Thread : public QThread
{
protected:
    /**
     * Call this function to start the thread.
     *
     * @author Warren Voelkl
     */
    virtual void run();
};

#endif
