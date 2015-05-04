#ifndef XMLPROTOCOL_H
#define XMLPROTOCOL_H

#include "types.h"
#include <QObject>
#include "tcpclient.h"
#include <QtXml>
#include <QVector>

class XmlProtocol : public QObject
{
    Q_OBJECT
public:
    explicit XmlProtocol(QObject *parent = 0);
    ~XmlProtocol();

    void setConnection(tcpclient *connection);

    void sendRegister(QString name);
    void sendSelectRole(QString role);
    void sendAction(TURN_TYPE action, QString item, QStringList targets);
    void sendVote(QString name, bool unvote);

private:
    tcpclient* connection;
    QDomElement makeElement(QDomDocument& domDoc,
                             const QString strName,
                             const QString strAttr,
                             const QString strText, const QString strAttrText);
    void select(QDomElement node);
    void change(QDomElement node);
    void vote(QDomElement node);
    void init(QDomElement node);

signals:
//    void GetParsedData(SERVER_RESPONSE_TYPE type, QMap<QString, PlayerInfo>& players);
//    void GetActions(QVector<TurnObject> actions);

    void onChange(onChangeInfo info);
    void onSelect(onSelectInfo info);
    void onVote(onVoteInfo info);
    void onInit(onInitInfo info);

public slots:
    void GetData(QString data);
};

#endif // XMLPROTOCOL_H
