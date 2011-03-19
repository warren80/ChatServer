#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

class Component : public QObject
{
    Q_OBJECT
public:
    /**
     * Constructor that will create an interface for the service(client or server)
     *
     * @author Warren Voelkl
     * @param port - the port where the socket will be bound to
     *        bufsize - the size of the packet
     */
    Component(int port, int bufSize);
    /**
     * A pure virtual method that will start whichever service the user has chosen.
     *
     * @author Warren Voelkl
     */
    virtual void Start() = 0;

protected:
    int bufSize_;
    int port_;

signals:
    void connectionError(const char*);
    void success(const char*);

};

#endif // COMPONENT_H
