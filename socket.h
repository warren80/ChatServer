#ifndef SOCKET_H
#define SOCKET_H

#include <QString>

#include <stdio.h>
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <QtGui>
#include <QFile>

#define TCP 1
#define UDP 2

#define BUFSIZE     1024
#define IPADDRSIZE  16
#define ALIASSIZE   32

/**
 * A generic socket class where the socket will be created or destroyed. This is
 * also where messages are to be transmitted or received.
 *
 * This is a multicast socket that uses select for efficiency and performance.
 */

struct MessageStruct {
    int mesgType; //0 text, 1 voice, 2 stream, 3 file
    char ipAddr[16];
    char alias[32];
    char data[BUFSIZE - IPADDRSIZE - ALIASSIZE];
};

class SocketClass : public QObject {
    Q_OBJECT
public:
    /**
     * The socket class constructor where some variables are initialized. Some
     * connections are also done here.
     *
     * @author Karl Castillo, Warren Voelkl
     * @arg type - the type of service (client or server)
     *      port - the port in which the socket will be bound to
     */
    SocketClass(int type, int port);
    /**
     * This method will create a socket that will be used by the client. This
     * method will only be called if the user specified the application to be
     * client.
     *
     * @author Warren Voelkl
     * @arg str - the type of protocol to be used (TCP or UDP)
     * @return 0 - if no error occurs
     *         -1 - if an error occurs
     */
    int SetAsClient(const char *str);
    /**
     * This method will create a socket that will be used by the server. This
     * method will only be called if the user specified the application to be
     * server.
     *
     * @author Warren Voelkl
     * @return 0 - if no error occurs
     *         -1 - if an error occurs
     */
    int SetAsServer();
    /**
     * Call this method to send a message to the client.
     *
     * @author Warren Voelkl
     * @arg mesg - the struct that will be transmitted
     * @return 0 - if no error occurs
     *         -1 - if an error occurs
     */
    int tx(MessageStruct *mesg);
    /**
     * An overload of the tx method.
     *
     * @author Warren Voelkl
     * @arg mesg - the struct that will be trasmitted
     *      length - the length of the struct to be transmitted
     * @return 0 - if no error occurs
     *         -1 - if an error occurs
     */
    int tx(MessageStruct *mesg, int length);
    /**
     * An overload of the tx method.
     *
     * @author Karl Castillo
     * @arg mesg - the struct that will be trasmitted
     *      length - the length of the struct to be transmitted
     *      socketDescriptor - the socket where the struct is to be transmitted
     * @return 0 - if no error occurs
     *         -1 - if an error occurs
     */
    int tx(MessageStruct *mesg, int length, int socketDescriptor);
    /**
     * This is a blocked method and will only unblock if a message is received or
     * other socket operation is going on.
     *
     * @author Karl Castillo, Warren Voelkl
     * @arg mesg - the struct where the message received will be stored
     * @return 0 - if no error occurs
     *         -1 - if an error occurs
     */
    int rx(MessageStruct *mesg);
    /**
     * Call this method to close the socket descriptor.
     *
     * @author Karl Castillo, Warren Voelkl
     */
    void closeSocket();
private:
    /**
     * Call this method to create a TCP socket drescriptor.
     *
     * @author Warren Voelkl
     */
    void createTCPSocket();
    /**
     * Call this method to create a UDP socket descriptor.
     *
     * @author Warren Voelkl
     */
    void createUDPSocket();
    /**
     * Call this method to start listening for clients as a TCP server. This will
     * be a multicast server that makes use of select.
     *
     * @author Karl Castillo, Warren Voelkl
     * @return 0 - if no error occurs
     *         -1 - if an error occurs
     */
    int TCPServer();
    /**
     * Not implemented.
     */
    int UDPServer();
    /**
     * Call this method to setup the socket descriptor.
     *
     * @author Warren Voelkl
     * @arg str - determines whether the socket is for a server or for a client
     * @return 0 - if no error occurs
     *         -1 - if an error occurs
     */
    int SetupSocket(const char *str);
    /**
     * This method is called to send the message received by the server to the
     * other clients.
     *
     * @author Warren Voelkl
     * @arg maxi - the max index of the client array
     *      client - the array of clients
     *      recieveSocketDescriptor - the socket descriptor of the client that
     *                                sent the message
     *      mesg - the struct that is to be sent to the clients
     */
    void writeToEveryoneElse(int maxi, int client[FD_SETSIZE],
             int recieveSocketDescriptor, MessageStruct * mesg);
    /**
     * This method is called to write a message to the log either in the error
     * log or server log.
     *
     * @author Karl Castillo
     * @arg log - the file descriptor of the log file
     *      logMesg - the message that is to be written to the file
     */
    void writeToLog(QFile *log, QString logMesg);
    /**
     * The file descriptor of the server log.
     */
    QFile *log_;
    /**
     * The file descriptor of the error log.
     */
    QFile *errorLog_;
    /**
     * The length of the struct that will be sent.
     */
    int buflen_;
    /**
     * The type of socket (TCP or UDP).
     */
    int socketType_;
    /**
     * The port where the socket will be bound to.
     */
    int sPort_;
    /**
     * The sockaddrs for the client and server.
     */
    struct sockaddr_in client_, server_;
    /**
     * The length of the server sockaddr.
     */
    int serverLength_;
    /**
     * The socket descriptor of the application.
     */
    int socketDescriptor_;

signals:
    /**
     * Emitted if a client connects to the server.
     */
    void signalClientConnected(QString);
    /**
     * Emitted if a client disconnects from the server.
     */
    void signalClientDisconnected(QString);

};

#endif
