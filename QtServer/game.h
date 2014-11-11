#ifndef GAME_H
#define GAME_H
#include <QtCore>
#include "player.h"
#include "voting.h"
#include "event.h"

class game:public QObject
{
Q_OBJECT
public:
    bool daytime;

    ingame_event* _event;
    game();
    QMap <QString,player> playerlist;//имя-игрок!!!
    QMap <QString,item> itemlist;
    QQueue <voting> votingque;
    QMap <QString,player> rolelist;
    QList <player> passengerlist;

signals:
    void startgame();
    void startday();
    void startnight();
    void namecorrect(QString name, QString tempname);
    void nonamecorrect(QString name);
    void rolecorrect(QString name);
    void norolecorrect(QString name);
    void sendrolelist2all(QMap <QString,player> playerlist,QMap <QString,player>rolelist);


public slots:
    void register_new_player(QString tempname, QString name);
    void registerRolebyPlayer(QString _name, QString role);
    void add_role();
    void delete_role();
    void use_item();
    void add_item();
    void delete_item();
    void start();
    void day();
    void night();
    void make_events();

};

#endif // GAME_H
