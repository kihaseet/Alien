#include "xmlprotocol.h"

XmlProtocol::XmlProtocol(QObject *parent) : QObject(parent)
{

}

XmlProtocol::~XmlProtocol()
{

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

void XmlProtocol::sendAction(AlienClient::TURN_TYPE action, QString item, QStringList targets)
{
    QDomDocument doc("changing");
    QDomElement domElement = doc.createElement("changing");
    doc.appendChild(domElement);

    if (targets.count() == 1)
    {
        switch (action)
        {
        case AlienClient::TT_USE_ITEM:
            domElement.appendChild(makeElement(doc, "use", "item", targets[0], item));
            break;
        case AlienClient::TT_ULT_ITEM:
            domElement.appendChild(makeElement(doc, "use", "ult", targets[0], item));
            break;
        case AlienClient::TT_ATTACK:
            domElement.appendChild(makeElement(doc, "attack", "", targets[0], ""));
            break;
        case AlienClient::TT_INFECT:
            domElement.appendChild(makeElement(doc, "infect", "", targets[0], ""));
            break;
        case AlienClient::TT_SKIP:
            domElement.appendChild(makeElement(doc, "wait", "", "", ""));
            break;
        case AlienClient::TT_UP:
            domElement.appendChild(makeElement(doc, "up", "", "", ""));
            break;
        case AlienClient::TT_DOWN:
            domElement.appendChild(makeElement(doc, "down", "", "", ""));
            break;

        }
    }
    else
    {
        auto multiTarget = domElement.appendChild(makeElement(doc, "use", "item", "", item));

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
    QStringList list = msg.split("\n\n");
    for (QString& m: list) {
        QDomDocument domDoc;
        if(domDoc.setContent(m)) {
            QDomElement domElement= domDoc.documentElement();
            if(domElement.tagName()=="select"){
                select(domElement.firstChildElement());
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
            QMap <QString,AlienClient::PlayerInfo> players;
            while(!list.isNull()){
                players.insert(list.tagName(), AlienClient::PlayerInfo(list.tagName(), list.text(), AlienClient::PLAYER_STATUS::PS_UP));
                list = list.nextSiblingElement();
            }
            emit GetParsedData(type, players);
        }
        node = node.nextSiblingElement();
    }
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
