#include "types/player.h"

Player::Player() : ITarget("")
{
    this->roles = QStringList();
    this->image = PlayerImage::PASSENGER;
    this->status = Status::UP;
    this->onDuty = false;
    this->online = true;
}

Player::Player(QString name, QStringList roles, PlayerImage image, bool onDuty, bool online, Status status) : ITarget(name)
{
    this->roles = roles;
    this->image = image;
    this->status = status;
    this->onDuty = onDuty;
    this->online = online;

    for (QString& role: roles)
    {
        if (role == "Captain")
        {
            this->items.push_back(Item(IT_BADGE, 0));
        }
        else  if (role == "Doctor")
        {
            this->items.push_back(Item(IT_INJECTOR, 0));
        }
        else  if (role == "Gunmen")
        {
            this->items.push_back(Item(IT_BLASTER, 0));
        }
        else if (role == "Assistant")
        {
            this->items.push_back(Item(IT_ROTATION, 0));
        }
        else  if (role == "Engineer")
        {
            this->items.push_back(Item(IT_BATTERY, 0));
        }
        else  if (role == "Scientist")
        {
            this->items.push_back(Item(IT_SCANNER, 0));
        }
        else  if (role == "Signalmen")
        {
            this->items.push_back(Item(IT_NOTEBOOK, 0));
        }

    }
}

void Player::update(const Player &p)
{
    this->image = p.image;
    this->items = p.items;
    this->name = p.name;
    this->onDuty = p.onDuty;
    this->online = p.online;
    this->roles = p.roles;
    this->status = p.status;
}

Status Player::getStatus()
{
    return this->status;
}

void Player::setStatus(Status status)
{
    this->status = status;
}

void Player::setOnline(bool online)
{
    this->online = online;
}

void Player::setOnDuty(bool onDuty)
{
    this->onDuty = onDuty;
}

QStringList Player::getRoles() const
{
    return this->roles;
}

void Player::setRoles(QStringList roles)
{
    this->roles = roles;
}

void Player::setImage(PlayerImage img)
{
    this->image = img;
}

bool Player::isOnline() const
{
    return this->online;
}

bool Player::isOnDuty()
{
    return this->onDuty;
}

void Player::addItem(Item item)
{
    this->items.push_back(item);
}

Item *Player::getItem(ItemType itemType)
{
    for (int i = 0; i < this->items.length(); i++)
    {
        if (this->items[i].getType() == itemType)
        {
            return &this->items[i];
        }
    }

    return nullptr;
}

QVector<Item> Player::getItems()
{
    return this->items;
}

void Player::setItems(QVector<Item> items)
{
    this->items = items;
}

bool Player::operator<(const Player &p) const
{
    return this->getName().length() < p.getName().length();
}
