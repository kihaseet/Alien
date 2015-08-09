#include "types/currentplayer.h"
#include "factories/actionfactory.h"

CurrentPlayer::CurrentPlayer(QString name, Status status, QStringList roles, PlayerImage image, int hp, bool isAlien)
{
    this->name = name;
    this->status = status;
    this->roles = roles;
    this->image = image;
    this->hp = hp;
    this->_isAlien = isAlien;
    this->yetVote = false;
}

//void CurrentPlayer::recalcActions()
//{
//    this->actions.clear();

//    if (gameClient->isNight())
//    {
//        if (!this->yetWait)
//        {
//            this->actions.push_back(ActionFactory::sleep());

//            if (this->_isAlien)
//            {
//                if (!this->getYetAttack())
//                {
//                    for (auto& target: gameClient->getPlayers())
//                    {
//                        if (target.getName() != this->getName())
//                        {
//                            this->actions.push_back(ActionFactory::attack(target));
//                        }
//                    }
//                }

//                if (!this->yetInfect && this->isInfected)
//                {
//                    for (auto& target: gameClient->getPlayers())
//                    {
//                        this->actions.push_back(ActionFactory::infect(target));
//                    }
//                }
//            }
//        }

//        for (Item& item: this->getItems())
//        {
//            item.setActive(!(this->yetWait || this->yetUsed || item.getType() == ItemType::IT_NOTEBOOK || item.getType() == ItemType::IT_ROTATION));
//        }
//    }
//    else
//    {
//        if (gameClient->getCurrentVoting() != nullptr)
//        {
//            if (!this->yetVote)
//            {
//                for (auto& target: gameClient->voteTargets())
//                {
//                    this->actions.push_back(ActionFactory::vote(target));
//                }
//            }
//            else
//            {
//                this->actions.push_back(ActionFactory::unvote());
//            }
//        }

//        for (Item& item: this->getItems())
//        {
//            item.setActive(!(item.getType() == ItemType::IT_MOP
//                             || (item.getType() == ItemType::IT_ROTATION && gameClient->getOnDutyPlayers().length() != 0)));
//        }
//    }
//}

int CurrentPlayer::getHP()
{
    return this->hp;
}

void CurrentPlayer::setHP(int hp)
{
    this->hp = hp;
}

bool CurrentPlayer::isAlien()
{
    return this->_isAlien;
}

bool CurrentPlayer::isInfected()
{
    return this->_isInfected;
}

void CurrentPlayer::setAlien(bool isAlien)
{
    this->_isAlien = isAlien;
}

QVector<Action> CurrentPlayer::getActions()
{
    return this->actions;
}

void CurrentPlayer::setActions(QVector<Action> actions)
{
    this->actions = actions;
}

bool CurrentPlayer::getYetAttack()
{
    return this->yetAttacked;
}

bool CurrentPlayer::getYetInfect()
{
    return this->yetInfect;
}

bool CurrentPlayer::getYetUsed()
{
    return this->yetUsed;
}

bool CurrentPlayer::getYetWait()
{
    return this->yetWait;
}

bool CurrentPlayer::getYetVote()
{
    return this->yetVote;
}
