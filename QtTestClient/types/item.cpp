#include "item.h"

Item::Item()
{
    this->type = ItemType::IT_UNKNOW;
}

Item::Item(ItemType type, int charge)
{
    this->type = type;
    this->charge = charge;
    this->isActive = true;
    this->batteryBlessing = false;

    switch(type)
    {
    case ItemType::IT_BADGE:
        this->name = "Badge";
        break;
    case ItemType::IT_BATTERY:
        this->name = "Battery";
        break;
    case ItemType::IT_BLASTER:
        this->name = "Blaster";
        break;
    case ItemType::IT_FETUS:
        this->name = "Fetus";
        break;
    case ItemType::IT_INJECTOR:
        this->name = "Injector";
        break;
    case ItemType::IT_MOP:
        this->name = "Mop";
        break;
    case ItemType::IT_NOTEBOOK:
        this->name = "Notebook";
        break;
    case ItemType::IT_ROTATION:
        this->name = "Rotation";
        break;
    case ItemType::IT_SCANNER:
        this->name = "Scanner";
        break;
    case ItemType::IT_UNKNOW:
        this->name = "Unknown";
        break;
    }
}

int Item::getChargeLevel()
{
    return this->charge;
}

ItemType Item::getType() const
{
    return this->type;
}

void Item::setChargeLevel(int charge)
{
    this->charge = charge;
}

void Item::setBatteryBlessing(bool blessing)
{
    this->batteryBlessing = blessing;
}

bool Item::getBatteryBlessing()
{
    return this->batteryBlessing;
}

bool Item::canUse()
{
    return this->batteryBlessing || (this->isActive && this->charge == 0);
}

bool Item::canUlt()
{
    return (this->batteryBlessing || this->charge == 0) && this->type != ItemType::IT_ROTATION && this->type != ItemType::IT_MOP;
}

void Item::setActive(bool isActive)
{
    this->isActive = isActive;
}

bool Item::operator==(const Item &item) const
{
    return item.getType() == this->getType();
}

