#include "types/itarget.h"

ITarget::ITarget()
{
    this->name = "";
}

ITarget::ITarget(QString name)
{
    this->name = name;
}

QString ITarget::getName() const
{
    return this->name;
}

void ITarget::setName(QString name)
{
    this->name = name;
}
