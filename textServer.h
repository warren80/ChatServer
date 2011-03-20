#ifndef TEXTSERVER_H
#define TEXTSERVER_H

#include <QObject>
#include "socket.h"
#include "component.h"

/**
 * The server class will act as the server where the socket will be created.
 */

class TextServer : public Component {
    Q_OBJECT

public:
    /**
     * The server class constructor where some variables are initialized. Some
     * connections are also done here.
     *
     * @author Karl Castillo, Warren Voelkl
     * @arg port - the port where the  socket will be bound to
     *      bufsize - the size of the struct to be sent
     */
    TextServer(int port, int bufsize);
    /**
     * The destructor of the server class where objects are deleted.
     *
     * @author Karl Castillo
     */
    ~TextServer();
    /**
     * A getter that will return the socket associated with the server.
     *
     * @author Karl Castillo
     * @return the socket class associated with the server
     */
    SocketClass* getSocket();

public slots:
    /**
     * This function is called to start the server session.
     *
     * @author Warren Voelkl
     */
    virtual void Start();

signals:
    /**
     * Emitted when a fatal error occurs during execution.
     */
    void connectionError(const char*);

private:
    /**
     * Holds the socket class associated with the server.
     */
    SocketClass *pSocket_;
};

#endif // TEXTSERVER
