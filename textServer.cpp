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
}

void TextServer::Start() {
    if(pSocket_->SetAsServer() == -1) {
        emit connectionError("Cannot start server. Check error log for details.");
    }
}

TextServer::~TextServer() {
    delete pSocket_;
}
