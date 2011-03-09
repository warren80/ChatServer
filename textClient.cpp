#include "textClient.h"
#include <QDebug>
#include <QMessageBox>

TextClient::TextClient(const char* ip, int port, int bufsize)
    : Component(port, bufsize) {
    pSocket_ = new SocketClass(TCP, port, bufsize);
    ip_ = new char[16];
    strncpy(ip_,ip, 16);
}

void TextClient::Start() {
    qDebug("Client Started");
    if(pSocket_->SetAsClient(ip_) == -1) {
        emit connectionError("Cannont connect to server.\n Try again later.");
        return;
    } else {
        emit success("Connected to server.");
    }
    qDebug(ip_);
    char * str = new char[bufSize_]; //may need +1 here not sure

    while (pSocket_->rx(str) > 0) {
        //setup structure or something.
        //emit signal
    }
    pSocket_->closeSocket();
   // pSocket->SetAsClient(ip);
}

void TextClient::txMessage(const QString str) { //this function is in the gui thread and thats as planned
    pSocket_->tx(str);
}

TextClient::~TextClient() {
}

void TextClient::slotTextRecieved(char *) {

}


