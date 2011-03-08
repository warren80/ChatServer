#include "textServer.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>


TextServer::TextServer(int port) {
    //code to init socket

}

void TextServer::Start() {
    //code to start server
}

TextServer::~TextServer() {
}

void TextServer::slotClientConnect(char *) {

}

void TextServer::slotClientDisconnect(char *) {

}
