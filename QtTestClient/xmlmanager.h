#ifndef XMLMAKER_H
#define XMLMAKER_H
#include <QtXml>
#include <QObject>

class xmlmaker:public QObject
{
Q_OBJECT
public:
    xmlmaker();
    void select(QDomElement node);
    QDomElement makeElement(QDomDocument& domDoc,
                             const QString strName,
                             const QString strAttr,
                             const QString strText, const QString strAttrText);
signals:
    void signal_NameCorrect();
    void signal_NoNameCorrect();
    void signal_RoleCorrect();
    void signal_NoRoleCorrect();
    void signal_RoleList(QList <QString>* list);
    void signal_game_Start();
    void signal_game_NightStart();
    void signal_game_DayStart();
    void signal_votingAlienStart();
    void signal_votingAlienFin();
    void signal_votingChangeVote();
    void signal_playerlist(QMap <QString,QString> list);

    void send2serv(QString msg);
public slots:
    void slot_sendNewName(QString what, QString name);
    void new_analise(QString msg);
};

#endif // XMLMAKER_H
