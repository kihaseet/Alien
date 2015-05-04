#include "xmlmanager.h"

xmlmaker::xmlmaker()
{
}

void xmlmaker::select(QDomElement node){
    while(!node.isNull()){
        if(node.tagName()=="namecorrect") {
            emit signal_NameCorrect();
        }
        if (node.tagName() == "rolecorrect"){
            emit signal_RoleCorrect();
        }
        if(node.tagName() == "norolecorrect"){
            emit signal_NoRoleCorrect();
        }
        if (node.tagName() == "nonamecorrect") {
            emit signal_NoNameCorrect();
        }
        if(node.tagName() == "list"){
            QDomElement list = node.firstChildElement();
            QMap <QString,QString> players;
            while(!list.isNull()){
                players.insert(list.tagName(),list.text());
                list = list.nextSiblingElement();
            }
            emit signal_playerlist(players);
        }
        if(node.tagName() == "unusedrole"){
            //            QList <QString>* unusedrole = new QList <QString>();
            //            while (token != QXmlStreamReader::EndElement && xmlDoc.name()!="unusedrole"){
            //                token = xmlDoc.readNext();
            //                if(token == QXmlStreamReader::StartElement){
            //                    QString na = xmlDoc.name().toString();
            //                    unusedrole->append(na);
            //                }
            //            }
            //            emit signal_RoleList(unusedrole);
            //            continue;
        }
        node = node.nextSiblingElement();
    }
}


void xmlmaker::new_analise(QString msg){
    QStringList list = msg.split("\n\n");
    foreach (QString m, list) {
        QDomDocument domDoc;
        if(domDoc.setContent(m)) {
            QDomElement domElement= domDoc.documentElement();
            if(domElement.tagName()=="select"){
                select(domElement.firstChildElement());
            }
        }
    }
}


//=============================================================================
void xmlmaker::slot_sendNewName(QString what,QString name){
    QDomDocument doc("selecting");
    QDomElement domElement = doc.createElement("selecting");
    doc.appendChild(domElement);
    domElement.appendChild(makeElement(doc,what,"",name,""));
    emit send2serv(doc.toString());
}

QDomElement xmlmaker::makeElement( QDomDocument& domDoc,
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

