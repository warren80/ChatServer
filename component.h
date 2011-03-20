#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

/**
 * An interface class that will hold necessary information about the socket.
 */
class Component : public QObject
{
    Q_OBJECT
public:
    /**
     * Constructor that will create an interface for the service(client or server)
     *
     * @author Warren Voelkl
     * @arg port - the port where the socket will be bound to
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
    /**
     * The size of the packets that is to be sent.
     */
    int bufSize_;
    /**
     * The port in which the socket is bound to.
     */
    int port_;

signals:
    /**
     * Emitted when a fatal error occurs during execution.
     */
    void connectionError(const char*);
    /**
     * Emitted when creating the socket descriptor did not produce any error.
     */
    void success(const char*);

};

#endif // COMPONENT_H
