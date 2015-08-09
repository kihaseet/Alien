#include "gameclient.h"
#include "types/currentplayer.h"

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
}

Vote *GameClient::getCurrentVoting()
{
    return this->vote;
}

QVector<Player> GameClient::getPlayers()
{
    return this->players;
}

QVector<Player> GameClient::getVoteTargets()
{
    return this->voteTargets.keys().toVector();
}

QVector<Player> GameClient::getOnDutyPlayers()
{
    return this->onDutyPlayers;
}

int GameClient::getCurrentDay()
{
    return this->currentDay;
}

bool GameClient::connect(QString address)
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
        this->lastVote = action.getTargets()[0];
    }
    else if (action.getActionType() == TT_UNVOTE)
    {
        QVector<ITarget> targets;
        targets.push_back(this->lastVote);
        action.setTargets(targets);
    }
    protocol->doAction(action);
    return true;
}

void GameClient::disconnect()
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

void GameClient::event(IEvent event)
{
    emit log(event.getDisplayMsg());
}

void GameClient::errorMessage(QString message)
{
    emit errorLog(message);
}

void GameClient::disconnected()
{
    emit log("Disconnected for server.");
}

