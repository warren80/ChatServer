#include "textServer.h"

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

void TextServer::Stop() {
    qDebug("Server Disonnected");
    pSocket_->closeSocket();
}
