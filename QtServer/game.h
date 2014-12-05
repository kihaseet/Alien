#ifndef GAME_H
#define GAME_H
#include <QtCore>
#include "player.h"
#include "voting.h"
#include "event.h"
class ingame_event;



class game:public QObject
{
Q_OBJECT
public:
    bool daytime;
    int currentday;
    bool hardresolve; //true если во время голосования решение принимает капитан

    ingame_event* _event;//объект текущего события
    voting* _currvoting;//объект текущего голосования
    QQueue <ingame_event*> _nightque;//очередь ночных событий
    game();
    QMap <QString,player*> playerlist;//имя-игрок!!!
    QMap <QString,item*> itemlist;//название-указатель
    QList <QString> brokeitemlist;
    QQueue <voting*> votingque;//очередь дневных голосований
    QQueue <QString> nightrotation; //очередь ночных дежурств
    QMultiMap <QString,player*> rolelist;//роль-игроки
    QList <QString> passengerlist;//список игроков без роли
    QList <QString> unclame_rolelist;

    void sortNightActions();
    void StartRandomEvasion();
    bool makeNightActoins();
    void player_death(player *dead);
    void check_for_role(QString role);
    void day_end_curr_voting(QString winner);
    void make_actionlist(player* who);
    void getItemByRoleAll();
    bool make_events_check(ingame_event* _event);
//обязательно понадобится проверка на изменение количества игроков во время голосования (убийство, дисконнект)
    //и собственно динамическое изменение голосов

signals:
    void GuiUpdatePlayerlist(QMap<QString,player*>list);
    void GuiUpdateVotelist(QMap <QString,QPair<QString,int> > votelist);
    void startnewsessionenable(bool check);
    void startgame();
    void startday();
    void startnight();
    void namecorrect(QString name, QString tempname);
    void nonamecorrect(QString name);
    void rolecorrect(QString name);
    void norolecorrect(QString name);
    void sendrolelist2all(QMap <QString,player*> playerlist,QList <QString>rolelist);
    void game_over();
    void send_actionlist(player* who);
    void send_changes(player* who);
    void send_events(player* who);
    void send_votelist(player* who);
    void send_nightmare(QQueue <ingame_event*>_n,QMap <QString,player*> p);


public slots:
    void register_new_player(QString tempname, QString name);
    void registerRolebyPlayer(QString _name, QString role);
    void slot_disconnected(QString name);
    void slot_attack(QString who, QString whom);
    void slot_infect(QString who, QString whom);
    void slot_wait(QString who);
    void slot_up(QString who);
    void slot_down(QString who);
    void slot_alien(QString who);
    void slot_getitem(QString who,QString useit,QString power);
    void slot_vote(QString who,QString whom);
    void slot_unvote(QString who);
    void add_role(player *whom, QString what);
    void delete_role(player *whom, QString what);
    void slot_use_item(QString who, QString whom, QString useit);
    void slot_ult_item(QString who,QString whom,QString useit);
    void add_item(){}
    void delete_item(){}
    void start();
    void day();
    void day_next_voting();
    void day_resolve_curr_voting(QList<QString> win);
    void day_cap_curr_voting(QString who,QString win,QString useit);
    void night_start();
    bool night();
    void make_events(QString who, QString what, QString whom, QString how, QQueue<QString> rota);
    void make_events(QString who, QString what, QString whom, QString how);
    void slot_use_item_cap(QString who, QString whom, QString useit);
    void day_canseled_voting();
    void slot_game_over();

};

#endif // GAME_H