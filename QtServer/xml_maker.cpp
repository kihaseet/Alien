#include "xml_maker.h"

xml_maker::xml_maker()
{

}



void xml_maker::newAnalise(int _name,const QString input){

    if(input!="New connection")
    {
        QStringList list = input.split("\n\n");
        foreach (QString m, list) {
            QDomDocument domDoc;

            //qDebug() <<"[XMLmaker:input]" <<input;
            if(domDoc.setContent(m))
            {
                QDomElement domElement= domDoc.documentElement();

                TurnObject turn = traverseNode(domElement);
                ROLE r;
                switch (turn.type) {
                case TT_NOTHING:
                    break;
                case TT_REGNAME:
                    emit sigRegisterCreate(RegisterObject(_name,TT_REGNAME,turn.targets.first()));
                    break;
                case TT_REGROLE:
                    r = RegisterObject::RoleDescr.value(turn.targets.first(), RT_UNKNOWN);
                    if (r != RT_UNKNOWN) {
                        emit sigRegisterCreate(RegisterObject(_name,TT_REGROLE,RegisterObject::RoleDescr.value(turn.targets.first())));
                    }
                    break;
                default:
                    emit sigTurnCreate(_name,turn);
                    break;
                }

            }
        }
        //qDebug()  <<"[XMLmaker:to game]"<< _xml.what << _xml.whom << _xml.how << _xml.rotation;
    }
}

TurnObject xml_maker::traverseNode(const QDomNode& node)
{
    TurnObject _xml;
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "regname") {
                    _xml.type = TT_REGNAME;
                    _xml.targets.append(domElement.text());
                    // _xml.how=domElement.attribute("avatar","");
                } else if (domElement.tagName() == "regrole" ){
                    _xml.type = TT_REGROLE;
                    _xml.targets.append(domElement.text());
                }

                else if(domElement.tagName() == "vote") {
                    _xml.type = TT_VOTE;
                    _xml.targets.append(domElement.text());
                    //qDebug()  << domElement.tagName() << domElement.text();
                }
                else if(domElement.tagName() == "unvote") {
                    _xml.type = TT_UNVOTE;
                    _xml.targets.append(domElement.text());
                }

                else if(domElement.tagName() == "attack")
                {
                    _xml.type = TT_ATTACK;
                    _xml.targets.append(domElement.text());
                }
                else if(domElement.tagName() == "infect")
                {
                    _xml.type = TT_INFECT;
                    _xml.targets.append(domElement.text());
                }
                else if(domElement.tagName() == "wait")
                {
                    _xml.type = TT_SKIP;
                }
                else if(domElement.tagName() == "up")
                {
                    _xml.type = TT_UP;
                }
                else if(domElement.tagName() == "down")
                {
                    _xml.type = TT_DOWN;
                }
                else if(domElement.tagName() == "use")
                {
                    if(domElement.attribute("item","") != "")
                    {
                        _xml.type = TT_USE_ITEM;
                        _xml.item = TurnObject::ItemDescr.value(domElement.attribute("item",""),IT_UNKNOW);
                    }
                    else if(domElement.attribute("ult","") != "")
                    {
                        _xml.type = TT_ULT_ITEM;
                        _xml.item = TurnObject::ItemDescr.value(domElement.attribute("ult",""),IT_UNKNOW);

                    }
                    else if(domElement.attribute("badge","") != "")
                    {
                        _xml.type = TT_USE_BADGE;
                        _xml.targets.append(domElement.text());
                        _xml.item = TurnObject::ItemDescr.value(domElement.attribute("badge",""),IT_UNKNOW);
                    }
                    else
                    {
                        _xml.type = TT_NOTHING;
                        continue;
                    }
                    switch (_xml.item) {
                    case IT_ROTATION:
                        _xml.targets = makeRotation(domNode);
                        break;
                    case IT_UNKNOW:
                        _xml.type = TT_NOTHING;
                        break;
                    default:
                        _xml.targets.append(domElement.text());
                        break;
                    }
                }
                else
                    _xml.type = TT_NOTHING;
            }
        }
        domNode = domNode.nextSibling();
    }
    return _xml;
}

QQueue<QString> xml_maker::makeRotation(const QDomNode& node){
    QQueue<QString> rotation;
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                rotation.enqueue(domElement.tagName());
            }
        }
        domNode = domNode.nextSibling();
    }
    return rotation;
}

/*==================================================*/




void xml_maker::slotSendVoteList(QList<VoteObject*> votelist)
{

    QDomDocument doc("vote");
    QDomElement domVote = doc.createElement("votelist");
    doc.appendChild(domVote);
    foreach (VoteObject* vote, votelist) {
        if(vote->status == 1)
        {
            QDomElement domVotes = makeElement(doc,"vote","name",vote->whom,vote->who);
            domVote.appendChild(domVotes);
        }
    }
    emit sigSendToAll(doc.toString());
}

void xml_maker::slotSendStat(TurnObject turn)
{
    QDomDocument doc("stat");
    QDomElement domStat = doc.createElement("stat");
    doc.appendChild(domStat);

    QDomElement domEv;

    switch (turn.type) {
    case TT_GETITEM:
        domEv = doc.createElement("additem");
        domEv.setAttribute("item",QString::number((int)turn.item));
        domEv.setAttribute("power",turn.targets.first().toInt());
        break;
    case TT_DELITEM:
        domEv = doc.createElement("delitem");
        domEv.setAttribute("item",QString::number((int)turn.item));
        break;
    case TT_CORRECT:
        domEv = doc.createElement("useditem");
        domEv.setAttribute("item",QString::number((int)turn.item));
        break;
    case TT_ATTACK:
    case TT_INFECT:
        domEv = doc.createElement("useaction");
        domEv.setAttribute("action",TurnObject::TurnDescr.key(turn.type));
        break;
    case TT_CHARGERED:
        domEv = doc.createElement("chargeitem");
        domEv.setAttribute("item",TurnObject::ItemDescr.key(turn.item));
        break;
    case TT_NEEDROTATION:
        domEv = doc.createElement("needrotation");
        while (!turn.targets.isEmpty()) {
            domEv.appendChild(makeElement(doc,turn.targets.dequeue(),"","",""));
        }
        break;
    case TT_HARDRESOLVE:
        domEv = doc.createElement("hardresolve");
        while (!turn.targets.isEmpty()) {
            domEv.appendChild(makeElement(doc,turn.targets.dequeue(),"","",""));
        }
        break;
    case TT_ALIEN:
        domEv = doc.createElement("alien");
        break;
    case TT_HP:
        domEv = doc.createElement("HP");
        domEv.setAttribute("size",turn.targets.first().toInt());
        break;
    default:
        break;
    }
    domStat.appendChild(domEv);
    emit sigSendToClient(turn.wh->SocketId,doc.toString());
}

void xml_maker::slotSendTurn(TurnObject turn)
{
    QDomDocument doc("change");

    QDomElement domChanges = doc.createElement("change");
    doc.appendChild(domChanges);

    QDomElement domEv = doc.createElement("event");
    domEv.setAttribute("name",turn.wh->name);
    domChanges.appendChild(domEv);

    switch (turn.type) {
    case TT_USE_ITEM:
        domEv.setAttribute("useitem",TurnObject::ItemDescr.key(turn.item));
        foreach (QString name, turn.targets) {
            domEv.appendChild(doc.createElement(name));
        }
        break;
    case TT_USE_BADGE:
        domEv.setAttribute("usebadge",TurnObject::ItemDescr.key(turn.item));
        if(!turn.targets.isEmpty())
            domEv.appendChild(doc.createElement(turn.targets.first()));
        break;
    case TT_ULT_ITEM:
        domEv.setAttribute("useult",TurnObject::ItemDescr.key(turn.item));
        foreach (QString name, turn.targets) {
            domEv.appendChild(doc.createElement(name));
        }
        break;
    case TT_UP:
        domEv.setAttribute("status","up");
        break;
    case TT_DOWN:
        domEv.setAttribute("status","down");
        break;
    case TT_DIED:
        domEv.setAttribute("status","died");
        break;
    case TT_DUTY:
        domEv.setAttribute("status","duty");
        break;
    case TT_GETROLE:
        domEv.setAttribute("getrole",turn.targets.first());
        break;
    case TT_DELROLE:
        domEv.setAttribute("delrole",turn.targets.first());
        break;
    case TT_VOTE:
        domEv.setAttribute("voting","up");
        domEv.appendChild(doc.createElement(turn.targets.first()));
        break;
    case TT_UNVOTE:
        domEv.setAttribute("voting","down");
        domEv.appendChild(doc.createElement(turn.targets.first()));
        break;
    default:
        break;
    }
    emit sigSendToAll(doc.toString());
}

void xml_maker::slotSendMess(player* who, QString mess)
{
    QDomDocument doc("change");

    QDomElement domChanges = doc.createElement("change");
    doc.appendChild(domChanges);

    domChanges.appendChild(makeElement(doc,"playermess","",mess,""));

    emit sigSendToClient(who->SocketId,doc.toString());
}

void xml_maker::slotStartGame(QList<player*>playerlist)
{
    QDomDocument doc("init");

    QDomElement domElement = doc.createElement("init");
    doc.appendChild(domElement);

    domElement.appendChild(doc.createElement("startgame"));

    QDomElement domElementList = doc.createElement("list");
    domElement.appendChild(domElementList);

    foreach (player* corpse, playerlist) {
        QDomElement body = makeElement(doc,corpse->name,"status","",QString::number(corpse->healthy+1));
        {
            foreach (ROLE role, corpse->rolelist) {
                body.appendChild(doc.createElement(RegisterObject::RoleDescr.key(role)));
            }
            body.setAttribute("online",1);
            body.setAttribute("onduty",0);
            body.setAttribute("avatar",0);

            domElementList.appendChild(body);
        }
    }
    emit sigSendToAll(doc.toString());
}

void xml_maker::slotStartPhase(int dayNo, bool isDay)
{
    QDomDocument doc("init");

    QDomElement domElement = doc.createElement("init");
    doc.appendChild(domElement);

    if(isDay)
        domElement.appendChild(
                    makeElement(doc,"daytime","N","",QString::number(dayNo)));
    else
        domElement.appendChild(
                    makeElement(doc,"nighttime","N","",QString::number(dayNo)));
    emit sigSendToAll(doc.toString());
}

void xml_maker::slotStartVoting(ROLE targets,QList<QString>list)
{
    QDomDocument doc("init");

    QDomElement domElement = doc.createElement("init");
    doc.appendChild(domElement);
    QDomElement domVoting = doc.createElement("voting");
    domElement.appendChild(domVoting);
    QString tt = RegisterObject::RoleDescr.key(targets);
    domVoting.setAttribute("for",RegisterObject::RoleDescr.key(targets));

    foreach (QString body, list) {
        domVoting.appendChild(makeElement(doc,body,"vote","","0"));
    }
    emit sigSendToAll(doc.toString());
}

void xml_maker::slotEndVoting(ROLE targets,QString name,QString result = QString())
{
    QDomDocument doc("init");

    QDomElement domElement = doc.createElement("init");
    doc.appendChild(domElement);

    QDomElement domEl = doc.createElement("endvoting");
    domEl.setAttribute("for",RegisterObject::RoleDescr.key(targets));
    domElement.appendChild(domEl);

    if(name != "")
    {
        domEl.appendChild(makeElement(doc,"name","",name,""));
        if(targets == RT_ALIEN)
        {
            domEl.setAttribute("result",result);
        }
    }
    emit sigSendToAll(doc.toString());
}


void xml_maker::slotNameCorrect(int tempname, bool isCorrect) {
    QDomDocument doc("select");

    QDomElement domElement = doc.createElement("select");
    doc.appendChild(domElement);

    if(isCorrect)
        domElement.appendChild(doc.createElement("namecorrect"));
    else
        domElement.appendChild(doc.createElement("nonamecorrect"));
    emit sigSendToClient(tempname,doc.toString());
}



void xml_maker::slotRoleCorrect(int _name, bool isCorrect) {
    QDomDocument doc("select");

    QDomElement domElement = doc.createElement("select");
    doc.appendChild(domElement);

    if(isCorrect)
        domElement.appendChild(doc.createElement("rolecorrect"));
    else
        domElement.appendChild(doc.createElement("norolecorrect"));

    emit sigSendToClient(_name,doc.toString());
}


void xml_maker::slotUpdateRoleList(QList <player*> NameRolelist){
    QDomDocument doc("select");
    QDomElement domEl = doc.createElement("select");
    doc.appendChild(domEl);
    QDomElement domElement=doc.createElement("list");
    domEl.appendChild(domElement);
    foreach (player* jt, NameRolelist) {
        QDomElement domP=doc.createElement(jt->name);
        domElement.appendChild(domP);
        if(!jt->rolelist.isEmpty())
            domP.appendChild(makeElement(doc,"role","",RegisterObject::RoleDescr.key(jt->rolelist.first()),""));
        else
            domP.appendChild(makeElement(doc,"role","","none",""));
    }
    emit sigSendToAll(doc.toString());
}


QDomElement xml_maker::makeElement( QDomDocument& domDoc,
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

