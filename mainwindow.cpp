#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    TextServer * ts = new TextServer();
    TextClient * tc = new TextClient(); //move these to be started when button pressed in gui
    textServer = new QThread(this);
    textClient = new QThread(this);
    connect(ts,SIGNAL(signalClientConnected(ClientConnect*)),
            this,SLOT(slotClientConnected(ClientConnect*)));
    connect(tc,SIGNAL(signalTextRecieved(TextReceived*)),
            this,SLOT(slotTextRecieved(TextReceived*)));

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
