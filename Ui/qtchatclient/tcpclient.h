#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);

    Q_INVOKABLE void connectToServer(const QString &ip, const QString &port);
    Q_INVOKABLE void disconnectFromServer();
    Q_INVOKABLE bool isConnected() const;

signals:
    void newMessage(const QByteArray &ba);

public slots:
    void sendMessage(const QString &message);

private slots:
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);
    void onReadyRead();

private:
    QTcpSocket _socket;
};

#endif // TCPCLIENT_H
