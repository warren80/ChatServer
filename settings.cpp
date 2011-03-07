#include "settings.h"
#include "ui_settings.h"
#include <QValidator>
#include <QRegExp>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    QButtonGroup serviceGroup(ui->serviceBox);
    QValidator *validPort = new QRegExpValidator(QRegExp("^\\d*$"), this);
    QValidator *validIp = new QRegExpValidator(QRegExp("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$"), this);

    serviceGroup.addButton(ui->clientButton);
    serviceGroup.addButton(ui->serverButton);

    connect(ui->okCancel, SIGNAL(accepted()), this, SLOT(storeSettings()));
    connect(ui->clientButton, SIGNAL(toggled(bool)), this, SLOT(enableDisableClient(bool)));

    ui->portText->setValidator(validPort);
    ui->ipText->setValidator(validIp);
}

Settings::~Settings() {
    delete ui;
}

void Settings::storeSettings() {
    settings = new SETTINGS();

    settings->port = ui->portText->text().toInt();

    if((settings->isClient = ui->clientButton->isChecked())) {
        settings->ipAddr = ui->ipText->text();
    }
}

PSETTINGS Settings::getSettings() {
    return settings;
}

void Settings::enableDisableClient(bool client) {
    ui->clientBox->setEnabled(client);
}
