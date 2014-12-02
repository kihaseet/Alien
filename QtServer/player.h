#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
class item;
class player
{
public:
    QString name;
    player(QString n);
    int success_attack;
    int HP,status;
    int invasion; //замена фетуса. -1  отсутствует, 2 выставляется сразу после внедрения, каждое утро уменьшается на 1,
    bool healthy,waiting;//при нуле человек становится чужим
    int invasionday;/*номер дня осознания,0 для генератора случайных заражений*/
    QString whoinvas;/*имя последнего заразившего игрока*/
    int use_night_item; //0 если не было использований вещей ночью
    int attack_thisnight;//0 если чужой никого не атаковал этой ночью
    QList <QString> rolelist;
    QList <QPair<QString,QList<QString> > > actionlist;
    QMap <QString,item*> itemlist; //дескриптор-указатель
};

#endif // PLAYER_H
