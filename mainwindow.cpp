#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    enableChat(false);
}

void MainWindow::slotClientConnected(ClientConnect*) {

}

void MainWindow::slotTextRecieved(TextReceived*) {

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage() {
    QString message = ui->typeScreen->toPlainText();

    if(message != "") {
        printF(settings->alias + ": " + QTime::currentTime().toString()
               + "\n" + message + "\n");
    }

    ui->typeScreen->clear();
}

void MainWindow::printF(const char *message) {
    ui->chatScreen->appendPlainText(QString(*message));
}

void MainWindow::printF(QString message) {
    ui->chatScreen->appendPlainText(message);
}

void MainWindow::on_actionExit_triggered() {
    close();
}

void MainWindow::on_actionConnect_triggered() {
    Settings *settingsDiag = new Settings(this);

    settingsDiag->exec();

    settings = settingsDiag->getSettings();

    if(settingsDiag->result()) {
        //TODO: Connect to server/Listen for clients
        if(settings->isClient) {
            //move these to be started when button pressed in gui
            qDebug("Client");
            setWindowTitle("Los Ostrich - Client");
            enableChat(true);

            qDebug(settings->ipAddr.toLatin1().data());
            qDebug(QString::number(settings->port).toLatin1().data());
            qDebug(settings->alias.toLatin1().data());

            //TODO get a port from gui and ip just a hack here to make it compile
            char *ip = settings->ipAddr.toLatin1().data();
            TextClient * tc = new TextClient(ip, settings->port, BUFSIZE);
            textClient = new Thread();
            textClient->start();
            connect(tc,SIGNAL(signalTextRecieved(TextReceived*)),
                    this,SLOT(slotTextRecieved(TextReceived*)));
            tc->moveToThread(textClient);
            connect(this, SIGNAL(startSignalClient()), tc, SLOT(Start()));
            emit startSignalClient();
        } else {
            qDebug("Server");
            setWindowTitle("Los Ostrich - Server");
            enableChat(false);

            qDebug(QString::number(settings->port).toLatin1().data());

            TextServer * ts = new TextServer(settings->port, BUFSIZE);
            textServer = new Thread();
            textServer->start();
            connect(ts,SIGNAL(signalClientConnected(ClientConnect*)),
                    this,SLOT(slotClientConnected(ClientConnect*)));
            ts->moveToThread(textServer);
            connect(this, SIGNAL(startSignalServer()), ts, SLOT(Start()));
            emit startSignalServer();
        }
    } else {
        qDebug("Settings Cancelled");
    }
}

void MainWindow::enableChat(bool enable) {
    ui->sendButton->setEnabled(enable);
    ui->typeScreen->setEnabled(enable);
}
