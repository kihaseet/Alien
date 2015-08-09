#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QStringList>
#include <QVector>

#include "itarget.h"
#include "status.h"
#include "playerimage.h"
#include "item.h"

class Player : public ITarget
{
protected:
    Status status;
    QStringList roles;
    QVector<Item> items;
    PlayerImage image;
    bool online;
    bool onDuty;
public:
    explicit Player();
    explicit Player(QString name, QStringList roles, PlayerImage image, bool onDuty = false, bool online = true, Status status = Status::UP);

    Status getStatus();
    void setStatus(Status status);
    void setOnline(bool online);
    void setOnDuty(bool onDuty);
    QStringList getRoles();
    void setRoles(QStringList roles);
    void setImage(PlayerImage img);
    bool isOnline();
    bool isOnDuty();
    void addItem(Item item);
    Item* getItem(ItemType itemType);
    QVector<Item> getItems();
    void setItems(QVector<Item> items);

    bool operator<(const Player& p) const;
};

#endif // PLAYER_H
