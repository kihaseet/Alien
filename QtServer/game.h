#ifndef GAME_H
#define GAME_H


#include <QtCore>
#include "player.h"
#include "voting.h"
#include "event.h"
#include "types.h"
#include <QDebug>

struct TurnObject;
class player;
class item;
class voting;


class game:public QObject
{
Q_OBJECT

public:
    bool daytime;
    int currentday;
    bool hardresolve; //true если во время голосования решение принимает капитан
    QString mopper;//дежурный
    ITEM forrepowered; //предмет, который можно юзать за счет батарейки

    voting* _currvoting;//объект текущего голосования
    QQueue <TurnObject> _nightque;//очередь ночных событий
    game();
    QMap <int,QString> connectedName; //дескриптор сокета - имя ДЛЯ ОНЛАЙН
    QMap <QString,player*>* playerlist;//имя-игрок!!!
    QMap <ITEM,item*> itemlist;//название-указатель
    QList <ITEM> brokeitemlist;
    QQueue <voting*> votingque;//очередь дневных голосований
    QQueue <QString> nightrotation; //очередь ночных дежурств
    QMultiMap <ROLE,player*> rolelist;//роль-игрок
    QList <QString> passengerlist;//список игроков без роли
    QList <ROLE> unclame_rolelist;
    QQueue <TurnObject> GameLog;    //хронология событий

    void sortNightActions();
    void StartRandomEvasion();
    void StartRandomEvasion_testing();
    bool makeNightActoins();
    void player_death(player *dead);
    void check_for_role(ROLE role);
    void check_HP(player *w);
    void dayEndCurrVoting(QString winner);
    void make_actionlist(player* who);
    void getItemByRoleAll();
    bool make_events_check(TurnObject turn);
    void day_check_over();
    void doEvents(TurnObject TO);
//обязательно понадобится проверка на изменение количества игроков во время голосования (убийство, дисконнект)
    //и собственно динамическое изменение голосов
    
    void slotAttack(TurnObject TO);

signals:
    void GuiUpdatePlayerlist(QList<player*>list);
    void GuiUpdateVotelist();
    void GuiMess2Log(QString name,QString msg);
    void startnewsessionenable(bool check);

    void startGame(QList<player*>list);
    void startPhase(int dayNo,bool day);
    void startvote(ROLE tar,QList<QString>list);
    void endvote(ROLE role,QString name,QString result);
    void send_votelist(QList<VoteObject*>list);
    void send_changes(TurnObject turn);
    void sendStat(TurnObject turn);

    void namecorrect(int name, bool isCorr);
    void rolecorrect(int name, bool isCorr);
    void sendrolelist2all(QList <player*> pllst);
    void game_over();


    void send_events(player* who);

    void send_nightmare(QQueue <TurnObject>_n,QList <player*> p);


public slots:
    void registerNewPlayer(RegisterObject reg);
    void registerRoleByPlayer(RegisterObject reg);
    void slotSendRolelist();
    void slotDisconnected(int na);
    
    void slotInfect(TurnObject TO);
    void slotWait(TurnObject TO);
    void slotUp(TurnObject TO);
    void slotDown(TurnObject TO);
    void slotAlien(TurnObject TO);
    void slotGetItem(TurnObject turn);
    void slotVote(TurnObject turn);
    void slotUnvote(TurnObject turn);
    void addRole(player *whom, ROLE what);
    void deleteRole(player *whom, ROLE what);
    void slotUseItem(TurnObject turn);
    void slotUltItem(TurnObject turn);
    void add_item(){}
    void delete_item(){}
    void start();
    void day();
    void dayNextVoting();
    void dayResolveCurrVoting(QList<QString> win);
    void dayCapCurrVoting(QString win);
    void check_for_role_capDecision(QString whom);
    void night_start();
    bool night();
    void make_events(int wwh, TurnObject turn);
    void slotUseItemCap(TurnObject turn);
    void dayCanseledVoting();
    void slotGameOver();

};

#endif // GAME_H
