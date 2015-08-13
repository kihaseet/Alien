#include "xmlprotocol.h"

XmlProtocol::XmlProtocol()
{
    connect(&tcpClient, SIGNAL(GetData(QString)), this, SLOT(GetData(QString)));
    connect(&tcpClient, SIGNAL(sig_connected()), this, SLOT(sig_connected()));
    connect(&tcpClient, SIGNAL(sig_disconnect()), this, SLOT(sig_disconnect()));
}

XmlProtocol::~XmlProtocol()
{

}

bool XmlProtocol::_connect(QString &address)
{
    tcpClient.connect_(address, 21277);
    return true;
}

bool XmlProtocol::registerName(QString &name)
{
    QDomDocument doc("selecting");
    QDomElement domElement = doc.createElement("selecting");
    doc.appendChild(domElement);
    domElement.appendChild(makeElement(doc, "regname", "", name, ""));
    tcpClient.sendData(doc.toString());
    return true;
}

bool XmlProtocol::registerRole(QString &role)
{
    QDomDocument doc("selecting");
    QDomElement domElement = doc.createElement("selecting");
    doc.appendChild(domElement);
    domElement.appendChild(makeElement(doc, "regrole", "", role, ""));
    tcpClient.sendData(doc.toString());
    return true;
}

void XmlProtocol::doAction(Action &action)
{
    QDomDocument doc("changing");
    QDomElement domElement = doc.createElement("changing");
    doc.appendChild(domElement);

    if (action.getTargets().length() == 1)
    {
        switch (action.getActionType())
        {
        case TT_USE_ITEM:
            domElement.appendChild(makeElement(doc, "use", "item", action.getTargets()[0].getName(), action.getItem().getName()));
            break;
        case TT_ULT_ITEM:
            domElement.appendChild(makeElement(doc, "use", "ult", action.getTargets()[0].getName(), action.getItem().getName()));
            break;
        case TT_ATTACK:
            domElement.appendChild(makeElement(doc, "attack", "", action.getTargets()[0].getName(), ""));
            break;
        case TT_VOTE:
            domElement.appendChild(makeElement(doc, "vote", "", action.getTargets()[0].getName(), ""));
            break;
        case TT_UNVOTE:
            domElement.appendChild(makeElement(doc, "unvote", "", action.getTargets()[0].getName(), ""));
            break;
        case TT_INFECT:
            domElement.appendChild(makeElement(doc, "infect", "", action.getTargets()[0].getName(), ""));
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
        case TT_BADGE:
            domElement.appendChild(makeElement(doc, "use", "badge", action.getTargets()[0].getName(), action.getItem().getName()));
            break;
        }
    }
    else
    {
        QDomNode multiTarget;

        if (action.getActionType() == TT_BADGE)
        {
            multiTarget = domElement.appendChild(makeElement(doc, "use", "badge", "", action.getItem().getName()));
        }
        else
        {
            multiTarget = domElement.appendChild(makeElement(doc, "use", "item", "", action.getItem().getName()));
        }

        for (auto& target : action.getTargets())
        {
            multiTarget.appendChild(makeElement(doc, target.getName(), "", "", ""));
        }
    }

    tcpClient.sendData(doc.toString());
}

void XmlProtocol::_disconnect()
{
    QDomDocument doc("changing");
    QDomElement domElement = doc.createElement("changing");
    doc.appendChild(domElement);

    domElement.appendChild(makeElement(doc, "disconnect", "", "", ""));

    tcpClient.sendData(doc.toString());
}

void XmlProtocol::reconnect(QString &address)
{
    this->_connect(address);
}

void XmlProtocol::GetData(QString data)
{
    qDebug() << "XmlProtocol: XML DATA: \n" << data;
    QStringList list = data.split("\n\n");
    for (QString& m: list) {
        QDomDocument domDoc;
        if(domDoc.setContent(m)) {
            QDomElement domElement= domDoc.documentElement();
            if(domElement.tagName() == "select"){
                select(domElement);
            }
            else if(domElement.tagName() == "change")
            {
                change(domElement);
            }
            else if(domElement.tagName() == "stat")
            {
                stat(domElement);
            }
            else if(domElement.tagName() == "init")
            {
                init(domElement);
            }
        }
    }
}

void XmlProtocol::errormess(QString mess)
{
    emit errorMessage(mess);
}

void XmlProtocol::sig_disconnect()
{
    emit disconnected();
}

void XmlProtocol::sig_connected()
{
    emit connected();
}

void XmlProtocol::select(QDomElement node){
    node = node.firstChildElement();

    while(!node.isNull()){
        if(node.tagName()=="namecorrect") {
            emit nameCorrect();
        }
        else if (node.tagName() == "rolecorrect"){
            emit roleCorrect();
        }
        else if(node.tagName() == "norolecorrect"){
            emit roleIncorrect();
        }
        else if (node.tagName() == "nonamecorrect") {
            emit nameIncorrect();
        }
        else if(node.tagName() == "list")
        {

            QVector<Player> players;

            QDomElement player = node.firstChildElement();
            while(!player.isNull()){
                QString name = player.tagName();
                QString role = player.firstChildElement("role").text();
                int image = 0;

                players.push_back(Player(name, QStringList(role), (PlayerImage)image));
                player = player.nextSiblingElement();
            }

            emit playersUpdate(players);
        }
        node = node.nextSiblingElement();
    }
}

void XmlProtocol::change(QDomElement node)
{
    for (int i = 0; i < node.childNodes().length(); i++)
    {
        QDomElement eventEl = node.childNodes().at(i).toElement();
        if (eventEl.toElement().tagName() == "event")
        {
            QString name = eventEl.attribute("name");

            if (eventEl.hasAttribute("useitem"))
            {
                ItemType item = (ItemType)eventEl.attribute("useitem").toInt();
                QString target = eventEl.text();

                emit event(EventFactory::Item("использовал", name, target, Item(item, 0)));
            }
            else if (eventEl.hasAttribute("useult"))
            {
                ItemType item = (ItemType)eventEl.attribute("useult").toInt();
                QString target = eventEl.text();

                emit event(EventFactory::Item("ультанул", name, target, Item(item, 0)));
                emit playerUlted(item);
            }
            else if (eventEl.hasAttribute("status"))
            {
                Status status = (Status)eventEl.attribute("status").toInt();

                switch(status)
                {
                case Status::UP:
                case Status::DOWN:
                case Status::DIED:
                    emit event(EventFactory::StatusEvent(name, status));
                    break;
                default:
                    emit event(EventFactory::Duty(name));
                }

            }
            else if (eventEl.hasAttribute("getrole"))
            {
                QString role = eventEl.attribute("getrole");

                emit event(EventFactory::Role(role, name, true));

            }
            else if (eventEl.hasAttribute("delrole"))
            {
                QString role = eventEl.attribute("delrole");

                emit event(EventFactory::Role(role, name, false));

            }
            else if (eventEl.hasAttribute("voting"))
            {
                QString votingStatus = eventEl.attribute("voting");
                QString target = eventEl.firstChildElement().tagName();
                emit event(EventFactory::Voting(name, target, votingStatus == "up"));
            }
        }
    }
}

void XmlProtocol::stat(QDomElement node)
{
    for (int i = 0; i < node.childNodes().length(); i++)
    {
        QDomElement statEl = node.childNodes().at(i).toElement();

        if (statEl.tagName() == "additem")
        {
            ItemType item = (ItemType)statEl.attribute("item", "-1").toInt();
            int charge = statEl.attribute("power", "-1").toInt();
            emit statUpdate(StatUpdateFactory::addItem(Item(item, charge)));
        }
        else if (statEl.tagName() == "delitem")
        {
            ItemType item = (ItemType)statEl.attribute("item", "-1").toInt();
            emit statUpdate(StatUpdateFactory::delItem(Item(item, 0)));
        }
        else if (statEl.tagName() == "useditem")
        {
            ItemType item = (ItemType)statEl.attribute("item", "-1").toInt();
            emit statUpdate(StatUpdateFactory::delItem(Item(item, 0)));
        }
        else if (statEl.tagName() == "alien")
        {
            emit statUpdate(StatUpdateFactory::alien());
        }
        else if (statEl.tagName() == "HP")
        {
            int hp = statEl.attribute("size", "0").toInt();
            emit statUpdate(StatUpdateFactory::changeHP(hp));
        }
    }
}

void XmlProtocol::init(QDomElement node)
{
    if (!node.firstChildElement("startgame").isNull())
    {
        QDomElement list = node.firstChildElement("list");

        QVector<Player> update_players;

        for (int i = 0; i < list.childNodes().length(); i++)
        {
            auto player = list.childNodes().at(i);
            if (player.isElement() && !player.isNull())
            {
                QString name = player.toElement().tagName();
                bool onDuty = player.toElement().attribute("onduty", "0").toInt() == 1;
                bool online = player.toElement().attribute("online", "0").toInt() == 1;
                Status status = (Status)player.toElement().attribute("status", "0").toInt();
                PlayerImage img = (PlayerImage)player.toElement().attribute("avatar", "0").toInt();
                QStringList roles;

                for (int r = 0; r < player.childNodes().length(); r++)
                {
                    auto role = player.childNodes().at(r);
                    if (!role.isNull() && role.isElement())
                    {
                        roles.append(role.toElement().tagName());
                    }
                }

                update_players.push_back(Player(name, roles, img, onDuty, online, status));
            }
        }

        emit playersUpdate(update_players);
    }
    else if (!node.firstChildElement("daytime").isNull())
    {
        emit dayTime(node.firstChildElement("daytime").attribute("N", "0").toInt());
    }
    else if (!node.firstChildElement("nighttime").isNull())
    {
        emit nightTime();
    }
    else if (!node.firstChildElement("voting").isNull())
    {
        QDomElement votingEl = node.firstChildElement("voting");

        QString votingFor = votingEl.attribute("for");
        QStringList targets;

        for (int t = 0; t < votingEl.childNodes().length(); t++)
        {
            targets.append(votingEl.childNodes().at(t).toElement().tagName());
        }

        emit startVote(Vote(votingFor, targets));
    }
    else if (!node.firstChildElement("endvoting").isNull())
    {
        QDomElement votingEl = node.firstChildElement("endvoting");

        QString votingFor = votingEl.attribute("for", "");

        if (!votingEl.firstChildElement("name").isNull())
        {
            QString result = votingEl.attribute("result", "");
            QString name = votingEl.firstChildElement("name").text();

            emit endVote(EndVote(votingFor, result, name));
        }
        else
        {
            emit endVote(EndVote(votingFor, "", ""));
        }
    }
}

QDomElement XmlProtocol::makeElement( QDomDocument& domDoc,
                                      const QString strName,
                                      const QString strAttr,
                                      const QString strText,
                                      const QString strAttrText) {
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
