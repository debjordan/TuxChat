#include "tcpclient.h"
#include <QAbstractSocket>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
{
    connect(&_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    connect(&_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer(const QString &ip, const QString &port)
{
    bool isValidPort;
    quint16 portNumber = port.toUInt(&isValidPort);

    if (!isValidPort || portNumber < 1024 || portNumber > 65535) {
        qWarning() << "Invalid port number";
        return;
    }

    _socket.connectToHost(ip, portNumber);
}

void TcpClient::disconnectFromServer()
{
    _socket.disconnectFromHost();
}

bool TcpClient::isConnected() const
{
    return _socket.state() == QAbstractSocket::ConnectedState;
}

void TcpClient::sendMessage(const QString &message)
{
    if (message.trimmed().isEmpty()) {
        qWarning() << "Empty message";
        return;
    }

    _socket.write(message.toUtf8() + "\n");
    _socket.flush();
}

void TcpClient::onConnected()
{
    qInfo() << "Connected to host";
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Socket error:" << error;
}

void TcpClient::onReadyRead()
{
    QByteArray buffer = _socket.readAll();
    while (!buffer.isEmpty()) {
        int endOfLine = buffer.indexOf('\n');
        if (endOfLine == -1) {
            break;
        }

        QByteArray message = buffer.left(endOfLine);
        buffer = buffer.mid(endOfLine + 1);
        emit newMessage(message);
    }
}
