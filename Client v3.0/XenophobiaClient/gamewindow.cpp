#include "gamewindow.h"
#include <QVariant>
#include <QDebug>

void GameWindow::LobbyInputAccepted()
{
    QString server_ip = viewer->findChild<QObject*>("server_ip_text")->property("text").toString();
    qInfo() << server_ip;

    viewer->findChild<QObject*>("lobby_form")->setProperty("state", "register_state");
}
