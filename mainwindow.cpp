#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    enableChat(false);
}

void MainWindow::slotClientConnected(ClientSpecs * client) {
    qDebug("Client connected");
    printF("Conncted: " + QString(client->ipAddr) + "~"
           + QTime::currentTime().toString());

    delete client;
}

void MainWindow::slotTextRecieved(MesgSpecs * mesg) {
    qDebug("Client received a message");
    printF(QString(mesg->sender) + ": (" + QTime::currentTime().toString()
           + ")\n" + QString(mesg->data) + "\n");
    delete mesg;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage() {
    QString message = ui->typeScreen->toPlainText();

    if(message != "") {
        tc_->txMessage(message);
        printF(settings->alias + ": (" + QTime::currentTime().toString()
               + ")\n" + message + "\n");
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
            qDebug("Client");
            setWindowTitle("Los Ostrich - Client");

            qDebug(settings->ipAddr.toLatin1().data());
            qDebug(QString::number(settings->port).toLatin1().data());
            qDebug(settings->alias.toLatin1().data());

            //TODO get a port from gui and ip just a hack here to make it compile
            char *ip = (char*)malloc(settings->ipAddr.size() * sizeof(char));
            char *alias = (char*)malloc(settings->alias.size() * sizeof(char));

            strcpy(ip, settings->ipAddr.toLatin1().data());
            strcpy(alias, settings->alias.toLatin1().data());

            tc_ = new TextClient(ip, alias, settings->port, BUFSIZE);
            textClient = new Thread();
            textClient->start();

            //Setting connections of signals
            connect(tc_,SIGNAL(signalTextRecieved(MesgSpecs *)),
                    this,SLOT(slotTextRecieved(MesgSpecs *)));
            connect(this, SIGNAL(startSignalClient()), tc_, SLOT(Start()));
            connect(tc_, SIGNAL(connectionError(const char*)), this,
                    SLOT(error(const char*)));
            connect(tc_, SIGNAL(success(const char*)), this,
                    SLOT(success(const char*)));

            tc_->moveToThread(textClient);
            emit startSignalClient();
        } else {
            qDebug("Server");
            setWindowTitle("Los Ostrich - Server");

            qDebug(QString::number(settings->port).toLatin1().data());

            TextServer * ts = new TextServer(settings->port, BUFSIZE);
            textServer = new Thread();
            textServer->start();

            //Setting connections of signals
            connect(ts,SIGNAL(signalClientConnected(ClientSpecs *)),
                    this,SLOT(slotClientConnected(ClientSpecs *)));
            connect(this, SIGNAL(startSignalServer()), ts, SLOT(Start()));
            connect(ts, SIGNAL(connectionError(const char*)), this,
                    SLOT(error(const char*)));
            connect(ts, SIGNAL(success(const char*)), this,
                    SLOT(success(const char*)));

            ts->moveToThread(textServer);
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

void MainWindow::error(const char *error) {
    QMessageBox::QMessageBox(QMessageBox::Critical, "Error", QString(error)
                                         , QMessageBox::Ok, this).exec();
}

void MainWindow::success(const char *message) {
    QString mesg(message);
    if(settings->isClient) {
        enableChat(true);
        mesg += " Server: " + settings->ipAddr;
    }
    QMessageBox::QMessageBox(QMessageBox::NoIcon, "Success", mesg,
                             QMessageBox::Ok, this).exec();
}
