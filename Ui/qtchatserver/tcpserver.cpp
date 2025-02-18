#include "tcpserver.h"
#include <QAbstractSocket>

TcpServer::TcpServer(QObject *parent)
    : QObject(parent)
{
    connect(&_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    connect(this, &TcpServer::newMessage, this, &TcpServer::onNewMessage);

    if (_server.listen(QHostAddress::Any, 45000)) {
        qInfo() << "Listening on port 45000...";
    } else {
        qWarning() << "Failed to start server:" << _server.errorString();
    }
}

void TcpServer::onNewConnection()
{
    QTcpSocket *client = _server.nextPendingConnection();
    if (!client) {
        qWarning() << "Failed to accept new connection.";
        return;
    }

    QString clientKey = getClientKey(client);
    if (_clients.contains(clientKey)) {
        qWarning() << "Client already connected:" << clientKey;
        client->disconnectFromHost();
        return;
    }

    qInfo() << "New client connected:" << clientKey;
    _clients.insert(clientKey, client);

    connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
}

void TcpServer::onReadyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) {
        qWarning() << "Invalid client socket.";
        return;
    }

    QByteArray message = getClientKey(client).toUtf8() + ": " + client->readAll();
    emit newMessage(message);
}

void TcpServer::onDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) {
        qWarning() << "Invalid client socket.";
        return;
    }

    QString clientKey = getClientKey(client);
    qInfo() << "Client disconnected:" << clientKey;
    _clients.remove(clientKey);
    client->deleteLater();
}

void TcpServer::onNewMessage(const QByteArray &ba)
{
    for (const auto &client : qAsConst(_clients)) {
        client->write(ba);
        client->flush();
    }
}

void TcpServer::sendMessage(const QString &message)
{
    emit newMessage(message.toUtf8());
}
