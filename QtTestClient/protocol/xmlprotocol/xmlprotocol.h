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

class XmlProtocol : public IProtocol
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
public slots:
    void GetData(QString msg);
    void errormess(QString mess);
    void sig_disconnect();
    void sig_connected();
};

#endif // XMLPROTOCOL_H
