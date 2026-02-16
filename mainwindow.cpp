#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    connect(ui->connectButton, &QPushButton::clicked,
            this, &MainWindow::connectToServer);
    connect(ui->disconnectButton, &QPushButton::clicked,
            this, &MainWindow::disconnectFromServer);
    connect(ui->sendButton, &QPushButton::clicked,
            this, &MainWindow::sendMessage);
    connect(ui->clearLogButton, &QPushButton::clicked,
            ui->logTextEdit, &QTextEdit::clear);
    connect(ui->payloadLineEdit, &QLineEdit::returnPressed,
            this, &MainWindow::sendMessage);

    connect(socket, &QTcpSocket::connected,
            this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::disconnected,
            this, &MainWindow::onDisconnected);
    connect(socket, &QTcpSocket::readyRead,
            this, &MainWindow::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred,
            this, &MainWindow::onSocketError);

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
        appendLog("Cannot send: client is not connected.");
        return;
    }

    QString payload = ui->payloadLineEdit->text();
    if (payload.isEmpty()) {
        appendLog("Cannot send empty payload.");
        return;
    }

    if (ui->appendNewlineCheckBox->isChecked()) {
        payload.append('\n');
    }

    const QByteArray data = payload.toUtf8();
    const qint64 bytesWritten = socket->write(data);

    if (bytesWritten == -1) {
        appendLog(QString("Send failed: %1").arg(socket->errorString()));
        return;
    }

    appendLog(QString("Sent (%1 bytes): %2")
                  .arg(bytesWritten)
                  .arg(payload.trimmed()));
    ui->payloadLineEdit->clear();
}

void MainWindow::onConnected()
{
    updateConnectionUi(true);
    appendLog(QString("Connected to %1:%2")
                  .arg(socket->peerAddress().toString())
                  .arg(socket->peerPort()));
}

void MainWindow::onDisconnected()
{
    updateConnectionUi(false);
    appendLog("Disconnected from server.");
}

void MainWindow::onReadyRead()
{
    const QByteArray data = socket->readAll();
    const QString incoming = QString::fromUtf8(data);
    appendLog(QString("Received (%1 bytes): %2")
                  .arg(data.size())
                  .arg(incoming.trimmed()));
}

void MainWindow::onSocketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    appendLog(QString("Socket error: %1").arg(socket->errorString()));
    updateConnectionUi(socket->state() == QAbstractSocket::ConnectedState);
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
