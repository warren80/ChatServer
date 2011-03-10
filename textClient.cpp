#include "textClient.h"
#include <QDebug>
#include <QMessageBox>

TextClient::TextClient(char *ip, char *alias, int port, int bufsize)
    : Component(port, bufsize) {
    pSocket_ = new SocketClass(TCP, port);
    ip_ = new char[strlen(ip)];
    alias_ = new char[strlen(alias)];

    strcpy(ip_, ip);
    strcpy(alias_, alias);
}

void TextClient::Start() {
    qDebug("Client Started");
    MessageStruct * rxMesg = new MessageStruct;

    if(pSocket_->SetAsClient(ip_) == -1) {
        emit connectionError("Cannont connect to server.\n Try again later.");
        return;
    } else {
        emit success("Connected to server.");
    }

    while (pSocket_->rx(rxMesg) > 0) {
        emit signalTextRecieved(rxMesg);
        rxMesg = new MessageStruct;
    }

    pSocket_->closeSocket();
   // pSocket->SetAsClient(ip);
}

void TextClient::txMessage(const QString str) { //this function is in the gui thread and thats as planned
    MessageStruct * txMesg = new MessageStruct;

    qDebug(str.toLatin1().data());

    strncpy(txMesg->data, str.toLatin1().data(), BUFSIZE - IPADDRSIZE -ALIASSIZE );
    strncpy(txMesg->ipAddr,ip_,IPADDRSIZE);
    strncpy(txMesg->alias,alias_, ALIASSIZE);

    if(pSocket_->tx(txMesg) == -1) {
        emit connectionError("Cannot send message to sender.");
    }

    delete txMesg;
}

TextClient::~TextClient() {
    delete ip_;
    delete alias_;
    delete pSocket_;
}

