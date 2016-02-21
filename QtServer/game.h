#ifndef GAME_H
#define GAME_H
#define TARGET targets.first()

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
    bool started;
    TimeType daytime;
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
    void day_end_curr_voting(QString winner);
    void make_actionlist(player* who);
    void getItemByRoleAll();
    bool make_events_check(TurnObject turn);
    void day_check_over();
    void do_events(TurnObject TO);
    void sendMsg(player* who,QString msg);
//обязательно понадобится проверка на изменение количества игроков во время голосования (убийство, дисконнект)
    //и собственно динамическое изменение голосов
    
    void slot_attack(TurnObject TO);

    bool isHunted(QStringList playerhunt, TurnObject turn);
    void slot_use_battery(ITEM item);
    QList<QString> makeRotationList();
    void day_gameover();
signals:
    void GuiUpdatePlayerlist(QList<player*>list);
    void GuiUpdateVotelist();
    void GuiMess2Log(QString name,QString msg);
    void startnewsessionenable(bool check);

    void startgame(QList<player*>list);
    void startPhase(int dayNo,bool day);
    void startvote(ROLE tar,QList<QString>list);
    void endvote(ROLE role,QString name,QString result);
    void send_changes(TurnObject turn);
    void send_stat(TurnObject turn);
    void send_mess(int whoID,QString mess);
    void game_over();

    /*блок сигналов для нового протокола*/
    void sigGamePlayerDisconnect(QString name);
    void sigGameRegisterAnswer(int connectID, RegisterStatusType isCorrect);
    void sigGameRegisterUpdate(QList<player*> NameRolelist);
    void sigGameStartGame(QList<player*>playerlist);
    void sigGameTimeSwitch(int dayNo, TimeType type);
    void sigGameVoting(VotingType type ,QList<QString>list, ROLE targets);
    void sigGameEndVoting(ROLE targets,QString name,QString result);
    void sigGameChange(TurnObject turn);                                      //изменения с другими игроками
    void sigGameInventoryChange(int connectID,InvetoryChangeType type, ITEM item, int charge);  //изменения в инвентаре
    void sigGamePlayerChange(int connectID, PlayerChangeType type, int value);                  //изменение с хп, заражением или статусом(?)
    void sigGameActionRequest(int connectID, RequestType type, QList<QString> targets);         //посылается при хардрезолве и нидротации
    void sigGameActionResult(int connectID, ResultType type, TURN_TYPE action);                 //подтверждение действия или предмета

public slots:
    void register_new_player(RegisterObject reg);
    void registerRolebyPlayer(RegisterObject reg);
    void slotSendRolelist();
    void slot_disconnected(int na);
    
    void slot_infect(TurnObject TO);
    void slot_wait(TurnObject TO);
    void slot_up(TurnObject TO);
    void slot_down(TurnObject TO);
    void slot_alien(TurnObject TO);
    void slot_getitem(TurnObject turn);
    void slot_vote(TurnObject turn);
    void slot_unvote(TurnObject turn);
    void add_role(player *whom, ROLE what);
    void delete_role(player *whom, ROLE what);
    void slot_use_item(TurnObject turn);
    void slot_ult_item(TurnObject turn);
    void add_item(){}
    void delete_item(){}
    void start();
    void day();
    void day_next_voting();
    void day_resolve_curr_voting(QList<QString> win);
    void day_cap_curr_voting(QString win);
    void check_for_role_capDecision(QString whom);
    void night_start();
    bool night();
    void make_events(int wwh, TurnObject turn);
    void slot_use_item_cap(TurnObject turn);
    void day_canseled_voting();
    void slot_game_over();

};

#endif // GAME_H
