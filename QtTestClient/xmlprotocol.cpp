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

    qDebug() << "SEND XML: ******"
             << endl
             << doc.toString()
             << "****************";
    connection->sendData(doc.toString());
}

void XmlProtocol::sendVote(QString name, bool unvote)
{
    QDomDocument doc("voting");
    QDomElement domElement = doc.createElement("voting");
    doc.appendChild(domElement);
    domElement.appendChild(makeElement(doc, (unvote ? "unvote" : "vote"), "", name, ""));
    qDebug() << "SEND XML: ******"
             << endl
             << doc.toString()
             << "****************";
    connection->sendData(doc.toString());
}

void XmlProtocol::GetData(QString data)
{
    qDebug() << "XML DATA: " << data;
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
            else if(domElement.tagName() == "votelist")
            {
                vote(domElement);
            }
            else if(domElement.tagName() == "init")
            {
                init(domElement);
            }
        }
    }
}

void XmlProtocol::select(QDomElement node){

    onSelectInfo info;
    SELECT_TYPE type;

    node = node.firstChildElement();

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
            type = SRT_PLAYERLIST;
            QDomElement list = node.firstChildElement();
            QMap <QString,QString> players;
            while(!list.isNull()){
                players.insert(list.tagName(), list.text());
                list = list.nextSiblingElement();
            }
            info.players = players;
        }

        info.type = type;

        emit onSelect(info);
        node = node.nextSiblingElement();
    }
}

void XmlProtocol::change(QDomElement node)
{
    onChangeInfo info;

    QDomElement stat = node.firstChildElement("stat");

    if (!stat.isNull())
    {
        info.updated_stats.health = stat.firstChildElement("HP").text().toInt();
        info.updated_stats.alien = !stat.firstChildElement("alien").isNull();
        info.updated_stats.infected = !stat.firstChildElement("invasion").isNull();
        info.updated_stats.status = PS_UNKNOWS;
        QDomNodeList roles = stat.elementsByTagName("role");

        for (int i = 0; i < roles.length(); i++)
        {
            QDomNode role = roles.at(i);
            if (role.toElement().attribute("get") != "")
            {
                info.updated_stats.role.append(role.toElement().attribute("get"));
            }
            else if (role.toElement().attribute("del") != "")
            {
                info.updated_stats.role.removeOne(role.toElement().attribute("get"));
            }
        }

        info.updated_stats.dead = !stat.firstChildElement("dying").isNull();
    }

    QDomElement actions = node.firstChildElement("actions");

    if (!actions.isNull())
    {
        for (int i = 0; i < actions.childNodes().length(); i++)
        {
            QDomElement act_el = actions.childNodes().at(i).toElement();
            if (act_el.tagName() == "attack")
            {
                info.avaible_actions.append(TurnObject(TT_ATTACK, QStringList(), ""));
            }
            else if (act_el.tagName() == "wait")
            {
                info.avaible_actions.append(TurnObject(TT_SKIP, QStringList(), ""));
            }
            else if (act_el.tagName() == "down")
            {
                info.avaible_actions.append(TurnObject(TT_DOWN, QStringList(), ""));
            }
            else if (act_el.tagName() == "up")
            {
                info.avaible_actions.append(TurnObject(TT_UP, QStringList(), ""));
            }
            else if (act_el.tagName() == "infect")
            {
                info.avaible_actions.append(TurnObject(TT_INFECT, QStringList(), ""));
            }
            else if (act_el.tagName() == "use")
            {
                QStringList targets;

                for (int i = 0; i < act_el.childNodes().length(); i++)
                {
                    QDomNode target = act_el.childNodes().at(i);
                    targets.append(target.toElement().tagName());
                }

                if (act_el.attribute("item") != "")
                {

                    info.avaible_actions.append(TurnObject(TT_USE_ITEM, targets, act_el.attribute("item")));
                }
                else if (act_el.attribute("ult") != "")
                {
                    info.avaible_actions.append(TurnObject(TT_ULT_ITEM, targets, act_el.attribute("ult")));
                }
            }
        }
    }

    QDomElement events = node.firstChildElement("events");

    if (!events.isNull())
    {
        // GENERATE PLAYERS INFO

        {
            for (int i = 0; i < events.firstChildElement("list").childNodes().length(); i++)
            {
                QDomNode player = events.firstChildElement("list").childNodes().at(i);
                info.players_info[player.toElement().tagName()].name = player.toElement().tagName();
                info.players_info[player.toElement().tagName()].dead = false;
            }

            for (int i = 0; i < events.firstChildElement("allrole").childNodes().length(); i++)
            {
                QDomNode role = events.firstChildElement("allrole").childNodes().at(i);
                info.players_info[role.toElement().text()].role.append(role.toElement().tagName());
            }
        }

        {
            EventInfo e_down;
            e_down.type = ET_DOWNED;

            for (int i = 0; i < events.firstChildElement("down").childNodes().length(); i++)
            {
                QDomNode downed_player = events.firstChildElement("down").childNodes().at(i);
                e_down.message.append(downed_player.toElement().tagName());
                info.players_info[downed_player.toElement().tagName()].status == PS_DOWN;
            }

            info.events.append(e_down);
        }

        {
            EventInfo e_up;
            e_up.type = ET_UPPED;

            for (int i = 0; i < events.firstChildElement("up").childNodes().length(); i++)
            {
                QDomNode upped_player = events.firstChildElement("up").childNodes().at(i);
                e_up.message.append(upped_player.toElement().tagName());
                info.players_info[upped_player.toElement().tagName()].status == PS_UP;
            }

            info.events.append(e_up);
        }

        for (int i = 0; i < events.elementsByTagName("use").length(); i++)
        {
            QDomNode item = events.elementsByTagName("use").at(i);
            EventInfo e_use;
            e_use.type = ET_USED_ITEM;
            e_use.message.append(item.toElement().attribute("item") + " -> " + item.toElement().text());
            info.events.append(e_use);
        }

        for (int i = 0; i < events.elementsByTagName("ult").length(); i++)
        {
            QDomNode item = events.elementsByTagName("ult").at(i);
            EventInfo e_ult;
            e_ult.type = ET_ULT_ITEM;
            e_ult.message.append(item.toElement().attribute("item") + " -> " + item.toElement().text());
            info.events.append(e_ult);
        }

        {
            EventInfo e_died;
            e_died.type = ET_DIED;

            for (int i = 0; i < events.firstChildElement("died").childNodes().length(); i++)
            {
                QDomNode died_player = events.firstChildElement("died").childNodes().at(i);
                e_died.message.append(died_player.toElement().tagName());
                info.players_info[died_player.toElement().tagName()].status == PS_DEAD;
                info.players_info[died_player.toElement().tagName()].dead = true;
            }

            info.events.append(e_died);
        }

        for (int i = 0; i < events.elementsByTagName("role").length(); i++)
        {
            QDomNode item = events.elementsByTagName("role").at(i);
            EventInfo e_role;

            if (item.toElement().attribute("get") != "")
            {
                e_role.type = ET_SETTED_ROLE;
                e_role.message.append(item.toElement().attribute("get"));
            }
            else if (item.toElement().attribute("del") != "")
            {
                e_role.type = ET_SETTED_ROLE;
                e_role.message.append(item.toElement().attribute("del"));
            }

            e_role.message.append(item.toElement().text());
            info.events.append(e_role);
        }

        {
            QDomElement duty = events.firstChildElement("duty");
            EventInfo e_duty;
            e_duty.type = ET_DUTIED;
            e_duty.message.append(duty.text());
            info.events.append(e_duty);
        }

        for (int i = 0; i < events.elementsByTagName("playmess").length(); i++)
        {
            QDomNode item = events.elementsByTagName("playmess").at(i);
            EventInfo e_playmess;
            e_playmess.type = ET_MESSAGE;
            e_playmess.message.append(item.toElement().text());
            info.events.append(e_playmess);
        }
    }

    emit onChange(info);
}

void XmlProtocol::init(QDomElement node)
{
    qDebug() << "XMLProtocol: Init";
    if (!node.firstChildElement("daytime").isNull())
    {
        qDebug() << "XMLProtocol: daytime";
        onInitInfo info;
        info.type = IT_DAYTIME;
        change(node.firstChildElement("changes"));
        emit onInit(info);
    }
    else if (!node.firstChildElement("nighttime").isNull())
    {
        qDebug() << "XMLProtocol: nighttime";
        onInitInfo info;
        info.type = IT_NIGHTTIME;
        change(node.firstChildElement("changes"));
        emit onInit(info);
    }
    else if (!node.firstChildElement("voting").isNull())
    {
        qDebug() << "XMLProtocol: voting";
        QDomElement e_voting = node.firstChildElement("voting");
        onInitInfo info;

        if (e_voting.attribute("for") == "alien")
        {
            info.type = IT_VOTING_FOR_ALIEN;
        }
        else
        {
            info.type = IT_VOTING_FOR_ROLE;
        }

        info.target = e_voting.attribute("for");

        for (int i = 0; i < e_voting.childNodes().length(); i++)
        {
            QDomNode player = e_voting.childNodes().at(i);
            info.data.append(player.toElement().tagName());
        }

        emit onInit(info);
    }
    else if (!node.firstChildElement("endvoting").isNull())
    {
        QDomElement e_voting = node.firstChildElement("endvoting");
        onInitInfo info;

        if (e_voting.attribute("for") == "alien")
        {
            info.type = IT_ENDVOTING_FOR_ALIEN;
            info.target = e_voting.attribute("for");
            info.data.append(e_voting.firstChildElement("name").text());
            info.data.append(e_voting.firstChildElement("result").text());
        }
        else
        {
            info.type = IT_ENDVOTING_FOR_ROLE;
            info.target = e_voting.firstChildElement("target").text();
            info.data.append(e_voting.firstChildElement("target").firstChildElement("name").text());
        }

        emit onInit(info);
    }
}

void XmlProtocol::vote(QDomElement node)
{
    onVoteInfo info;

    for (int i = 0; i < node.childNodes().length(); i++)
    {
        QDomNode vote = node.childNodes().at(i);
        info.votelist[vote.toElement().attribute("name")] = QPair<int, QString>(vote.firstChildElement("status").text().toInt(), vote.firstChildElement("target").text());
    }

    emit onVote(info);
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
