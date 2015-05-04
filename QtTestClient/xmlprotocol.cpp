#include "xmlprotocol.h"

XmlProtocol::XmlProtocol(QObject *parent) : QObject(parent)
{

}

XmlProtocol::~XmlProtocol()
{

}

void XmlProtocol::setConnection(tcpclient* connection)
{
    this->connection = connection;
}

void XmlProtocol::sendRegister(QString name)
{
    QDomDocument doc("selecting");
    QDomElement domElement = doc.createElement("selecting");
    doc.appendChild(domElement);
    domElement.appendChild(makeElement(doc, "regname", "", name, ""));
    connection->sendData(doc.toString());
}

void XmlProtocol::sendSelectRole(QString role)
{
    QDomDocument doc("selecting");
    QDomElement domElement = doc.createElement("selecting");
    doc.appendChild(domElement);
    domElement.appendChild(makeElement(doc, "regrole", "", role, ""));
    connection->sendData(doc.toString());
}

void XmlProtocol::sendAction(TURN_TYPE action, QString item, QStringList targets)
{
    QDomDocument doc("changing");
    QDomElement domElement = doc.createElement("changing");
    doc.appendChild(domElement);

    if (targets.count() == 1)
    {
        switch (action)
        {
        case TT_USE_ITEM:
            domElement.appendChild(makeElement(doc, "use", "item", targets[0], item));
            break;
        case TT_ULT_ITEM:
            domElement.appendChild(makeElement(doc, "use", "ult", targets[0], item));
            break;
        case TT_ATTACK:
            domElement.appendChild(makeElement(doc, "attack", "", targets[0], ""));
            break;
        case TT_INFECT:
            domElement.appendChild(makeElement(doc, "infect", "", targets[0], ""));
            break;
        case TT_SKIP:
            domElement.appendChild(makeElement(doc, "wait", "", "", ""));
            break;
        case TT_UP:
            domElement.appendChild(makeElement(doc, "up", "", "", ""));
            break;
        case TT_DOWN:
            domElement.appendChild(makeElement(doc, "down", "", "", ""));
            break;

        }
    }
    else
    {
        QDomNode multiTarget = domElement.appendChild(makeElement(doc, "use", "item", "", item));

        for (auto& target : targets)
        {
            multiTarget.appendChild(makeElement(doc, target, "", "", ""));
        }
    }

    connection->sendData(doc.toString());
}

void XmlProtocol::sendVote(QString name, bool unvote)
{
    QDomDocument doc("voting");
    QDomElement domElement = doc.createElement("voting");
    doc.appendChild(domElement);
    domElement.appendChild(makeElement(doc, (unvote ? "unvote" : "vote"), "", name, ""));
    connection->sendData(doc.toString());
}

void XmlProtocol::GetData(QString data)
{
    QStringList list = data.split("\n\n");
    for (QString& m: list) {
        QDomDocument domDoc;
        if(domDoc.setContent(m)) {
            QDomElement domElement= domDoc.documentElement();
            if(domElement.tagName() == "select"){
                select(domElement.firstChildElement());
            }
            else if(domElement.tagName() == "change")
            {
                change(domElement.firstChildElement());
            }
            else if(domElement.tagName() == "vote")
            {
                vote(domElement.firstChildElement());
            }
        }
    }
}

void XmlProtocol::select(QDomElement node){

    SERVER_RESPONSE_TYPE type;

    while(!node.isNull()){
        if(node.tagName()=="namecorrect") {
            type = SRT_NAME_CORRECT;
        }
        else if (node.tagName() == "rolecorrect"){
            type = SRT_ROLE_CORRECT;
        }
        else if(node.tagName() == "norolecorrect"){
            type = SRT_NAME_INCORRECT;
        }
        else if (node.tagName() == "nonamecorrect") {
            type = SRT_NAME_INCORRECT;
        }
        else if(node.tagName() == "list"){
            QDomElement list = node.firstChildElement();
            QMap <QString,PlayerInfo> players;
            while(!list.isNull()){
                players.insert(list.tagName(), PlayerInfo(list.tagName(), list.text(), PS_UP));
                list = list.nextSiblingElement();
            }
            emit GetParsedData(type, players);
        }
        node = node.nextSiblingElement();
    }
}

void XmlProtocol::change(QDomElement node)
{
    this->connection = connection;
}

void XmlProtocol::vote(QDomElement node)
{

}

QDomElement XmlProtocol::makeElement( QDomDocument& domDoc,
                                      const QString strName,
                                      const QString strAttr = QString(),
                                      const QString strText = QString(),
                                      const QString strAttrText = QString()) {
    QDomElement domElement = domDoc.createElement(strName);
    if (!strAttr.isEmpty()) {
        QDomAttr domAttr = domDoc.createAttribute(strAttr);
        domAttr.setValue(strAttrText);
        domElement.setAttributeNode(domAttr);
    }
    if (!strText.isEmpty()) {
        QDomText domText = domDoc.createTextNode(strText);
        domElement.appendChild(domText);
    }
    return domElement;
}
