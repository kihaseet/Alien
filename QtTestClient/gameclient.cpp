#include "gameclient.h"
#include "types/currentplayer.h"
#include <typeinfo>

void GameClient::recalcActions()
{
    QVector<Action> actions;

    if (Night)
    {
        if (!this->currentPlayer->getYetWait())
        {
            actions.push_back(ActionFactory::sleep());

            if (this->currentPlayer->isAlien())
            {
                if (!this->currentPlayer->getYetAttack())
                {
                    for (auto& target: players)
                    {
                        if (target.getName() != this->currentPlayer->getName())
                        {
                            actions.push_back(ActionFactory::attack(target));
                        }
                    }
                }

                if (!this->currentPlayer->getYetInfect() && this->currentPlayer->isInfected())
                {
                    for (auto& target: players)
                    {
                        actions.push_back(ActionFactory::infect(target));
                    }
                }
            }
        }

        auto items = this->currentPlayer->getItems();
        for (Item& item: items)
        {
            item.setActive(!(this->currentPlayer->getYetWait()
                             || this->currentPlayer->getYetUsed()
                             || item.getType() == ItemType::IT_NOTEBOOK
                             || item.getType() == ItemType::IT_ROTATION));
        }

        this->currentPlayer->setItems(items);
    }
    else
    {
        if (this->vote != nullptr)
        {
            if (!this->currentPlayer->getYetVote())
            {
                for (auto& target: this->vote->getTargets())
                {
                    actions.push_back(ActionFactory::vote(*this->getPlayer(target)));
                }
            }
            else
            {
                actions.push_back(ActionFactory::unvote());
            }
        }

        auto items = this->currentPlayer->getItems();
        for (Item& item: items)
        {
            item.setActive(!(item.getType() == ItemType::IT_MOP
                             || (item.getType() == ItemType::IT_ROTATION && onDutyPlayers.length() != 0)));
        }

        this->currentPlayer->setItems(items);
    }

    emit updateActions(this->currentPlayer->getActions());
    emit updateItems(this->currentPlayer->getItems());
}

Player *GameClient::getPlayer(QString name)
{
    for (int i = 0; i < this->players.length(); i++)
    {
        if (this->players[i].getName() == name)
        {
            return &this->players[i];
        }
    }

    return nullptr;
}

GameClient::GameClient()
{
    this->Night = false;
    this->onDutyPlayers.clear();
    this->players.clear();
    this->protocol  = new XmlProtocol();
    this->voteTargets.clear();
    this->vote = nullptr;
    this->currentPlayer = new CurrentPlayer("", UP, QStringList(), PASSENGER);

    ActionFactory::currentPlayer = this->currentPlayer;

    QObject::connect(protocol, SIGNAL(dayTime(int)), this, SLOT(dayTime(int)));
    QObject::connect(protocol, SIGNAL(disconnected()), this, SLOT(disconnected()));
    QObject::connect(protocol, SIGNAL(connected()), this, SLOT(sig_connected()));
    QObject::connect(protocol, SIGNAL(endVote(EndVote)), this, SLOT(endVote(EndVote)));
    QObject::connect(protocol, SIGNAL(errorMessage(QString)), this, SLOT(errorMessage(QString)));
    QObject::connect(protocol, SIGNAL(event(const IEvent&)), this, SLOT(sig_event(const IEvent&)));
    QObject::connect(protocol, SIGNAL(nameCorrect()), this, SLOT(nameCorrect()));
    QObject::connect(protocol, SIGNAL(nameIncorrect()), this, SLOT(nameIncorrect()));
    QObject::connect(protocol, SIGNAL(nightTime()), this, SLOT(nightTime()));
    QObject::connect(protocol, SIGNAL(playersUpdate(QVector<Player>)), this, SLOT(playersUpdate(QVector<Player>)));
    QObject::connect(protocol, SIGNAL(playerUlted(ItemType)), this, SLOT(playerUlted(ItemType)));
    QObject::connect(protocol, SIGNAL(roleCorrect()), this, SLOT(roleCorrect()));
    QObject::connect(protocol, SIGNAL(startVote(Vote)), this, SLOT(startVote(Vote)));
    QObject::connect(protocol, SIGNAL(statUpdate(IStatUpdate)), this, SLOT(statUpdate(IStatUpdate)));
}

Vote *GameClient::getCurrentVoting()
{
    return this->vote;
}

QVector<Player> GameClient::getPlayers()
{
    return this->players;
}

Player GameClient::getPlayerByName(QString name)
{
    Player* p = this->getPlayer(name);

    if (p == nullptr)
    {
        throw std::exception();
    }
    else
    {
        return *p;
    }
}

QVector<Player> GameClient::getVoteTargets()
{
    return this->voteTargets.keys().toVector();
}

QVector<Player> GameClient::getOnDutyPlayers()
{
    return this->onDutyPlayers;
}

CurrentPlayer *GameClient::getCurrentPlayer()
{
    return this->currentPlayer;
}

QVector<ItemType> &GameClient::getWreckedItems()
{
    return this->ultedItems;
}

int GameClient::getCurrentDay()
{
    return this->currentDay;
}

bool GameClient::connectToServer(QString address)
{
    return protocol->_connect(address);
}

bool GameClient::registerName(QString name)
{
    this->currentPlayer->setName(name);
    return protocol->registerName(name);
}

bool GameClient::registerRole(QString role)
{
    this->currentPlayer->setRoles(QStringList(role));
    return protocol->registerRole(role);
}

bool GameClient::doAction(Action action)
{
    if (action.getActionType() == TT_VOTE)
    {
        this->vote->setCurrentTarget(action.getTargets()[0].getName());
    }
    else if (action.getActionType() == TT_UNVOTE)
    {
        QVector<ITarget> targets;
        targets.push_back(ITarget(this->vote->getCurrentTarget()));
        action.setTargets(targets);
        this->vote->setCurrentTarget("");
    }
    protocol->doAction(action);
    return true;
}

void GameClient::disconnectFromServer()
{
    protocol->_disconnect();
}

bool GameClient::reconnect()
{
    protocol->reconnect(this->address);
    return true;
}

void GameClient::nameCorrect()
{
    emit registerNameStatus(true);
}

void GameClient::nameIncorrect()
{
    emit registerNameStatus(false);
}

void GameClient::roleCorrect()
{
    emit registerRoleStatus(true);
}

void GameClient::roleIncorrect()
{
    emit registerRoleStatus(false);
}

void GameClient::dayTime(int day)
{
    this->Night = false;
    currentDay = day;
    emit dayUpdate(day, true);
    this->recalcActions();
}

void GameClient::nightTime()
{
    this->Night = true;
    emit dayUpdate(currentDay, false);
    this->recalcActions();
}

void GameClient::startVote(Vote vote)
{
    if (this->vote != nullptr)
    {
        delete this->vote;
    }

    this->vote = new Vote(vote.getVotingFor(), vote.getTargets());

    this->voteTargets.clear();
    for (QString player_name: this->vote->getTargets())
    {
        for (Player& player: this->players)
        {
            if (player.getName() == player_name)
            {
                this->voteTargets[player] = 0;
                break;
            }
        }
    }

    emit startVoting(*this->vote);
    this->recalcActions();
}

void GameClient::endVote(EndVote endvote)
{
    if (this->vote != nullptr)
    {
        delete this->vote;
    }

    this->vote = nullptr;
    voteTargets.clear();
    emit endVoting();
    emit log(endvote.getDisplayMsg());
    this->recalcActions();
}

void GameClient::playerUlted(ItemType item)
{
    this->ultedItems.push_back(item);
}

void GameClient::playersUpdate(QVector<Player> players)
{
    this->players = players;

    emit updatePlayers(this->players);
}

void GameClient::statUpdate(IStatUpdate stat)
{
    stat.apply(*this->currentPlayer);

    emit updateActions(this->currentPlayer->getActions());
    emit updateItems(this->currentPlayer->getItems());
}

void GameClient::sig_event(const IEvent &e)
{
    emit log(e.getDisplayMsg());

    if (typeid(e) == typeid(EventVoting))
    {
        const EventVoting* event = ((const EventVoting*)&e);
        for (auto& targetPlayer: this->voteTargets.keys())
        {
            if (targetPlayer.getName() == event->getTarget())
            {
                this->voteTargets[targetPlayer] += (event->getVoteUp() ? 1 : -1);
                emit voteUpdate(targetPlayer.getName(), this->voteTargets[targetPlayer]);
                break;
            }
        }
    }
    else if (typeid(e) == typeid(EventRole))
    {
        EventRole* event = ((EventRole*)&e);

        Player* p = this->getPlayer(event->getTarget());

        if (p != nullptr)
        {
            QStringList roles = p->getRoles();
            if (event->gotRole())
            {
                roles.append(event->getRoleUpdate());
            }
            else
            {
                roles.removeAll(event->getRoleUpdate());
            }
            p->setRoles(roles);
        }

        emit updatePlayers(this->players);
    }
}

void GameClient::errorMessage(QString message)
{
    emit errorLog(message);
}

void GameClient::disconnected()
{
    emit log("Disconnected for server.");
}

void GameClient::sig_connected()
{
    emit connected();
}

