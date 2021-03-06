#ifndef ITEM_H
#define ITEM_H

#include <QtCore>
#include "player.h"
#include "game.h"
#include "types.h"

class player;
class game;

class item:public QObject
{
Q_OBJECT
protected:
    ITEM ID;
    QString handle;
   //статус последней просканированной цели
    int power; /*!=0 незаряжен, -1 сломан -2 для капитанского значка*/
public:
    QQueue <QString> rotation;
    QPair<QString,int> lastscan;

    QString note; //описание

    void counter();
    void reforge(int i);
    item();//добавить playerlist
    game* _game;

    ITEM getID();
    QString getHandle();
    QPair<QString,int> getLastScan();
    int getPower();
    void setPower(int charge);

public slots:
    virtual void use_item_day(QQueue<QString> whom){}
    virtual void use_item_night(QQueue<QString> whom){}
    virtual void ult_item(QQueue<QString> whom){}
};

class Badge:public item
{
public:
    Badge(game* _g);
    void use_item_day(QQueue<QString> whom);
};

class Rotation:public item
{
public:
    Rotation(game* _g);
    void use_item_day(QQueue<QString> whom);
};

class Blaster:public item
{
public:
    Blaster(game *_g);
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
    void use_item_night(QQueue<QString> whom);
};
#endif // ITEM_H
