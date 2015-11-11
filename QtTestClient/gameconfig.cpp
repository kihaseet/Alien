#include "gameconfig.h"

GameConfig::GameConfig()
{
    roles << "Captain";
    roles << "Doctor";
    roles << "Gunmen";
    roles << "Assistant";
    roles << "Engineer";
    roles << "Scientist";
    roles << "Signalmen";
}

QStringList &GameConfig::getRoles()
{
    return this->roles;
}

