#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gamewindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* root = engine.rootObjects()[0];
    GameWindow gameWindow(root, engine.rootContext());
    engine.rootContext()->setContextProperty("_gamewindow", &gameWindow);

    return app.exec();
}
