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
    void slotStartVoting(ROLE targets,QList<QString>list);
    void slotEndVoting(ROLE targets,QString name,QString result);
    void slotSendTurn(TurnObject turn);
    void slotSendStat(TurnObject turn);
    void slotSendMess(player *who, QString mess);


};




#endif // XML_MAKER_H
