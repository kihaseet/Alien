#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

class player
{
public:
    QString name;
    player(QString n);
    int HP,status;
    int use_night_item; //0 если не было использований вещей ночью
    QList <QString> rolelist;
    QList <QString> actionlist;
    QMap <QString,item> itemlist;
};

#endif // PLAYER_H
