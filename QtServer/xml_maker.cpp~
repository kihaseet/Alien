#include "xml_maker.h"

xml_maker::xml_maker()
{

}



void xml_maker::new_analise(const QString _name,const QString input){

    if(input!="New connection") {
        QDomDocument domDoc;
        xml_msg _xml;

        if(domDoc.setContent(&input)) {
            QDomElement domElement= domDoc.documentElement();

            _xml=traverseNode(domElement,_xml,domDoc.doctype().name());
        }
        if(_xml.what=="regname"){
            emit newname(_name,_xml.whom);
        }
        qDebug()  << _xml.what << _xml.whom << _xml.how << _xml.rotation;
    }
}



xml_msg xml_maker::traverseNode(const QDomNode& node,xml_msg _xml, QString mod)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                //qDebug()  << mod;
                if (mod=="selecting"){

                    if((domElement.tagName() == "regname") || (domElement.tagName() == "regrole" )) {
                        _xml.what=domElement.tagName();
                        _xml.whom=domElement.text();
                        //qDebug()  << domElement.tagName() << domElement.text();
                    }
                }
                if (mod=="voting"){
                    if(domElement.tagName() == "vote") {
                        _xml.what = domElement.tagName();
                        _xml.whom = domElement.text();
                        //qDebug()  << domElement.tagName() << domElement.text();
                    }
                }
                if (mod == "changing") {
                    if((domElement.tagName() == "attack") || (domElement.tagName() == "infect")) {
                        _xml.what = domElement.tagName();
                        _xml.whom = domElement.text();
                        //qDebug()  << domElement.tagName() << domElement.text();
                    }
                    if((domElement.tagName() == "wait")||(domElement.tagName()=="up")||(domElement.tagName()=="down")){
                        _xml.what=domElement.tagName();
                        //qDebug()  << domElement.tagName();
                    }
                    if(domElement.tagName() == "use"){
                        if(domElement.attribute("item","")!=""){
                            _xml.what="useitem";
                            _xml.how=domElement.attribute("item","");
                            // qDebug()  << domElement.tagName() << domElement.attribute("item","");
                            if(_xml.how=="Rotation"){
                                _xml.rotation=makeRotation(domNode);
                            }
                            else _xml.whom=domElement.text();

                        }
                        if(domElement.attribute("ult","")!=""){
                            _xml.what="useult";
                            _xml.whom=domElement.text();
                            _xml.how=domElement.attribute("ult","");
                            //qDebug()  << domElement.tagName() << domElement.attribute("ult","") << domElement.text();
                        }
                    }
                }
            }
        }
        traverseNode(domNode,_xml,mod);
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

void xml_maker::nightmare(QQueue<ingame_event> _que,QMap <QString,player> playerlist, QMap <QString,item> itemlist){
    QMap<QString, player>::iterator it = playerlist.begin();
    for (;it != playerlist.end(); ++it) {/*для всех игроков*/
        QDomDocument doc("init");

        QDomElement domElement = doc.createElement("init");
        doc.appendChild(domElement);

        domElement.appendChild(doc.createElement("daytime"));

        QDomElement domChanges = doc.createElement("changes");
        domElement.appendChild(domChanges);

        domChanges.appendChild(doc.createElement(this->append_actions(doc,it.value(),playerlist,itemlist,1)));

        QDomElement domStat = doc.createElement("stat");
        domChanges.appendChild(domStat);

        if(it.value().HP<=0)
            domStat.appendChild(makeElement(doc,"dying","","",""));
        else {
            domStat.appendChild(makeElement(doc,"HP","",QString::number(it.value().HP),""));
        }

        QDomElement domEvents = doc.createElement("events");
        domChanges.appendChild(domEvents);

        QDomElement list=doc.createElement("list");
        domEvents.appendChild(list);

        QDomElement died=doc.createElement("died");
        domEvents.appendChild(died);

        QDomElement allrole=doc.createElement("allrole");
        domEvents.appendChild(allrole);

        QDomElement up=doc.createElement("up");
        domEvents.appendChild(up);

        QDomElement down=doc.createElement("down");
        domEvents.appendChild(down);

        QMap<QString, player>::iterator jt = playerlist.begin();
        for (;jt != playerlist.end(); ++jt){
            if(jt.value().HP>0){
                list.appendChild(makeElement(doc,jt.key(),"","",""));

                if(!jt.value().rolelist.contains("Passenger")){
                    QList<QString>::iterator kt = jt.value().rolelist.begin();
                    while (kt != jt.value().rolelist.end()) {
                        allrole.appendChild(makeElement(doc,*kt,"",jt.key(),""));
                        ++kt;
                    }
                }

            }
            if(jt.value().HP<=0){
                died.appendChild(makeElement(doc,jt.key(),"","",""));
                if(!jt.value().rolelist.contains("Passenger")){
                    QList<QString>::iterator kt = jt.value().rolelist.begin();
                    while (kt != jt.value().rolelist.end()) {
                        allrole.appendChild(makeElement(doc,*kt,"","",""));
                        domEvents.appendChild(makeElement(doc,"role","del",jt.key(),*kt));
                        ++kt;
                    }
                }
            }
        }
        QQueue<ingame_event>_queue = _que;/*обработка событий*/
        ingame_event _eve;
        while(!_queue.isEmpty()){
            _eve=_queue.dequeue();
            if(_eve.what=="up"){/*если встал с ванны*/
                up.appendChild(makeElement(doc,_eve.who.name,"","",""));
                if(it.value().name==_eve.who.name){
                    domEvents.appendChild(makeElement(doc,"playmess","","Вы встали из биованны",""));
                }
            }
            if(_eve.what=="down"){/*если лег в ванну*/
                down.appendChild(makeElement(doc,_eve.who.name,"","",""));
                if(it.value().name==_eve.who.name){
                    domEvents.appendChild(makeElement(doc,"playmess","","Вы очнулись в биованне",""));
                }
            }

            if((_eve.what=="useitem")
                    &&(_eve.useit.handle=="Mop")
                    &&(it.value().name==_eve.who.name)) {
                domEvents.appendChild(makeElement(doc,"playmess","","Дежурство состоялось",""));
            }
            if((it.value().itemlist.contains("Mop"))
                    &&(_eve.what=="useult")
                    &&(_eve.useit.handle=="Mop")
                    &&(it.value().name!=_eve.who.name)) {
                domEvents.appendChild(makeElement(doc,"playmess","","Дежурство не состоялось",""));
            }
            if(_eve.what=="useitem"){
                if((_eve.useit.handle=="Blaster")
                        &&(it.value().name==_eve.who.name)) {
                    domEvents.appendChild(makeElement(doc,"playmess","","Вы кого-то подстрелили!",""));
                    domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Blaster"));
                }
                if((_eve.useit.handle=="Scanner")
                        &&(it.value().name==_eve.who.name)) {
                    QString _scan;
                    if(_eve.whom.status==0) _scan="человек";
                    if(_eve.whom.status==1) _scan="заражен";
                    if(_eve.whom.status==2) {
                        _scan="чужой";
                        if((_eve.who.status==2)
                                &&(_eve.whom.itemlist.contains("Fetus")))
                            _scan="чужой с эмбрионом";
                    }
                    domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Scanner"));
                    domEvents.appendChild(makeElement(doc,"playmess","","Сканер показал, что "+_eve.whom.name+" - "+_scan,""));
                }
                if((_eve.useit.handle=="Injector")
                        &&(it.value().name==_eve.who.name)){
                    domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Injector"));
                }
                if((_eve.useit.handle=="Battery")
                        &&(it.value().name==_eve.who.name)){
                    domEvents.appendChild(makeElement(doc,"playmess","","Вы успешно переночевали на обшивке",""));
                    domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Battery"));
                }

            }
            if(_eve.what=="ingect"){
                if(_eve.whom.status!=2) {
                    if(_eve.whom.name==it.key()){
                        domStat.appendChild(makeElement(doc,"invasion","","",""));
                        domStat.appendChild(makeElement(doc,"item","get",QString::number(1),"Fetus"));
                    }

                }
                if(_eve.who.name==it.key()){
                    domStat.appendChild(makeElement(doc,"item","del","","Fetus"));
                }
            }
            if(_eve.what="useult"){
                if(((_eve.useit.handle=="Blaster")
                    ||(_eve.useit.handle=="Injector")
                    ||(_eve.useit.handle=="Battery")
                    ||(_eve.useit.handle=="Scanner"))
                        &&(_eve.who.rolelist.contains("Captain"))) {
                    QMap<QString, player>::iterator tt = playerlist.begin();
                    for (;tt != playerlist.end(); ++tt){
                        if((tt.value().itemlist.contains(_eve.useit.handle))
                                &&(it.key()==tt.key())){
                            domEvents.appendChild(makeElement(doc,"playmess","","Вы обнаружили, что один из ваших инструментов разряжен!",""));
                            domStat.appendChild(makeElement(doc,"item","get",QString::number(2),eve.useit.handle));
                        }
                    }
                    if(it.key()==_eve.who.name){
                        if(_eve.useit.handle=="Blaster"){
                            domEvents.appendChild(makeElement(doc,"playmess","","Вы кого-то подстрелили!",""));
                        }
                        if((_eve.useit.handle=="Scanner")
                                &&(it.value().name==_eve.who.name)) {
                            QString _scan;
                            if(_eve.whom.status==0) _scan="человек";
                            if(_eve.whom.status==1) _scan="заражен";
                            if(_eve.whom.status==2) {
                                _scan="чужой";
                                if((_eve.who.status==2)
                                        &&(_eve.whom.itemlist.contains("Fetus")))
                                    _scan="чужой с эмбрионом";
                            }
                            domEvents.appendChild(makeElement(doc,"playmess","","Сканер показал, что "+_eve.whom.name+" - "+_scan,""));
                        }
                        if((_eve.useit.handle=="Battery")
                                &&(it.value().name==_eve.who.name)){
                            domEvents.appendChild(makeElement(doc,"playmess","","Вы успешно переночевали на обшивке",""));
                        }
                        domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Badge"));
                    }
                }else
                {
                    if((_eve.useit.handle=="Blaster")
                            &&(it.value().name==_eve.who.name)) {
                        domStat.appendChild(makeElement(doc,"item","del","","Blaster"));
                        domStat.appendChild(makeElement(doc,"rol","del","","Gunmen"));
                        if(_eve.who.rolelist.contains("Passenger")){
                            domEvents.appendChild(makeElement(doc,"playmess","","Вы стали простым пассажиром",""));
                        }
                    }
                    if((_eve.useit.handle=="Injector")
                            &&(it.value().name==_eve.who.name)) {
                        domStat.appendChild(makeElement(doc,"item","del","","Injector"));
                        domStat.appendChild(makeElement(doc,"rol","del","","Doctor"));
                        if(_eve.who.rolelist.contains("Passenger")){
                            domEvents.appendChild(makeElement(doc,"playmess","","Вы стали простым пассажиром",""));
                        }
                    }
                    if((_eve.useit.handle=="Scanner")
                            &&(it.value().name==_eve.who.name)) {
                        domStat.appendChild(makeElement(doc,"item","del","","Scanner"));
                        domStat.appendChild(makeElement(doc,"rol","del","","Scientist"));
                        if(_eve.who.rolelist.contains("Passenger")){
                            domEvents.appendChild(makeElement(doc,"playmess","","Вы стали простым пассажиром",""));
                        }
                    }
                    if((_eve.useit.handle=="Battery")
                            &&(it.value().name==_eve.who.name)) {
                        domStat.appendChild(makeElement(doc,"item","del","","Battery"));
                        domStat.appendChild(makeElement(doc,"rol","del","","Engineer"));
                        if(_eve.who.rolelist.contains("Passenger")){
                            domEvents.appendChild(makeElement(doc,"playmess","","Вы стали простым пассажиром",""));
                        }
                    }
                }
            }
        }
    }

}

void xml_maker::end_of_day(QMap <QString,player> playerlist,QMap <QString,item> itemlist){
    QMap<QString, player>::iterator it = playerlist.begin();
    for (;it != playerlist.end(); ++it) {/*для всех игроков*/
        QDomDocument doc("init");

        QDomElement domElement = doc.createElement("init");
        doc.appendChild(domElement);

        domElement.appendChild(doc.createElement("nighttime"));

        QDomElement domChanges = doc.createElement("changes");
        domElement.appendChild(domChanges);

        domChanges.appendChild(doc.createElement(this->append_actions(doc,it.value(),playerlist,itemlist,0)));

        QDomElement domStat = doc.createElement("stat");
        domChanges.appendChild(domStat);

        if(it.value().HP<=0)
            domStat.appendChild(makeElement(doc,"dying","","",""));
        else {
            domStat.appendChild(makeElement(doc,"HP","",QString::number(it.value().HP),""));
        }

        QDomElement domEvents = doc.createElement("events");
        domChanges.appendChild(domEvents);

        QDomElement list=doc.createElement("list");
        domEvents.appendChild(list);

        QDomElement died=doc.createElement("died");
        domEvents.appendChild(died);

        QDomElement allrole=doc.createElement("allrole");
        domEvents.appendChild(allrole);

        QMap<QString, player>::iterator jt = playerlist.begin();
        for (;jt != playerlist.end(); ++jt){
            if(jt.value().HP>0){
                list.appendChild(makeElement(doc,jt.key(),"","",""));

                if(!jt.value().rolelist.contains("Passenger")){
                    QList<QString>::iterator kt = jt.value().rolelist.begin();
                    while (kt != jt.value().rolelist.end()) {
                        allrole.appendChild(makeElement(doc,*kt,"",jt.key(),""));
                        ++kt;
                    }
                }

            }
            if(jt.value().HP<=0){
                died.appendChild(makeElement(doc,jt.key(),"","",""));
                if(!jt.value().rolelist.contains("Passenger")){
                    QList<QString>::iterator kt = jt.value().rolelist.begin();
                    while (kt != jt.value().rolelist.end()) {
                        allrole.appendChild(makeElement(doc,*kt,"","",""));
                        ++kt;
                    }
                }
            }
        }
    }
}

QDomElement xml_maker::append_actions(QDomDocument& domDoc,player _player,
                                      QMap <QString,player> _playerlist, QMap <QString,item> _itemlist,
                                      int is_night) /*указатель на DOM,текущий игрок,список игроков,список вещей,ночь/день*/
{
    QDomElement domActions = domDoc.createElement("actions");

    QList<QString>::iterator jt = _player.actionlist.begin();

    while (jt != _player.actionlist.end()) {
        domActions.appendChild(doc.createElement(*jt));
        ++jt;
    }
    if(is_night==0){
        /*ночные применения предметов*/
        if(_player.use_night_item==0){

            QMap<QString, item>::iterator jt = _player.itemlist.begin();
            for (;jt != _player.itemlist.end(); ++jt) {

                if(((jt.key()=="Blaster") || (jt.key()=="Injector")
                    || (jt.key()=="Battery") || (jt.key()=="Scanner")
                    || (jt.key()=="Mop"))
                        && (jt.value().power==0)) {

                    QDomElement domItem=domDoc.createElement("use");

                    QDomAttr domAttr = domDoc.createAttribute("item");
                    domAttr.setValue(jt.key());
                    domItem.setAttributeNode(domAttr);

                    domActions.appendChild(domItem);

                    if(jt.key()!="Battery"){
                        QMap<QString, player>::iterator it = _playerlist.begin();
                        for (;it != _playerlist.end(); ++it) {
                            domItem.appendChild(domDoc.createElement(it.key()));
                        }
                    }
                }
                if(_player.status==2 && jt.key()=="Fetus"){
                    QDomElement domItem=domDoc.createElement("use");

                    QDomAttr domAttr = domDoc.createAttribute("item");
                    domAttr.setValue(jt.key());
                    domItem.setAttributeNode(domAttr);
                    domActions.appendChild(domItem);
                }
            }

            jt = _player.itemlist.begin();
            for (;jt != _player.itemlist.end(); ++jt) {

                if(((jt.key()=="Blaster")&&(jt.value().power==0) )|| ((jt.key()=="Injector")&&(jt.value().power==0))
                        || (jt.key()=="Battery") || (jt.key()=="Scanner")
                        || (jt.key()=="Badge")) {

                    QDomElement domItem=domDoc.createElement("use");

                    QDomAttr domAttr = domDoc.createAttribute("ult");
                    domAttr.setValue(jt.key());
                    domItem.setAttributeNode(domAttr);

                    domActions.appendChild(domItem);

                    if((jt.key()!="Battery")&&(jt.key()!="Badge")){
                        QMap<QString, player>::iterator it = _playerlist.begin();
                        for (;it != _playerlist.end(); ++it) {
                            domItem.appendChild(domDoc.createElement(it.key()));
                        }
                    }
                    if(jt.key()=="Battery"){
                        QMap<QString, item>::iterator kt = _itemlist.begin();
                        for (;kt != _itemlist.end(); ++kt) {
                            if(kt.value().power==-1){
                                domItem.appendChild(domDoc.createElement(kt.key()));
                            }
                        }
                    }
                    if(jt.key()=="Badge" && jt.value().power==0){
                        QMap<QString, item>::iterator kt = _itemlist.begin();
                        for (;kt != _itemlist.end(); ++kt) {
                            if(kt.key()!="Notebook"){
                                domItem.appendChild(domDoc.createElement(kt.key()));
                            }
                        }
                        domItem.appendChild(domDoc.createElement("Mop"));
                    }
                }
            }
        }
    }

    if(is_night==1){
        QString _forrepower;
        QMap<QString, item>::iterator jt = _itemlist.begin();
        for (;jt != _itemlist.end(); ++jt) {
            if((jt.key()=="Battery")&&(jt.value().power==0)&&(_itemlist.contains(jt.value().forrepower))){
                _forrepower=jt.value().forrepower;
            }
        }
        /*дневные применения предметов*/
        jt = _player.itemlist.begin();
        for (;jt != _player.itemlist.end(); ++jt) {

            if(((jt.value().power==0)||(_forrepower==jt.key()))&&((jt.key()!="Badge")||(jt.key()!="Fetus")
                                                                  ||(jt.key()!="Rotation")||(jt.key()!="Blaster"))) {

                QDomElement domItem=domDoc.createElement("use");

                QDomAttr domAttr = domDoc.createAttribute("item");
                domAttr.setValue(jt.key());
                domItem.setAttributeNode(domAttr);

                domActions.appendChild(domItem);

                if(jt.key()!="Battery"){
                    QMap<QString, player>::iterator it = _playerlist.begin();
                    for (;it != _playerlist.end(); ++it) {
                        domItem.appendChild(domDoc.createElement(it.key()));
                    } else {
                        QMap<QString, item>::iterator kt = _itemlist.begin();
                        for (;kt != _itemlist.end(); ++kt) {
                            if(kt.value().power>=0){
                                domItem.appendChild(domDoc.createElement(kt.key()));
                            }
                        }
                    }
                }
            }
            if((jt.key()=="Rotation")&&(jt.value().rotation.isEmpty())){

                DomElement domItem=domDoc.createElement("use");

                QDomAttr domAttr = domDoc.createAttribute("item");
                domAttr.setValue(jt.key());
                domItem.setAttributeNode(domAttr);
                domActions.appendChild(domItem);
            }

        }
        /*дневные ульты*/
        jt = _player.itemlist.begin();
        for (;jt != _player.itemlist.end(); ++jt) {

            if(((jt.key()=="Blaster")&&(jt.value().power==0) ) || ((jt.key()=="Injector")&&(jt.value().power==0))
                    || (jt.key()=="Battery") || (jt.key()=="Scanner")
                    || (jt.key()=="Badge") || (jt.key()=="Notebook")) {

                QDomElement domItem=domDoc.createElement("use");

                QDomAttr domAttr = domDoc.createAttribute("ult");
                domAttr.setValue(jt.key());
                domItem.setAttributeNode(domAttr);

                domActions.appendChild(domItem);

                if((jt.key()!="Battery")&&(jt.key()!="Badge")){
                    QMap<QString, player>::iterator it = _playerlist.begin();
                    for (;it != _playerlist.end(); ++it) {
                        domItem.appendChild(domDoc.createElement(it.key()));
                    }
                }
                if(jt.key()=="Battery"){
                    QMap<QString, item>::iterator kt = _itemlist.begin();
                    for (;kt != _itemlist.end(); ++kt) {
                        if(kt.value().power==-1){
                            domItem.appendChild(domDoc.createElement(kt.key()));
                        }
                    }
                }
                if(jt.key()=="Badge" && jt.value().power==0){
                    QMap<QString, item>::iterator kt = _itemlist.begin();
                    for (;kt != _itemlist.end(); ++kt) {
                        domItem.appendChild(domDoc.createElement(kt.key()));
                    }
                }
            }
        }
    }

    return domActions;
}

void xml_maker::send_to_all(ingame_event _eve,QMap <QString,player> playerlist,QMap <QString,item> itemlist){
    QMap<QString, player>::iterator it = playerlist.begin();
    for (;it != playerlist.end(); ++it) {/*для всех игроков*/
        QDomDocument doc("change");

        QDomElement domChanges = doc.createElement("change");
        doc.appendChild(domChanges);

        domChanges.appendChild(doc.createElement(this->append_actions(doc,it.value(),playerlist,itemlist,1)));

        QDomElement domStat = doc.createElement("stat");
        domChanges.appendChild(domStat);

        if(it.value().HP<=0)
            domStat.appendChild(makeElement(doc,"dying","","",""));
        else {
            domStat.appendChild(makeElement(doc,"HP","",QString::number(it.value().HP),""));
        }

        QDomElement domEvents = doc.createElement("events");
        domChanges.appendChild(domEvents);

        if(_eve.what=="up"){/*если встал с ванны*/
            up.appendChild(makeElement(doc,_eve.who.name,"","",""));
            if(it.value().name==_eve.who.name){
                domEvents.appendChild(makeElement(doc,"playmess","","Вы встали из биованны",""));
            }else domEvents.appendChild(makeElement(doc,"playmess","",_eve.who.name+" встал из биованны",""));
        }
        if(_eve.what=="down"){/*если лег в ванну*/
            down.appendChild(makeElement(doc,_eve.who.name,"","",""));
            if(it.value().name==_eve.who.name){
                domEvents.appendChild(makeElement(doc,"playmess","","Вы очнулись в биованне",""));
            } else domEvents.appendChild(makeElement(doc,"playmess","",_eve.who.name+" попал в биованну",""));
        }

        if(_eve.what=="useitem"){
            if(_eve.useit.handle=="Scanner"){
                domEvents.appendChild(makeElement(doc,"use","item",_eve.whom.name,_eve.useit.handle);
                        if(it.value().name==_eve.who.name) {
                    QString _scan;
                    if(_eve.whom.status==0) _scan="человек";
                    if(_eve.whom.status==1) _scan="заражен";
                    if(_eve.whom.status==2) {
                        _scan="чужой";
                        if((_eve.who.status==2)
                                &&(_eve.whom.itemlist.contains("Fetus")))
                            _scan="чужой с эмбрионом";
                    }
                    domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Scanner"));
                    domEvents.appendChild(makeElement(doc,"playmess","","Сканер показал, что "+_eve.whom.name+" - "+_scan,""));
                }
            }
            if(_eve.useit.handle=="Injector"){
                domEvents.appendChild(makeElement(doc,"use","item",_eve.whom.name,_eve.useit.handle);
                        if(it.value().name==_eve.who.name){
                    domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Injector"));
                }
            }

            if(_eve.useit.handle=="Notebook"){
                domEvents.appendChild(makeElement(doc,"playmess","","Юлианна отдала голос "+_eve.whom.name,""));
                domEvents.appendChild(makeElement(doc,"use","item",_eve.whom.name,_eve.useit.handle);
                        if(it.value().name==_eve.who.name){
                    domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Notebook"));
                }
            }

            if(_eve.useit.handle=="Battery"){
                domEvents.appendChild(makeElement(doc,"use","item",_eve.useit.forrepower,_eve.useit.handle);
                        if(it.value().name==_eve.who.name){
                    domEvents.appendChild(makeElement(doc,"playmess","",_eve.useit.forrepower+" можно использовать с вашей батарейкой",""));
                }
            }

        }

        if(_eve.what="useult"){
            if(((_eve.useit.handle=="Injector")
                ||(_eve.useit.handle=="Notebook")
                ||(_eve.useit.handle=="Battery")
                ||(_eve.useit.handle=="Scanner"))
                    &&(_eve.who.rolelist.contains("Captain"))) {
                QMap<QString, player>::iterator tt = playerlist.begin();
                for (;tt != playerlist.end(); ++tt){
                    if((tt.value().itemlist.contains(_eve.useit.handle))
                            &&(it.key()==tt.key())){
                        domEvents.appendChild(makeElement(doc,"playmess","","Вы обнаружили, что один из ваших инструментов разряжен!",""));
                        domStat.appendChild(makeElement(doc,"item","get",QString::number(2),eve.useit.handle));
                    }
                }
                if(it.key()==_eve.who.name){
                    if((_eve.useit.handle=="Scanner")
                            &&(it.value().name==_eve.who.name)) {
                        QString _scan;
                        if(_eve.whom.status==0) _scan="человек";
                        if(_eve.whom.status==1) _scan="заражен";
                        if(_eve.whom.status==2) {
                            _scan="чужой";
                            if((_eve.who.status==2)
                                    &&(_eve.whom.itemlist.contains("Fetus")))
                                _scan="чужой с эмбрионом";
                        }
                        domEvents.appendChild(makeElement(doc,"playmess","","Сканер показал, что "+_eve.whom.name+" - "+_scan,""));
                    }
                    if(_eve.useit.handle=="Battery"){
                        domEvents.appendChild(makeElement(doc,"ult","item",_eve.useit.forrepower,_eve.useit.handle));
                        if(it.value().name==_eve.who.name){
                            domEvents.appendChild(makeElement(doc,"playmess","",_eve.useit.forrepower+" можно использовать с батарейкой",""));
                        }
                    }
                    if(_eve.useit.handle=="Injector"){
                        domEvents.appendChild(makeElement(doc,"ult","item",_eve.whom.name,_eve.useit.handle));
                    }
                    if(_eve.useit.handle=="Notebook"){
                        domEvents.appendChild(makeElement(doc,"ult","item",_eve.whom.name,_eve.useit.handle));
                        domEvents.appendChild(makeElement(doc,"playmess","","Юлианна отдала голос "+_eve.whom.name,""));
                    }
                    domStat.appendChild(makeElement(doc,"item","get",QString::number(2),"Badge"));
                }
            } else
            {
                if((_eve.useit.handle=="Blaster")
                        &&(it.value().name==_eve.who.name)) {
                    domStat.appendChild(makeElement(doc,"item","del","","Blaster"));
                    domStat.appendChild(makeElement(doc,"rol","del","","Gunmen"));
                    if(_eve.who.rolelist.contains("Passenger")){
                        domEvents.appendChild(makeElement(doc,"playmess","","Вы стали простым пассажиром",""));
                    }
                }
                if((_eve.useit.handle=="Injector")
                        &&(it.value().name==_eve.who.name)) {
                    domStat.appendChild(makeElement(doc,"item","del","","Injector"));
                    domStat.appendChild(makeElement(doc,"rol","del","","Doctor"));
                    if(_eve.who.rolelist.contains("Passenger")){
                        domEvents.appendChild(makeElement(doc,"playmess","","Вы стали простым пассажиром",""));
                    }
                }
                if((_eve.useit.handle=="Scanner")
                        &&(it.value().name==_eve.who.name)) {
                    domStat.appendChild(makeElement(doc,"item","del","","Scanner"));
                    domStat.appendChild(makeElement(doc,"rol","del","","Scientist"));
                    if(_eve.who.rolelist.contains("Passenger")){
                        domEvents.appendChild(makeElement(doc,"playmess","","Вы стали простым пассажиром",""));
                    }
                }
                if((_eve.useit.handle=="Battery")
                        &&(it.value().name==_eve.who.name)) {
                    domStat.appendChild(makeElement(doc,"item","del","","Battery"));
                    domStat.appendChild(makeElement(doc,"rol","del","","Engineer"));
                    if(_eve.who.rolelist.contains("Passenger")){
                        domEvents.appendChild(makeElement(doc,"playmess","","Вы стали простым пассажиром",""));
                    }
                }
            }
        }

        emit sendtoclient(it.value().name,doc.toString());
    }
}

void xml_maker::slotnamecorrect(QString tempname,QString _name){
    QDomDocument doc("select");

    QDomElement domElement = doc.createElement("select");
    doc.appendChild(domElement);

    domElement.appendChild(doc.createElement("namecorrect"));

    domElement.appendChild(name_role_list(doc,_rolelist));
    emit namecorrect(tempname,_name);
    emit sendtoclient(_name,doc.toString());
    emit sendtoclient(tempname,doc.toString());
}


void xml_maker::nonamecorrect(QString tempname){
    QDomDocument doc("select");

    QDomElement domElement = doc.createElement("select");
    doc.appendChild(domElement);

    domElement.appendChild(doc.createElement("namecorrect"));

    emit sendtoclient(tempname,doc.toString());
    emit noVerifyClientName(tempname);
}


void xml_maker::updaterolelist(QMap <QString,player> playerlist,QMap<QString,player>_rolelist){
    QMap<QString, player>::iterator it = playerlist.begin();
    for (;it != playerlist.end(); ++it){
        QDomDocument doc("select");

        QDomElement domElement = doc.createElement("select");
        doc.appendChild(domElement);
        domElement.appendChild(name_role_list(doc,_rolelist));

        emit sendtoclient(it.value().name,doc.toString());
    }
}




QDomElement xml_maker::name_role_list(QDomDocument& domDoc,QMap <QString,player> _rolelist){
    QDomElement domElement=domDoc.createElement("list");
    QMap<QString, player>::iterator it = _rolelist.begin();
    for (;it != _rolelist.end(); ++it) {
        QString _name;
        if(it.value()!=NULL) _name=it.value().name;
        else _name="";
        domElement.appendChild(makeElement(domDoc,it.key(),"",_name,""));
    }
    return domElement;
}


QDomElement xml_maker::makeElement( QDomDocument& domDoc,
                                    const QString& strName,
                                    const QString& strAttr = QString(),
                                    const QString& strText = QString(),
                                    const QString& strAttrText = QString()) {
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

