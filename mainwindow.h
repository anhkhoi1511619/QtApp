#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectToServer();
    void disconnectFromServer();
    void sendMessage();
    void onAutoSendToggled(bool enabled);

    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onSocketError(QAbstractSocket::SocketError socketError);

private:
    bool buildPayloadToSend(const QString &input, QByteArray &output, QString &errorMessage) const;
    void appendLog(const QString &message);
    void updateConnectionUi(bool connected);
    void updateAutoSendState();
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QTimer *autoSendTimer;
};
#endif // MAINWINDOW_H
