#ifndef ITEM_H
#define ITEM_H

#include <QtCore>
#include "player.h"
#include "game.h"

class player;
class game;

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
    QPair<QString,int> lastscan;//статус последней просканированной цели
    int power; /*!=0 незаряжен, -1 сломан*/
    void counter();
    void reforge(int i);
    item();//добавить playerlist
    game* _game;

public slots:
    virtual void use_item_day(QQueue<QString> whom){}
    virtual void use_item_night(QQueue<QString> whom){}
    virtual void ult_item(QQueue<QString> whom){}
signals:
    void item_heal_all();
    void item_scan_all();
    void item_voting_all();
};

class Badge:public item
{
public:
    Badge(game* _g);
    void use_item_day();
    void use_item_night();
    void ult_item();
};

class Rotation:public item
{
public:
    Rotation(game* _g);
    void use_item_day(QQueue<QString> whom);
    void use_item_night();
    void ult_item();
};

class Blaster:public item
{
public:
    Blaster(game *_g);
    void use_item_day();
    void use_item_night(QQueue<QString> whom);
    void ult_item(QQueue<QString> whom);
};

class Injector:public item
{
public:
    Injector(game *_g);
    void use_item_day(QQueue<QString> whom);
    void use_item_night(QQueue<QString> whom);
    void ult_item(QQueue<QString> whom);
};

class Notebook:public item
{
public:
    Notebook(game *_g);
    void use_item_day(QQueue<QString> whom);
    void use_item_night(QQueue<QString> whom);
    void ult_item(QQueue<QString> whom);
};

class Battery:public item
{
public:
    Battery(game *_g);
    void use_item_day(QQueue<QString> whom);
    void use_item_night(QQueue<QString> whom);
    void ult_item(QQueue<QString> whom);
};

class Scanner:public item
{
public:
    Scanner(game *_g);
    void use_item_day(QQueue<QString> whom);
    void use_item_night(QQueue<QString> whom);
    void ult_item(QQueue<QString> whom);
};

class Mop:public item
{
public:
    Mop(game *_g);
    void use_item_day();
    void use_item_night(QQueue<QString> whom);
    void ult_item();
};
#endif // ITEM_H
