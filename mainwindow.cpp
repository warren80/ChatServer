#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //move these to be started when button pressed in gui
    TextServer * ts = new TextServer();
    textServer = new QThread(this);
    textServer->start();
    connect(ts,SIGNAL(signalClientConnected(ClientConnect*)),
            this,SLOT(slotClientConnected(ClientConnect*)));
    ts->moveToThread(textServer);

    //move these to be started when button pressed in gui
    TextClient * tc = new TextClient();
    textClient = new QThread(this);
    textClient->start();
    connect(tc,SIGNAL(signalTextRecieved(TextReceived*)),
            this,SLOT(slotTextRecieved(TextReceived*)));
    tc->moveToThread(textClient);

    ui->setupUi(this);
}

void MainWindow::slotClientConnected(ClientConnect*) {

}

void MainWindow::slotTextRecieved(TextReceived*) {

}

MainWindow::~MainWindow()
{
    delete ui;
}
