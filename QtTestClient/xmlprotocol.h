#ifndef XMLPROTOCOL_H
#define XMLPROTOCOL_H

#include <QObject>
#include "tcpclient.h"
#include <QtXml>
#include <QVector>
#include "alienclient.h"

struct AlienClient;

class XmlProtocol : public QObject
{
    Q_OBJECT
public:

    enum SERVER_RESPONSE_TYPE {
        SRT_NAME_CORRECT = 0,
        SRT_ROLE_CORRECT,
        SRT_NAME_INCORRECT,
        SRT_ROLE_INCORRECT,
        SRT_LIST
    };

    explicit XmlProtocol(QObject *parent = 0, tcpclient& connection);
    ~XmlProtocol();

    void sendRegister(QString name);
    void sendSelectRole(QString role);
    void sendAction(AlienClient::TURN_TYPE action, QString item, QStringList targets);
    void sendVote(QString name, bool unvote);

private:
    tcpclient* connection;
    QDomElement XmlProtocolmakeElement( QDomDocument& domDoc,
                                        const QString strName,
                                        const QString strAttr = QString(),
                                        const QString strText = QString(),
                                        const QString strAttrText = QString());
    void select(QDomElement node);
    void change(QDomElement node);
    void vote(QDomElement node);

signals:
    void GetParsedData(SERVER_RESPONSE_TYPE type, QMap<QString, AlienClient::PlayerInfo>& players);
    void GetActions(QVector<AlienClient::TurnObject> actions);

public slots:
    void GetData(QString data);
};

#endif // XMLPROTOCOL_H
