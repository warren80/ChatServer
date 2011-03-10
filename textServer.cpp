#include "textServer.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>


TextServer::TextServer(int port, int bufsize)
    : Component(port, bufsize) {
    pSocket_ = new SocketClass(TCP, port_);

    connect(pSocket_, SIGNAL(SignalClientConnected(char*)),
            this, SLOT(slotClientConnect(char*)));
    connect(pSocket_, SIGNAL(SignalClientDisconnected(char*)),
            this, SLOT(slotClientDisconnect(char*)));
}

void TextServer::Start() {
    if(pSocket_->SetAsServer() == -1) {
        emit connectionError("Cannot start server.");
    } else {
        emit success("Server started.");
    }
}

TextServer::~TextServer() {
    delete pSocket_;
}

void TextServer::slotClientConnect(char *ipAddr) {
    qDebug("Client connected - server slot.");
    MessageStruct * client = new MessageStruct;
    strncpy(client->ipAddr, ipAddr, IPADDRSIZE);

    emit signalShowClientConnected(client);
}

void TextServer::slotClientDisconnect(char *) {

}
