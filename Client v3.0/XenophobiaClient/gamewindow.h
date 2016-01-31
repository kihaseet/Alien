#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QQmlContext>
#include "models/rolesmodel.h"
#include "proto/types.pb.h"

class GameWindow : public QObject
{
    Q_OBJECT
public:
    GameWindow(QObject* QMLObject, QQmlContext* QMLContext)
        : viewer(QMLObject)
        , ctx(QMLContext)
    {
        ctx->setContextProperty("available_roles_model", &availableRoles);
        availableRoles.addRole(::types::CAPTAIN);
    }

public slots:
    void LobbyInputAccepted();

protected:
    QObject* viewer;
    QQmlContext* ctx;
    RolesModel availableRoles;
};

#endif // GAMEWINDOW_H
