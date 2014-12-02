#ifndef XML_MAKER_H
#define XML_MAKER_H
#include <QtGui>
#include <QtXml>
#include <qfile.h>
#include <qdebug.h>
#include "event.h"
#include "player.h"

class QTcpSocket;

struct xml_msg
{
    QString who,whom,what,how;
    QQueue <QString>rotation;
};


class xml_maker:public QObject
{
Q_OBJECT
public:
    xml_maker();
    xml_msg traverseNode(const QDomNode& node, xml_msg _xml,QString mod);
    QQueue <QString> makeRotation(const QDomNode& node);


    QDomElement makeElement(QDomDocument& domDoc,
                             const QString strName,
                             const QString strAttr,
                             const QString strText, const QString strAttrText);

    QDomElement append_actions(QDomDocument &domDoc, player* player);
    QDomElement append_events(QDomDocument &domDoc, QMap <QString,player*> playerlist);
    QDomElement append_stats(QDomDocument &domDoc, player* player);

    QDomElement name_role_list(QDomDocument& domDoc,QMap <QString,player*> playerlist,QList<QString>_rolelist);
    void send_actionlist(player* who);
    void send_stat(player* who);

public slots:
    void new_analise(const QString _name, const QString input);
    void nightmare(QQueue<ingame_event *> _que, QMap<QString, player *> playerlist, QMap<QString, item *> itemlist);
    void end_of_day(QMap<QString, player *> playerlist, QMap<QString, item *> itemlist);
    void send_votelist_to_all(QMap <QString,player*> playerlist,QMap <QString,QPair<QString,int> > votelist);
    void send_to_all(ingame_event *_eve, QMap<QString, player *> playerlist, QMap<QString, item *> itemlist);
    void slotnamecorrect(QString tempname, QString _name);
    void nonamecorrect(QString tempname);
    void rolecorrect(QString _name);
    void norolecorrect(QString _name);
    void updaterolelist(QMap<QString, player *> playerlist, QList<QString> _rolelist);

signals:
    void xml_create(QString who,QString what,QString whom,QString how,QQueue<QString>rota);
    void newname(QString _tempname,QString who);
    void newrole(QString who);
    void sendtoclient(QString _name,QString _xmldoc);
    void noVerifyClientName(QString tempname);
    void namecorrect(QString tempname,QString name);
    void registerRolebyPlayer(QString _name, QString role);

};




#endif // XML_MAKER_H
