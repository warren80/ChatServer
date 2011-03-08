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
    pSocket = new Socket(TCP, port_, bufSize_);

}

void TextServer::Start() {
    pSocket->SetAsServer();
}

TextServer::~TextServer() {
}

void TextServer::slotClientConnect(char *) {

}

void TextServer::slotClientDisconnect(char *) {

}
