#include "gameclient.h"
#include "types/currentplayer.h"
#include <typeinfo>

void GameClient::recalcActions()
{
    QVector<ActionType> actions;

    if (Night)
    {
        if (!this->currentPlayer->didPlayerAction(ActionType::TT_SKIP))
        {
            actions.push_back(ActionType::TT_SKIP);

            if (this->currentPlayer->isAlien())
            {
                if (!this->currentPlayer->didPlayerAction(ActionType::TT_ATTACK))
                {
                    actions.push_back(ActionType::TT_ATTACK);
                }

                if (!this->currentPlayer->didPlayerAction(ActionType::TT_INFECT) && this->currentPlayer->isInfected())
                {
                    actions.push_back(ActionType::TT_INFECT);
                }
            }
        }

        auto items = this->currentPlayer->getItems();
        for (Item& item: items)
        {
            item.setActive(!(this->currentPlayer->didPlayerAction(ActionType::TT_SKIP)
                             || this->currentPlayer->didPlayerAction(ActionType::TT_USE_ITEM)
                             || this->currentPlayer->didPlayerAction(ActionType::TT_ULT_ITEM)
                             || item.getType() == ItemType::IT_NOTEBOOK
                             || item.getType() == ItemType::IT_ROTATION));
        }

        this->currentPlayer->setItems(items);
    }
    else
    {
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

PlayerPtr GameClient::getPlayer(QString name)
{
    for (int i = 0; i < this->players.length(); i++)
    {
        if (this->players[i]->getName() == name)
        {
            return this->players[i];
        }
    }

    return nullptr;
}

void GameClient::brute_copy(QVector<PlayerPtr> &from, QConstPlayersVector &to)
{
    for (auto& f: from)
    {
        to.push_back(f);
    }
}

GameClient::GameClient()
{
    this->Night = false;
    this->onDutyPlayers.clear();
    this->players.clear();
    this->protocol  = new XmlProtocol();
    this->voteTargets.clear();
    this->vote = nullptr;
    this->currentPlayer.reset(new CurrentPlayer("", UP, QStringList(), PASSENGER));

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

QConstPlayersVector GameClient::getPlayers()
{
    QConstPlayersVector const_players;
    brute_copy(this->players, const_players);
    return const_players;
}

const PlayerPtr GameClient::getPlayerByName(QString name)
{
    auto p = this->getPlayer(name);

    if (p == nullptr)
    {
        throw std::exception();
    }
    else
    {
        return p;
    }
}

QConstPlayersVector GameClient::getVoteTargets()
{
    QConstPlayersVector const_players;
    auto vote_targets = this->voteTargets.keys().toVector();
    brute_copy(vote_targets, const_players);
    return const_players;
}

QConstPlayersVector GameClient::getOnDutyPlayers()
{
    QConstPlayersVector const_players;
    brute_copy(onDutyPlayers, const_players);
    return const_players;
}

CurrentPlayerPtr GameClient::getCurrentPlayer()
{
    return this->currentPlayer;
}

QVector<ItemType> GameClient::getWreckedItems()
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
        for (auto& player: this->players)
        {
            if (player->getName() == player_name)
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
    auto find_player = [&](QString name) -> PlayerPtr
    {
      for (auto& player: this->players)
      {
          if (player->getName() == name)
          {
              return player;
          }
      }

      return nullptr;
    };

    for (auto& player: players)
    {
        PlayerPtr s_player = find_player(player.getName());

        if (s_player != nullptr)
        {
            s_player->update(player);
        }
        else
        {
            this->players.push_back(std::make_shared<Player>(player));
        }
    }

    emit updatePlayers(this->getPlayers());
}

void GameClient::statUpdate(const IStatUpdate &stat)
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
        this->voteTargets[this->getPlayerByName(event->getTarget())] += (event->getVoteUp() ? 1 : -1);
        emit voteUpdate(event->getTarget(), this->voteTargets[this->getPlayerByName(event->getTarget())]);

    }
    else if (typeid(e) == typeid(EventRole))
    {
        EventRole* event = ((EventRole*)&e);

        PlayerPtr p = this->getPlayer(event->getTarget());

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

        emit updatePlayers(this->getPlayers());
    }
}

void GameClient::errorMessage(QString message)
{
    emit errorLog(message);
}

void GameClient::disconnected()
{
    emit log("Disconnected from server.");
}

void GameClient::sig_connected()
{
    emit connected();
}

