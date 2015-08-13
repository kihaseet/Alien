#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <QStringList>

class GameConfig
{
    QStringList roles;
public:
    GameConfig();
    QStringList& getRoles();
};

#endif // GAMECONFIG_H
