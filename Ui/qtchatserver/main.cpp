#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl)
                     {
        if (!obj && url == objUrl) {
            qWarning() << "Failed to create QML object:" << objUrl;
            QCoreApplication::exit(-1);
        } }, Qt::QueuedConnection);

    TcpServer tcpServer;
    engine.rootContext()->setContextProperty("server", &tcpServer);

    engine.load(url);

    if (engine.rootObjects().isEmpty())
    {
        qWarning() << "Failed to load QML file:" << url;
        return -1;
    }

    return app.exec();
}