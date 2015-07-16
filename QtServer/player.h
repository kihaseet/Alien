#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

class item;



class player
{
public:
    QString name;
    int SocketId; //привязка к сетевому сокету
    int avatar;//пятизначное число, цифра - вариант. голова-прическа-одежда-волосы-кожа
    player(QString n, int id);
    bool ImDuty;//true - дежурил в текужем графике ротации
    int success_attack;
    int HP,status;
    int invasion; //замена фетуса. -1  отсутствует, 2 выставляется сразу после внедрения, каждое утро уменьшается на 1,
    bool healthy,waiting;//при нуле человек становится чужим. у чужого при 0 есть возможность заражать.
    int invasionday;/*номер дня осознания,0 для генератора случайных заражений*/
    player* whoinvas;/*имя последнего заразившего игрока*/
    bool use_night_item; //false если не было использований вещей ночью
    bool attack_thisnight;//false если чужой никого не атаковал этой ночью
    bool simplebath;//true если не покидал биованну этой ночью
    bool infecting;//true если уже заражал этой ночью
    QList <QString> rolelist;
    QList <TurnObject> actionlist;
    QMap <QString,item*> itemlist; //дескриптор-указатель
};


#endif // PLAYER_H
