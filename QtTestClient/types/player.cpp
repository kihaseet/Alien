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

QStringList Player::getRoles()
{
    return this->roles;
}

void Player::setRoles(QStringList roles)
{
    this->roles = roles;
}

bool Player::isOnline()
{
    return this->online;
}

bool Player::isOnDuty()
{
    return this->onDuty;
}
