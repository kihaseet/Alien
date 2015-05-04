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
    void event_maker(QDomDocument doc, QDomElement domStat,
                     QDomElement domEvents, player* it, QMap<QString, player *> playerlist,
                     ingame_event* _eve);

    QDomElement name_role_list(QDomDocument& domDoc,QMap <QString,player*> playerlist,QList<QString>_rolelist);
    QDomElement name_role_list(QDomDocument& domDoc, QList<player *> *playerlist);
    void send_actionlist(player* who);
    void send_stat(player* who);

public slots:
    void day_event(ingame_event* _eve,QMap <QString,player*> playerlist);
    void new_analise(int _name, const QString input);
    void nightmare(QQueue<ingame_event *> _que, QList<player *> playerlist);
    void end_of_day(QMap<QString, player *> playerlist, QMap<QString, item *> itemlist);
    void send_votelist_to_all(QMap <QString,player*> playerlist,QMap <QString,QPair<QString,int> > votelist);
   // void send_to_all(ingame_event *_eve, QMap<QString, player *> playerlist, QMap<QString, item *> itemlist);
    void slotnamecorrect(int tempname);
    void nonamecorrect(int tempname);
    void rolecorrect(int _name);
    void norolecorrect(int _name);
    void updaterolelist(QList<player *> NameRolelist);

signals:
    void xml_create(int who,QString what,QString whom,QString how,QQueue<QString>rota);
    void xml_create_norot(int who,QString what,QString whom,QString how);
    void newname(int _tempname,QString who,QString avatar);
    void newrole(QString who);
    void sendtoclient(int _name,QString _xmldoc);
    void send_to_all(QString _xmldoc);
    void registerRolebyPlayer(int _name, QString role);
    void votebyPlayer(QString _name,QString whom);
    void unvotebyPlayer(QString _name);

};




#endif // XML_MAKER_H
