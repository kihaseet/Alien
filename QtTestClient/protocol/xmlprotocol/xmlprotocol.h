#ifndef XMLPROTOCOL_H
#define XMLPROTOCOL_H

#include <QObject>
#include "protocol/tcpclient.h"
#include "protocol/iprotocol.h"
#include "factories/eventfactory.h"
#include "factories/statupdatefactory.h"
#include <QtXml>
#include <QVector>
#include <QWaitCondition>
#include <QMutex>

class XmlProtocol : public QObject, public IProtocol
{
    Q_OBJECT
public:
    explicit XmlProtocol();
    ~XmlProtocol();

    virtual bool _connect(QString& address);
    virtual bool registerName(QString& name);
    virtual bool registerRole(QString& role);
    virtual void doAction(Action& action);
    virtual void _disconnect();
    virtual void reconnect(QString& address);
private:
    void select(QDomElement node);
    void change(QDomElement node);
    void stat(QDomElement node);
    void init(QDomElement node);

    QDomElement makeElement( QDomDocument& domDoc,
                             const QString strName,
                             const QString strAttr = QString(),
                             const QString strText = QString(),
                             const QString strAttrText = QString());

signals:
    void nameCorrect();
    void nameIncorrect();
    void roleCorrect();
    void roleIncorrect();
    void dayTime(int day);
    void nightTime();
    void startVote(Vote vote);
    void endVote(EndVote endvote);
    void playersUpdate(QVector<Player> players);
    void statUpdate(IStatUpdate stat);
    void event(IEvent event);
    void errorMessage(QString message);
    void disconnected();
public slots:
    void GetData(QString msg);
    void errormess(QString mess);
    void sig_disconnect();
};

#endif // XMLPROTOCOL_H
