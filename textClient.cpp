#include "textClient.h"
#include <QDebug>

TextClient::TextClient(const char* ip, int port, int bufsize)
    : Component(port, bufsize) {
    pSocket = new Socket(TCP, port, bufsize);
    ip_ = new char[16];
    strncpy(ip_,ip, 16);
}

void TextClient::Start() {
    qDebug("Client Started");
    pSocket->SetAsClient(ip_);
    qDebug(ip_);
    char * str = new char[bufSize_]; //may need +1 here not sure

    while (pSocket->rx(str) > 0) {
        //setup structure or something.
        //emit signal
    }
    pSocket->closeSocket();
   // pSocket->SetAsClient(ip);
}

void TextClient::txMessage(const char * str) { //this function is in the gui thread and thats as planned
    pSocket->tx(str);
}

TextClient::~TextClient() {
}

void TextClient::slotTextRecieved(char *) {

}


