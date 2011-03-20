#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#include <QObject>
#include "socket.h"
#include "component.h"

/**
 * The client class will act as the client where the socket will be created.
 */

class TextClient : public Component {
    Q_OBJECT

public:
    /**
     * The client class constructor where some variables are initialized. Some
     * connections are also done here.
     *
     * @author Karl Castillo, Warren Voelkl
     * @arg ip - the ip address of the server
     *      alias - the alias of the user
     *      port - the port where the  socket will be bound to
     *      bufsize - the size of the struct to be sent
     */
    TextClient(char *ip, char *alias, int port, int bufsize);
    /**
     * The destructor of the client class where objects are deleted.
     *
     * @author Karl Castillo
     */
    ~TextClient();
    /**
     * Call this function to send a message to through the socket.
     *
     * @author Karl Castillo, Warren Voelkl
     * @arg mesg - the struct that will be transmitted
     */
    void txMessage(const QString mesg);
    /**
     * A getter that will return the socket associated with the client.
     *
     * @author Karl Castillo
     * @return the socket class associated with the client
     */
    SocketClass* getSocket();

public slots:
    /**
     * This function is called to start the client session.
     *
     * @author Warren Voelkl
     */
    virtual void Start();

signals:
    /**
     * Emitted when a message is received.
     */
    void signalTextRecieved(MessageStruct *);
    /**
     * Emitted when the server closed.
     */
    void signalServerClosed();

private:
    /**
     * Holds the ip address of the server.
     */
    char *ip_;
    /**
     * Holds the alias chosen by the user.
     */
    char *alias_;
    /**
     * Holds the socket class associated with the client.
     */
    SocketClass *pSocket_;
};

#endif // TEXTCLIENT
