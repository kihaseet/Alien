#ifndef ITEM_H
#define ITEM_H

#include <QtCore>
#include "player.h"

class player;

class item:public QObject
{
Q_OBJECT
public:
    QQueue <QString> rotation;
    QString name;
    QString handle;
    QString note; //описание
    QString forrepower;//предмет для батарейки
    QString role;//чей предмет
    int lastscan;//статус последней просканированной цели
    int power; /*!=0 незаряжен, -1 сломан*/
    void counter();
    void reforge(int i);
    item();

public slots:
    virtual void use_item_day(QString whom){}
    virtual void use_item_night(QString whom){}
    virtual void ult_item(QString whom){}
signals:
    void item_heal_all();
    void item_scan_all();
    void item_voting_all();
};

class Badge:public item
{
public:
    Badge();
    void use_item_day();
    void use_item_night();
    void ult_item();
};

class Rotation:public item
{
public:
    Rotation();
    void use_item_day();
    void use_item_night();
    void ult_item();
};

class Blaster:public item
{
public:
    Blaster();
    void use_item_day();
    void use_item_night(player *whom);
    void ult_item(player *whom);
};

class Injector:public item
{
public:
    Injector();
    void use_item_day(player *whom);
    void use_item_night(player *whom);
    void ult_item();
};

class Notebook:public item
{
public:
    Notebook();
    void use_item_day(player *whom);
    void use_item_night();
    void ult_item();
};

class Battery:public item
{
public:
    Battery();
    void use_item_day(item* whom);
    void use_item_night();
    void ult_item(item* whom);
};

class Scanner:public item
{
public:
    Scanner();
    void use_item_day(player* whom);
    void use_item_night(player* whom);
    void ult_item();
};

class Mop:public item
{
public:
    Mop();
    void use_item_day();
    void use_item_night(player* whom);
    void ult_item();
};
#endif // ITEM_H
