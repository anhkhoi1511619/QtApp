/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *connectionGroupBox;
    QGridLayout *gridLayout;
    QLabel *hostLabel;
    QLineEdit *hostLineEdit;
    QLabel *portLabel;
    QSpinBox *portSpinBox;
    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QLabel *connectionStatusLabel;
    QLabel *connectionStatusValueLabel;
    QGroupBox *payloadGroupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *payloadLineEdit;
    QCheckBox *hexModeCheckBox;
    QCheckBox *appendNewlineCheckBox;
    QCheckBox *autoSendCheckBox;
    QPushButton *sendButton;
    QGroupBox *receivedHexGroupBox;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *receivedHexTextEdit;
    QPushButton *clearReceivedHexButton;
    QGroupBox *logGroupBox;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *logTextEdit;
    QPushButton *clearLogButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 620);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        connectionGroupBox = new QGroupBox(centralwidget);
        connectionGroupBox->setObjectName("connectionGroupBox");
        gridLayout = new QGridLayout(connectionGroupBox);
        gridLayout->setObjectName("gridLayout");
        hostLabel = new QLabel(connectionGroupBox);
        hostLabel->setObjectName("hostLabel");

        gridLayout->addWidget(hostLabel, 0, 0, 1, 1);

        hostLineEdit = new QLineEdit(connectionGroupBox);
        hostLineEdit->setObjectName("hostLineEdit");

        gridLayout->addWidget(hostLineEdit, 0, 1, 1, 1);

        portLabel = new QLabel(connectionGroupBox);
        portLabel->setObjectName("portLabel");

        gridLayout->addWidget(portLabel, 0, 2, 1, 1);

        portSpinBox = new QSpinBox(connectionGroupBox);
        portSpinBox->setObjectName("portSpinBox");
        portSpinBox->setMaximum(65535);
        portSpinBox->setValue(5000);

        gridLayout->addWidget(portSpinBox, 0, 3, 1, 1);

        connectButton = new QPushButton(connectionGroupBox);
        connectButton->setObjectName("connectButton");

        gridLayout->addWidget(connectButton, 0, 4, 1, 1);

        disconnectButton = new QPushButton(connectionGroupBox);
        disconnectButton->setObjectName("disconnectButton");

        gridLayout->addWidget(disconnectButton, 0, 5, 1, 1);

        connectionStatusLabel = new QLabel(connectionGroupBox);
        connectionStatusLabel->setObjectName("connectionStatusLabel");

        gridLayout->addWidget(connectionStatusLabel, 1, 0, 1, 1);

        connectionStatusValueLabel = new QLabel(connectionGroupBox);
        connectionStatusValueLabel->setObjectName("connectionStatusValueLabel");

        gridLayout->addWidget(connectionStatusValueLabel, 1, 1, 1, 5);


        verticalLayout->addWidget(connectionGroupBox);

        payloadGroupBox = new QGroupBox(centralwidget);
        payloadGroupBox->setObjectName("payloadGroupBox");
        horizontalLayout = new QHBoxLayout(payloadGroupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        payloadLineEdit = new QLineEdit(payloadGroupBox);
        payloadLineEdit->setObjectName("payloadLineEdit");

        horizontalLayout->addWidget(payloadLineEdit);

        hexModeCheckBox = new QCheckBox(payloadGroupBox);
        hexModeCheckBox->setObjectName("hexModeCheckBox");
        hexModeCheckBox->setChecked(true);

        horizontalLayout->addWidget(hexModeCheckBox);

        appendNewlineCheckBox = new QCheckBox(payloadGroupBox);
        appendNewlineCheckBox->setObjectName("appendNewlineCheckBox");
        appendNewlineCheckBox->setChecked(false);

        horizontalLayout->addWidget(appendNewlineCheckBox);

        autoSendCheckBox = new QCheckBox(payloadGroupBox);
        autoSendCheckBox->setObjectName("autoSendCheckBox");
        autoSendCheckBox->setChecked(false);

        horizontalLayout->addWidget(autoSendCheckBox);

        sendButton = new QPushButton(payloadGroupBox);
        sendButton->setObjectName("sendButton");

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addWidget(payloadGroupBox);

        receivedHexGroupBox = new QGroupBox(centralwidget);
        receivedHexGroupBox->setObjectName("receivedHexGroupBox");
        verticalLayout_3 = new QVBoxLayout(receivedHexGroupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        receivedHexTextEdit = new QTextEdit(receivedHexGroupBox);
        receivedHexTextEdit->setObjectName("receivedHexTextEdit");
        receivedHexTextEdit->setReadOnly(true);

        verticalLayout_3->addWidget(receivedHexTextEdit);

        clearReceivedHexButton = new QPushButton(receivedHexGroupBox);
        clearReceivedHexButton->setObjectName("clearReceivedHexButton");

        verticalLayout_3->addWidget(clearReceivedHexButton);


        verticalLayout->addWidget(receivedHexGroupBox);

        logGroupBox = new QGroupBox(centralwidget);
        logGroupBox->setObjectName("logGroupBox");
        verticalLayout_2 = new QVBoxLayout(logGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        logTextEdit = new QTextEdit(logGroupBox);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setReadOnly(true);

        verticalLayout_2->addWidget(logTextEdit);

        clearLogButton = new QPushButton(logGroupBox);
        clearLogButton->setObjectName("clearLogButton");

        verticalLayout_2->addWidget(clearLogButton);


        verticalLayout->addWidget(logGroupBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "TCP Client Simulator (Qt)", nullptr));
        connectionGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        hostLabel->setText(QCoreApplication::translate("MainWindow", "Host", nullptr));
        hostLineEdit->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        portLabel->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        disconnectButton->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        connectionStatusLabel->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        connectionStatusValueLabel->setText(QCoreApplication::translate("MainWindow", "Disconnected", nullptr));
        payloadGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Payload", nullptr));
        payloadLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter payload (HEX or text)...", nullptr));
        hexModeCheckBox->setText(QCoreApplication::translate("MainWindow", "Hex mode", nullptr));
        appendNewlineCheckBox->setText(QCoreApplication::translate("MainWindow", "Append newline", nullptr));
        autoSendCheckBox->setText(QCoreApplication::translate("MainWindow", "Auto send (1s)", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        receivedHexGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Received HEX (from QTcpSocket)", nullptr));
        clearReceivedHexButton->setText(QCoreApplication::translate("MainWindow", "Clear received HEX", nullptr));
        logGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Session Log", nullptr));
        clearLogButton->setText(QCoreApplication::translate("MainWindow", "Clear log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
