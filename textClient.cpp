#include "textClient.h"
#include <QDebug>
#include <QMessageBox>

TextClient::TextClient(char *ip, char *alias, int port, int bufsize)
    : Component(port, bufsize) {
    pSocket_ = new SocketClass(TCP, port, bufsize);
    ip_ = new char[strlen(ip)];
    alias_ = new char[strlen(alias)];

    strcpy(ip_, ip);
    strcpy(alias_, alias);
}

void TextClient::Start() {
    qDebug("Client Started");
    PMESGSPECS mesg;
    PMESSAGESTRUCT rxMesg = new MESSAGESTRUCT;

    if(pSocket_->SetAsClient(ip_) == -1) {
        emit connectionError("Cannont connect to server.\n Try again later.");
        return;
    } else {
        emit success("Connected to server.");
    }

    while (pSocket_->rx(rxMesg) > 0) {
        mesg = new MESGSPECS;

        if(strcmp(rxMesg->alias, "Local") == 0) {
            mesg->sender = rxMesg->alias;
        } else {
            mesg->sender = rxMesg->ipAddr;
        }

        emit signalTextRecieved(mesg);
    }

    pSocket_->closeSocket();
   // pSocket->SetAsClient(ip);
}

void TextClient::txMessage(const QString str) { //this function is in the gui thread and thats as planned
    PMESSAGESTRUCT txMesg = new MESSAGESTRUCT;

    qDebug(str.toLatin1().data());

    strncpy(txMesg->data, str.toLatin1().data(), sizeof(char) * 1024);
    strncpy(txMesg->ipAddr,ip_,sizeof(char) * 16);
    strncpy(txMesg->alias,alias_, sizeof(char) * 32);

    if(pSocket_->tx(txMesg) == -1) {
        emit connectionError("Cannot send message to serer.");
    }

    delete txMesg;
}

TextClient::~TextClient() {
    delete ip_;
    delete alias_;
    delete pSocket_;
}

