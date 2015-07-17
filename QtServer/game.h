#ifndef GAME_H
#define GAME_H


#include <QtCore>
#include "player.h"
#include "voting.h"
#include "event.h"
#include <QDebug>

class ingame_event;
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

    TurnObject* _event;//объект текущего события
    voting* _currvoting;//объект текущего голосования
    QQueue <TurnObject> _nightque;//очередь ночных событий
    game();
    QMap <int,QString> connectedName; //дескриптор сокета - имя ДЛЯ ОНЛАЙН
    QMap <QString,player*>* playerlist;//имя-игрок!!!
    QMap <QString,item*> itemlist;//название-указатель
    QList <QString> brokeitemlist;
    QQueue <voting*> votingque;//очередь дневных голосований
    QQueue <QString> nightrotation; //очередь ночных дежурств
    QMultiMap <QString,player*> rolelist;//роль-игрок
    QList <QString> passengerlist;//список игроков без роли
    QList <QString> unclame_rolelist;

    void sortNightActions();
    void StartRandomEvasion();
    void StartRandomEvasion_testing();
    bool makeNightActoins();
    void player_death(player *dead);
    void check_for_role(QString role);
    void check_HP(player *w);
    void day_end_curr_voting(QString winner);
    void make_actionlist(player* who);
    void getItemByRoleAll();
    bool make_events_check(TurnObject turn);
    void day_check_over();
    void do_events(TurnObject TO);
//обязательно понадобится проверка на изменение количества игроков во время голосования (убийство, дисконнект)
    //и собственно динамическое изменение голосов
    
    void slot_attack(TurnObject TO);

signals:
    void GuiUpdatePlayerlist(QList<player*>list);
    void GuiUpdateVotelist(QMap <QString,QPair<QString,int> > votelist);
    void GuiMess2Log(QString name,QString msg);
    void startnewsessionenable(bool check);
    void startgame();
    void startday();
    void startnight();
    void namecorrect(int name);
    void nonamecorrect(int name);
    void rolecorrect(int name);
    void norolecorrect(int name);
    void sendrolelist2all(QList <player*> pllst);
    void game_over();
    void send_actionlist(player* who);
    void send_changes(player* who);
    void send_events(player* who);
    void send_votelist(player* who);
    void send_nightmare(QQueue <ingame_event*>_n,QList <player*> p);


public slots:
    void register_new_player(int tempname, TurnObject turn);
    void registerRolebyPlayer(int _na, TurnObject turn);
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
    void add_role(player *whom, QString what);
    void delete_role(player *whom, QString what);
    void slot_use_item(TurnObject turn);
    void slot_ult_item(TurnObject turn);
    void add_item(){}
    void delete_item(){}
    void start();
    void day();
    void day_next_voting();
    void day_resolve_curr_voting(QList<QString> win);
    void day_cap_curr_voting(QString who,QString win,QString useit);
    void check_for_role_capDecision(QString who,QString whom,QString useit);
    void night_start();
    bool night();
    void make_events(int wwh, QString what, QString whom, QString how, QQueue<QString> rota);
    void make_events(int wwh, TurnObject turn);
    void slot_use_item_cap(TurnObject turn);
    void day_canseled_voting();
    void slot_game_over();

};

#endif // GAME_H
