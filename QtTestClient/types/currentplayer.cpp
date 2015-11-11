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

QVector<ActionType> CurrentPlayer::getActions()
{
    return this->actions;
}

void CurrentPlayer::setActions(QVector<ActionType> actions)
{
    this->actions = actions;
}

QVector<Item> CurrentPlayer::getItems()
{
    return items;
}

void CurrentPlayer::setItems(QVector<Item> items)
{
    this->items = items;
}

void CurrentPlayer::addDidAction(Action action)
{
    didActions.push_back(action);
}

bool CurrentPlayer::didPlayerAction(Action action)
{
    auto act = std::find_if(didActions.begin(), didActions.end(), [action](Action& check_act)
    {
        return (check_act.getActionType() == action.getActionType()
                && ((action.getActionType() == ActionType::TT_USE_ITEM || action.getActionType() == ActionType::TT_ULT_ITEM)
                    && (check_act.getItem().getName() == action.getItem().getName())));
    });

    return act != didActions.end();
}

bool CurrentPlayer::didPlayerAction(ActionType action)
{
    auto act = std::find_if(didActions.begin(), didActions.end(), [action](Action& check_act)
    {
        if (action == ActionType::TT_USE_ITEM || action == ActionType::TT_ULT_ITEM)
        {
            throw std::exception();
        }
        return (check_act.getActionType() == action);
    });

    return act != didActions.end();
}
