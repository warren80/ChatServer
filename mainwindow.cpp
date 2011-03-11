#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    enableChat(false);

    connected_ = false;
}

void MainWindow::slotTextRecieved(MessageStruct * mesg) {
    qDebug("Client received a message");
    printF(QString(mesg->alias) + ": (" + QTime::currentTime().toString()
           + ")\n" + QString(mesg->data) + "\n");
    delete mesg;
}

void MainWindow::slotServerClosed() {
    if(connected_) {

        connected_ = false;
        emit signalDisconnect();
        printF("Client Disconnected.");

        if(settings->logChat) {
            saveChat();
        }
    }
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
        connected_ = true;
        printF(QString("Error Log will be saved to: errorLog"));
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
            connect(tc_,SIGNAL(signalTextRecieved(MessageStruct *)),
                    this,SLOT(slotTextRecieved(MessageStruct *)));
            connect(this, SIGNAL(startSignalClient()), tc_, SLOT(Start()));
            connect(tc_, SIGNAL(connectionError(const char*)), this,
                    SLOT(error(const char*)));
            connect(tc_, SIGNAL(success(const char*)), this,
                    SLOT(success(const char*)));
            connect(tc_, SIGNAL(signalServerClosed()), this, SLOT(slotServerClosed()));
            connect(this, SIGNAL(signalDisconnect()), tc_, SLOT(Stop()));

            tc_->moveToThread(textClient);
            emit startSignalClient();
        } else {
            qDebug("Server");
            setWindowTitle("Los Ostrich - Server");
            printF(QString("Server Log will be saved to: log"));

            qDebug(QString::number(settings->port).toLatin1().data());

            TextServer * ts = new TextServer(settings->port, BUFSIZE);
            textServer = new Thread();
            textServer->start();

            //Setting connections of signals
            connect(this, SIGNAL(startSignalServer()), ts, SLOT(Start()));
            connect(ts, SIGNAL(connectionError(const char*)), this,
                    SLOT(error(const char*)));
            connect(ts, SIGNAL(success(const char*)), this,
                    SLOT(success(const char*)));
            connect(this, SIGNAL(signalDisconnect()), ts, SLOT(Stop()));

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

void MainWindow::on_actionDisconnect_triggered() {
    if(connected_) {
        connected_ = false;
        if(settings->logChat) {
            saveChat();
        }
        qDebug("Disconnecting");
        emit signalDisconnect();
    }
}

void MainWindow::saveChat() {
    qDebug("Saving chat");
    QFile *chatLog = new QFile(QString("chatLog(") + QDateTime::currentDateTime().toString().toLatin1() + QString(")"));

    chatLog->open(QIODevice::Append);
    chatLog->write(QString("Chat Log ~ " + QDateTime::currentDateTime().toString()
                           + "\n").toLatin1().data());
    chatLog->write(ui->chatScreen->toPlainText().toLatin1().data());
    chatLog->close();

    printF(QString("Chat log saved to: ") + chatLog->fileName());

    delete chatLog;
}
