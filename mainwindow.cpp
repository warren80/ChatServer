#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //move these to be started when button pressed in gui
    TextServer * ts = new TextServer(7000);
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

    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
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
        printF("Local:\n    " + message + "\n");
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

    if(settings->accepted) {
        //TODO: Connect to server/Listen for clients
    }
}

void MainWindow::closeEvent(QCloseEvent *) {
    textServer->quit();
    textClient->quit();
}
