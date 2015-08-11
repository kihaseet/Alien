#ifndef XML_MAKER_H
#define XML_MAKER_H
#include <QtGui>
#include <QtXml>
#include <qfile.h>
#include <qdebug.h>
#include "event.h"
#include "player.h"

class QTcpSocket;


class xml_maker:public QObject
{
Q_OBJECT
public:

    xml_maker();
    TurnObject traverseNode(const QDomNode& node);
    QQueue <QString> makeRotation(const QDomNode& node);


    QDomElement makeElement(QDomDocument& domDoc,
                             const QString strName,
                             const QString strAttr,
                             const QString strText, const QString strAttrText);


public slots:
    void new_analise(int _name, const QString input);
    void slotSendVotelist(QList<VoteObject *> votelist);
   // void send_to_all(ingame_event *_eve, QMap<QString, player *> playerlist, QMap<QString, item *> itemlist);
    void slotnamecorrect(int tempname);
    void nonamecorrect(int tempname);
    void rolecorrect(int _name);
    void norolecorrect(int _name);
    void updaterolelist(QList<player *> NameRolelist);

    void slotStartGame(QList<player*>playerlist);
    void slotStartDay(int day);
    void slotStartNight(int day);
    void slotStartVoting(ROLE target,QList<QString>list);
    void slotEndVoting(ROLE target,QString name,QString result);
    void sendTurn(TurnObject turn);
    void sendStat(TurnObject turn);

signals:
    void turn_create(int who,TurnObject turn);
    void newname(RegisterObject turn);
    void sendtoclient(int _name,QString _xmldoc);
    void send_to_all(QString _xmldoc);
    void registerRolebyPlayer(RegisterObject turn);

};




#endif // XML_MAKER_H
