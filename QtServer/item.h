#ifndef ITEM_H
#define ITEM_H

#include <QtCore>

class item:public QObject
{
Q_OBJECT
public:
    QQueue <QString> rotation;
    QString name;
    QString handle;
    QString note; //описание
    QString forrepower;//предмет для батарейки
    int power; /*!=0 незаряжен, -1 сломан*/
    void counter();
    void reforge(int i);
    item();

public slots:
    virtual void use_item()=0;
    virtual void ult_item()=0;

};

class Badge:public item
{
public:
    Badge();
    void use_item();
    void ult_item();
};

class Rotation:public item
{
public:
    Rotation();
    void use_item();
    void ult_item();
};

class Blaster:public item
{
public:
    Blaster();
    void use_item();
    void ult_item();
};

class Injector:public item
{
public:
    Injector();
    void use_item();
    void ult_item();
};

class Notebook:public item
{
public:
    Notebook();
    void use_item();
    void ult_item();
};

class Battery:public item
{
public:
    Battery();
    void use_item();
    void ult_item();
};

class Scanner:public item
{
public:
    Scanner();
    void use_item();
    void ult_item();
};

class Mop:public item
{
public:
    Mop();
    void use_item();
    void ult_item();
};
#endif // ITEM_H
