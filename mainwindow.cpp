#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(new QTcpSocket(this))
    , autoSendTimer(new QTimer(this))

{
    ui->setupUi(this);

    autoSendTimer->setInterval(1000);

    connect(ui->connectButton, &QPushButton::clicked,
            this, &MainWindow::connectToServer);
    connect(ui->disconnectButton, &QPushButton::clicked,
            this, &MainWindow::disconnectFromServer);
    connect(ui->sendButton, &QPushButton::clicked,
            this, &MainWindow::sendMessage);
    connect(ui->clearLogButton, &QPushButton::clicked,
            ui->logTextEdit, &QTextEdit::clear);
    connect(ui->clearReceivedHexButton, &QPushButton::clicked,
            ui->receivedHexTextEdit, &QTextEdit::clear);
    connect(ui->payloadLineEdit, &QLineEdit::returnPressed,
            this, &MainWindow::sendMessage);

    connect(ui->hexModeCheckBox, &QCheckBox::toggled,
            ui->appendNewlineCheckBox, &QWidget::setDisabled);
    connect(ui->autoSendCheckBox, &QCheckBox::toggled,
            this, &MainWindow::onAutoSendToggled);

    connect(autoSendTimer, &QTimer::timeout,
            this, &MainWindow::sendMessage);

    connect(socket, &QTcpSocket::connected,
            this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::disconnected,
            this, &MainWindow::onDisconnected);
    connect(socket, &QTcpSocket::readyRead,
            this, &MainWindow::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred,
            this, &MainWindow::onSocketError);

    ui->appendNewlineCheckBox->setDisabled(ui->hexModeCheckBox->isChecked());
    updateConnectionUi(false);
    appendLog("TCP client simulator started. Ready to connect.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToServer()
{
    if (socket->state() != QAbstractSocket::UnconnectedState) {
        appendLog("Socket is already connected or connecting.");
        return;
    }

    const QString host = ui->hostLineEdit->text().trimmed();
    const quint16 port = static_cast<quint16>(ui->portSpinBox->value());

    appendLog(QString("Connecting to %1:%2 ...").arg(host).arg(port));
    socket->connectToHost(host, port);
}

void MainWindow::disconnectFromServer()
{
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        appendLog("Socket is not connected.");
        return;
    }

    appendLog("Disconnecting from server ...");
    socket->disconnectFromHost();
}

void MainWindow::sendMessage()
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        updateAutoSendState();
        if (sender() != autoSendTimer) {
            appendLog("Cannot send: client is not connected.");
        }
        return;
    }

    const QString payload = ui->payloadLineEdit->text();
    // if (payload.isEmpty()) {
    //     if (sender() != autoSendTimer) {
    //         appendLog("Cannot send empty payload.");
    //     }
    //     return;
    // }

    QByteArray data;
    QString errorMessage;
    if (!buildPayloadToSend(payload, data, errorMessage)) {
        appendLog(errorMessage);
        return;
    }

    const qint64 bytesWritten = socket->write(data);

    if (bytesWritten == -1) {
        appendLog(QString("Send failed: %1").arg(socket->errorString()));
        return;
    }

    appendLog(QString("Sent (%1 bytes): HEX=%2")
                  .arg(bytesWritten)
                  .arg(QString::fromLatin1(data.toHex().toUpper())));
}

void MainWindow::onAutoSendToggled(bool enabled)
{
    if (enabled) {
        appendLog("Auto-send enabled (1 second interval).");
    } else {
        appendLog("Auto-send disabled.");
    }

    updateAutoSendState();
}

void MainWindow::onConnected()
{
    updateConnectionUi(true);
    updateAutoSendState();
    appendLog(QString("Connected to %1:%2")
                  .arg(socket->peerAddress().toString())
                  .arg(socket->peerPort()));
}

void MainWindow::onDisconnected()
{
    updateConnectionUi(false);
    updateAutoSendState();
    appendLog("Disconnected from server.");
}

void MainWindow::onReadyRead()
{
    const QByteArray data = socket->readAll();
    const QString incomingUtf8 = QString::fromUtf8(data);
    const QString hex = QString::fromLatin1(data.toHex().toUpper());

    ui->receivedHexTextEdit->append(hex);

    appendLog(QString("Received (%1 bytes): HEX=%2")
                  .arg(data.size())
                  .arg(hex))
                  // .arg(incomingUtf8.trimmed()))
        ;
}

void MainWindow::onSocketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    appendLog(QString("Socket error: %1").arg(socket->errorString()));
    updateConnectionUi(socket->state() == QAbstractSocket::ConnectedState);
    updateAutoSendState();
}

bool MainWindow::buildPayloadToSend(const QString &input, QByteArray &output, QString &errorMessage) const
{
    if (ui->hexModeCheckBox->isChecked()) {
        char staffNo[] = {0x01, 0x02, 0x03}; // Staff number in hexadecimal
        char routeNo[] = {0x00, 0x10, 0x60, 0x20}; // Route number in BCD
        char currentTime[] = {0x11, 0x21, 0x01}; // Current number in BCD
        char stopStation[] = {0x00, 0x01}; // Stop Station in BCD
        char RSRP[] = {0x10, 0x0A}; // "Hello" in ASCII
        QByteArray combined;
        char command = 0x00; // Command byte
        char sequence = 0x0A; // Sequence length byte
        char dataSize = 2
                        + sizeof(staffNo)
                        + sizeof(routeNo)
                        + sizeof(currentTime)
                        + sizeof(stopStation)
                        + sizeof(RSRP);        // uint8_t dataSizeLo = ~dataSizeHi + 1; // Simple checksum (one's complement)
        uint8_t dataSum = 0x00; // Checksum byte

        output.append(0x02); // Start byte
        output.append((char)0x00);
        output.append((char)dataSize); // Placeholder for checksum (simple one's complement)
        output.append((char)(~dataSize + 1)); // Data size byte


        combined.append(command);
        combined.append(sequence);
        combined.append(staffNo, sizeof(staffNo));
        combined.append(routeNo, sizeof(routeNo));
        combined.append(currentTime, sizeof(currentTime));
        combined.append(stopStation, sizeof(stopStation));
        combined.append(RSRP, sizeof(RSRP));

        for (uint8_t byte : combined) {
            output.append(byte);
            dataSum += byte; // Calculate checksum
        }

        output.append(~dataSum + 1); // Append checksum byte
        output.append(0x03); // End byte
        return true;
    }

    output = input.toUtf8();
    if (ui->appendNewlineCheckBox->isChecked()) {
        output.append('\n');
    }
    return true;
}

void MainWindow::appendLog(const QString &message)
{
    const QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->logTextEdit->append(QString("[%1] %2").arg(timestamp, message));
}

void MainWindow::updateConnectionUi(bool connected)
{
    ui->connectButton->setEnabled(!connected);
    ui->disconnectButton->setEnabled(connected);
    ui->sendButton->setEnabled(connected);
    ui->hostLineEdit->setEnabled(!connected);
    ui->portSpinBox->setEnabled(!connected);
    ui->connectionStatusValueLabel->setText(connected ? "Connected" : "Disconnected");
}

void MainWindow::updateAutoSendState()
{
    const bool shouldRun = ui->autoSendCheckBox->isChecked()
    && socket->state() == QAbstractSocket::ConnectedState;

    if (shouldRun && !autoSendTimer->isActive()) {
        autoSendTimer->start();
    } else if (!shouldRun && autoSendTimer->isActive()) {
        autoSendTimer->stop();
    }
}
