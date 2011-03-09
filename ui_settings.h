/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QDialogButtonBox *okCancel;
    QLineEdit *portText;
    QLabel *portLabel;
    QGroupBox *serviceBox;
    QRadioButton *clientButton;
    QRadioButton *serverButton;
    QGroupBox *clientBox;
    QLabel *ipLabel;
    QLineEdit *ipText;
    QLabel *aliasLabel;
    QLineEdit *aliasText;
    QWidget *widget;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(500, 221);
        Settings->setStyleSheet(QString::fromUtf8(""));
        okCancel = new QDialogButtonBox(Settings);
        okCancel->setObjectName(QString::fromUtf8("okCancel"));
        okCancel->setGeometry(QRect(50, 180, 181, 32));
        okCancel->setOrientation(Qt::Horizontal);
        okCancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        portText = new QLineEdit(Settings);
        portText->setObjectName(QString::fromUtf8("portText"));
        portText->setGeometry(QRect(60, 10, 171, 31));
        portText->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 8px;\n"
"padding-left: 2px;\n"
"padding-right: 2px;"));
        portText->setInputMethodHints(Qt::ImhNone);
        portText->setFrame(true);
        portLabel = new QLabel(Settings);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setGeometry(QRect(10, 20, 41, 17));
        serviceBox = new QGroupBox(Settings);
        serviceBox->setObjectName(QString::fromUtf8("serviceBox"));
        serviceBox->setGeometry(QRect(20, 130, 201, 51));
        clientButton = new QRadioButton(serviceBox);
        clientButton->setObjectName(QString::fromUtf8("clientButton"));
        clientButton->setGeometry(QRect(10, 20, 117, 22));
        QFont font;
        font.setStrikeOut(false);
        clientButton->setFont(font);
        clientButton->setChecked(true);
        serverButton = new QRadioButton(serviceBox);
        serverButton->setObjectName(QString::fromUtf8("serverButton"));
        serverButton->setGeometry(QRect(110, 20, 117, 22));
        clientBox = new QGroupBox(Settings);
        clientBox->setObjectName(QString::fromUtf8("clientBox"));
        clientBox->setGeometry(QRect(20, 50, 201, 71));
        ipLabel = new QLabel(clientBox);
        ipLabel->setObjectName(QString::fromUtf8("ipLabel"));
        ipLabel->setGeometry(QRect(10, 20, 21, 17));
        ipText = new QLineEdit(clientBox);
        ipText->setObjectName(QString::fromUtf8("ipText"));
        ipText->setGeometry(QRect(40, 20, 161, 21));
        ipText->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 8px;\n"
"padding-left: 2px;\n"
"padding-right: 2px;"));
        aliasLabel = new QLabel(clientBox);
        aliasLabel->setObjectName(QString::fromUtf8("aliasLabel"));
        aliasLabel->setGeometry(QRect(10, 50, 41, 17));
        aliasText = new QLineEdit(clientBox);
        aliasText->setObjectName(QString::fromUtf8("aliasText"));
        aliasText->setGeometry(QRect(50, 46, 151, 21));
        aliasText->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 8px;\n"
"padding-left: 2px;\n"
"padding-right: 2px;"));
        widget = new QWidget(Settings);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(240, 0, 261, 221));
        widget->setStyleSheet(QString::fromUtf8("background: url(./ostrichSettingsBG.png);"));
        QWidget::setTabOrder(portText, ipText);
        QWidget::setTabOrder(ipText, clientButton);
        QWidget::setTabOrder(clientButton, serverButton);
        QWidget::setTabOrder(serverButton, okCancel);

        retranslateUi(Settings);
        QObject::connect(okCancel, SIGNAL(accepted()), Settings, SLOT(accept()));
        QObject::connect(okCancel, SIGNAL(rejected()), Settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Settings", 0, QApplication::UnicodeUTF8));
        portText->setText(QApplication::translate("Settings", "8001", 0, QApplication::UnicodeUTF8));
        portLabel->setText(QApplication::translate("Settings", "Port:", 0, QApplication::UnicodeUTF8));
        serviceBox->setTitle(QApplication::translate("Settings", "Service", 0, QApplication::UnicodeUTF8));
        clientButton->setText(QApplication::translate("Settings", "Client", 0, QApplication::UnicodeUTF8));
        serverButton->setText(QApplication::translate("Settings", "Server", 0, QApplication::UnicodeUTF8));
        clientBox->setTitle(QApplication::translate("Settings", "Client Settings", 0, QApplication::UnicodeUTF8));
        ipLabel->setText(QApplication::translate("Settings", "IP:", 0, QApplication::UnicodeUTF8));
        aliasLabel->setText(QApplication::translate("Settings", "Alias:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
