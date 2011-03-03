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
    QValidator *valid = new QRegExpValidator(QRegExp("^[0-9]*$"), this);

    serviceGroup.addButton(ui->clientButton);
    serviceGroup.addButton(ui->serverButton);

    connect(ui->okCancel, SIGNAL(accepted()), this, SLOT(storeSettings()));
    connect(ui->okCancel, SIGNAL(rejected()), this, SLOT(cancelSettings()));
    connect(ui->clientButton, SIGNAL(toggled(bool)), this, SLOT(enableDisableClient(bool)));

    ui->portText->setValidator(valid);
}

Settings::~Settings() {
    delete ui;
}

void Settings::storeSettings() {
    settings = (PSETTINGS)malloc(sizeof(SETTINGS));
    settings->accepted = true;

    settings->port = ui->portText->text().toInt();

    if((settings->isClient = ui->clientButton->isChecked())) {
        settings->ipAddr = ui->ipText->text();
    }
}

void Settings::cancelSettings() {
    settings = (PSETTINGS)malloc(sizeof(SETTINGS));
    settings->accepted = false;
}

PSETTINGS Settings::getSettings() {
    return settings;
}

void Settings::enableDisableClient(bool client) {
    ui->clientBox->setEnabled(client);
}
