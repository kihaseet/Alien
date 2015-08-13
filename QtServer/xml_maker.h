#ifndef XML_MAKER_H
#define XML_MAKER_H
#include <QtGui>
#include <QtXml>
#include <qfile.h>
#include <qdebug.h>
#include "event.h"
#include "player.h"
#include "protocol.h"

class QTcpSocket;


class xml_maker:public Protocol
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
    void newAnalise(int _name, const QString input);
    void slotSendVoteList(QList<VoteObject *> votelist);
    void slotNameCorrect(int tempname, bool isCorrect);
    void slotRoleCorrect(int _name, bool isCorrect);
    void slotUpdateRoleList(QList<player *> NameRolelist);
    void slotDisconnected(QList<player *> playerlist){}

    void slotStartGame(QList<player*>playerlist);
    void slotStartPhase(int dayNo, bool isDay);
    void slotStartVoting(ROLE target,QList<QString>list);
    void slotEndVoting(ROLE target,QString name,QString result);
    void slotSendTurn(TurnObject turn);
    void slotSendStat(TurnObject turn);

signals:
    /*void turn_create(int who,TurnObject turn);
    void newname(RegisterObject turn);
    void sendtoclient(int _name,QString _xmldoc);
    void send_to_all(QString _xmldoc);
    void registerRolebyPlayer(RegisterObject turn);*/

};




#endif // XML_MAKER_H
