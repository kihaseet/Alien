#include "game.h"

game::game()
{
    votingque.clear();
    _nightque.clear();
    currentday=0;
    //daytime=true;
    rolelist.insert("Captain",NULL);
    rolelist.insert("Doctor",NULL);
    rolelist.insert("Gunmen",NULL);
    rolelist.insert("Assistant",NULL);
    rolelist.insert("Engineer",NULL);
    rolelist.insert("Scientist",NULL);
    rolelist.insert("Signalmen",NULL);
    
    connect(this,SIGNAL(startday()),SLOT(day()));
    connect(this,SIGNAL(startnight()),SLOT(night_start()));
    connect(this,SIGNAL(startgame()),SLOT(start()));
    
}

void game::start(){
    StartRandomEvasion();
    //votingque.enqueue(new voting(playerlist,playerlist.values(),"Alien"));
    connect(_event,SIGNAL(event_attack(QString,QString)),this,SLOT(slot_attack(QString,QString)));
    connect(_event,SIGNAL(event_down(QString)),this,SLOT(slot_down(QString)));
    connect(_event,SIGNAL(event_infect(QString,QString)),this,SLOT(slot_infect(QString,QString)));
    connect(_event,SIGNAL(event_ultitem(QString,QString,QString)),this,SLOT(slot_ult_item(QString,QString,QString)));
    connect(_event,SIGNAL(event_up(QString)),this,SLOT(slot_up(QString)));
    connect(_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(slot_use_item(QString,QString,QString)));
    connect(_event,SIGNAL(event_useitemcap(QString,QString,QString)),this,SLOT(slot_use_item_cap(QString,QString,QString)));
    connect(_event,SIGNAL(event_wait(QString)),this,SLOT(slot_wait(QString)));
    connect(_event,SIGNAL(event_alien(QString)),this,SLOT(slot_alien(QString)));

    emit startday();
}

void game::make_actionlist(player* who){
    who->actionlist.clear();
    if(daytime){
        foreach (item* var, who->itemlist.values()) {
            switch(var->handle){
            case "Blaster":{
                if(var->power==0){
                    who->actionlist.append(qMakePair("ultBlaster",playerlist.keys()));
                }
                break;}
            case "Injector":{
                if(var->power==0){
                    who->actionlist.append(qMakePair("useInjector",playerlist.keys()));
                    who->actionlist.append(qMakePair("ultInjector",new QList()));

                }
                break;}
            case "Notebook":{
                if(_currvoting!=NULL){
                    who->actionlist.append(qMakePair("ultNotebook",new QList()));
                    if(var->power==0)
                        who->actionlist.append(qMakePair("useNotebook",_currvoting->electlist));
                }
                break;}
            case "Battery":{
                who->actionlist.append(qMakePair("ultBattery",brokeitemlist));
                if(var->power==0){
                    who->actionlist.append(qMakePair("useBattery",itemlist.keys()));
                }
                break;}
            case "Scanner":{
                who->actionlist.append(qMakePair("ultScanner",new QList()));
                if(var->power==0){
                    who->actionlist.append(qMakePair("useScanner",playerlist.keys()));
                }
                break;}
            case "Badge":{
                if(_currvoting!=NULL && hardresolve=true){
                    who->actionlist.append(qMakePair("useBadge",_currvoting->winners));
                }
                if(var->power==0){
                    who->actionlist.append(qMakePair("ultBadge",itemlist.keys()));
                }
                break;}
            case "Rotation":{
                if(nightrotation.isEmpty()){
                    who->actionlist.append(qMakePair("useRotation",playerlist.keys()));
                }
                break;}//если добавить дефолт, то там буде обработка ошибок
            }

        }
        if(_currvoting!=NULL){
            if(_currvoting->votelist.value(who->name).second==0)
                who->actionlist.append(qMakePair("vote",_currvoting->electlist));
            if(_currvoting->votelist.value(who->name).second==1)
                who->actionlist.append(qMakePair("unvote",new QList()));
        }
        if(who->status==2){
            if(who->healthy==true)
                who->actionlist.append(qMakePair("down",new QList()));
            else
                who->actionlist.append(qMakePair("up",new QList()));
        }
    }else{//если ночь
        if(who->use_night_item==0){
            foreach (item* var, who->itemlist.values()) {
                switch(var->handle){
                case "Blaster":{
                    if(var->power==0){
                        who->actionlist.append(qMakePair("useBlaster",playerlist.keys()));
                        who->actionlist.append(qMakePair("ultBlaster",playerlist.keys()));
                    }
                    break;}
                case "Injector":{
                    if(var->power==0){
                        who->actionlist.append(qMakePair("useInjector",playerlist.keys()));
                        who->actionlist.append(qMakePair("ultInjector",new QList()));

                    }
                    break;}
                case "Battery":{
                    who->actionlist.append(qMakePair("ultBattery",brokeitemlist));
                    if(var->power==0){
                        QList <QString> tmp;
                        tmp.append(who->name);
                        who->actionlist.append(qMakePair("useBattery",tmp));
                    }
                    break;}
                case "Scanner":{
                    who->actionlist.append(qMakePair("ultScanner",new QList()));
                    if(var->power==0){
                        who->actionlist.append(qMakePair("useScanner",playerlist.keys()));
                    }
                    break;}
                case "Badge":{
                    if(var->power==0){
                        who->actionlist.append(qMakePair("ultBadge",itemlist.keys()));
                    }
                    break;}
                case "Mop":{
                    who->actionlist.append(qMakePair("useMop",playerlist.keys()));
                    break;
                }
                case "Fetus":{
                    if(var->power==0){
                        who->actionlist.append(qMakePair("infect",playerlist.keys()));
                    }
                }
                }
            }

        }
    if(who->status==2)
    {
        if(who->attack_thisnight==0){
            who->actionlist.append(qMakePair("attack",playerlist));
        }
        if(who->healthy==true)
            who->actionlist.append(qMakePair("down",new QList()));
        else
            who->actionlist.append(qMakePair("up",new QList()));
    }
    if(who->waiting==false)
        who->actionlist.append(qMakePair("wait",new QList()));
    }
}


void game::day(){
    if(makeNightActoins()){
        daytime=true;
        currentday++;
        _currvoting=NULL;

        if (!votingque.isEmpty()){
            day_next_voting();
        } else {
            night_start();
        }
    } else emit game_over();
}

void game::day_next_voting(){
    hardresolve=false;
    _currvoting = votingque.dequeue();
    connect (_event,SIGNAL(event_useitem(QString,QString,QString)),_currvoting,SLOT(use_notebook(QString,QString,QString)));
    connect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(day_cap_curr_voting(QString,QString,QString)));

    connect (_event,SIGNAL(event_ultitem(QString,QString,QString)),_currvoting,SLOT(ult_notebook(QString,QString,QString)));

    connect (_event,SIGNAL(event_vote(QString,QString)),_currvoting,SLOT(on_voting(QString,QString)));
    connect (_event,SIGNAL(event_unvote(QString)),_currvoting,SLOT(off_voting(QString)));

    connect (_currvoting,SIGNAL(voting_over(QList<QString>)),this,SLOT(day_resolve_curr_voting(QList<QString>)));
    connect (_currvoting,SIGNAL(voting_canseled()),this,SLOT(day_canseled_voting()));

}


void game::day_cap_curr_voting(QString who,QString win,QString useit){
    if(useit=="Badge"){
        day_end_curr_voting(win);
    }
}

void game::day_end_curr_voting(QString winner){
    //тут отправка игрокам сообщения
    if (playerlist.contains(winner)){
        player* win = playerlist.value(winner);
        if (_currvoting->target=="Alien"){
            if(win->status<2){
                //игрок - человек
                win->HP=win->HP-1;
                if(win->HP>0)win->healthy=false;
                else player_death(win);
                if(win->status==1){
                    //оповещение об изъятии эмбриона
                    win->status=0;
                    win->itemlist.remove("Fetus");
                }
            }
            if(win->status==2){
                //оповещение о том, что игрок - чужой
                player_death(win);
            }
        }
        else{
            //оповещение о присуждении роли
            add_role(win,_currvoting->target);
        }
    }
    _currvoting=NULL;
    if(!votingque.isEmpty()){
        day_next_voting();
    }
    else {
        night_start();
    }
}


void game::day_resolve_curr_voting(QList<QString> win){


    if(win.count()==1){
        day_end_curr_voting(win.first());
    }
    if(win.count()>1){
        //тут будет предложение капитану определить итог голосования лично
        hardresolve=true;
    }

}


void game::day_canseled_voting(){
    //тут будет сообщение игрокам об отмене голосования
    if(!votingque.isEmpty()){
        day_next_voting();
    }
    else night_start();
}

void game::slot_game_over(){
    //    foreach (player*v, playerlist.values()) {
    //        //отправка сообщения об окончании игры
    //    }

    if(playerlist.begin().value()->status==0){
        //отправка всем сообщение о победе людей
    } else {
        //отправка всем сообщения о победе чужих
    }
    //статистика, ачивки, прочее дерьмо
}

bool game::night(){
    foreach (player* v, playerlist.values()){
        if(v->waiting==false){
            break;
            return false;
        }
    }
    return true;
}

void game::night_start(){
    daytime=false;
    foreach (player* v, playerlist.values()) {
        v->waiting=false;
        v->attack_thisnight=0;
        v->use_night_item=0;
    }
}

void game::StartRandomEvasion(){
    int sizeoflist=playerlist.size();
    int a1=rand()%(sizeoflist)+1;//первый чужой
    int a2=0;
    int a3;//первый зараженный
    int a4;//первый раненый
    player first;
    do{
        a3=rand()%(sizeoflist)+1;
        a4=rand()%(sizeoflist)+1;
    }
    while(a3==a1);
    
    QMap<QString, player>::const_iterator i;
    for (i = playerlist.constBegin(); i != playerlist.constEnd(); ++i){
        if(a2==a4){
            i.value().HP=1;
            first=i.value();
        }
        a2++;
    }
    a2=0;
    
    for (i = playerlist.constBegin(); i != playerlist.constEnd(); ++i){
        if (a2==a1){
            i.value().lastattack=first;
            i.value().status=2;
            i.value().invasionday=0;
            i.value().HP=5;
            
            item* fet=new Fetus();
            fet->power=2;
            i.value().itemlist.insert("Fetus",fet);
            ingame_event* _eve1=new ingame_event(i.value(),NULL,"getitem",fet);
            _nightque.enqueue(_eve1);
            
            ingame_event* _eve=new ingame_event(NULL,i.value(),"alien",NULL);
            _nightque.enqueue(_eve);
            
        }
        if(a2==a3){
            i.value().status=1;
            
            item* fet=new Fetus();
            fet->power=2;
            i.value().itemlist.insert("Fetus",fet);
            ingame_event* _eve1=new ingame_event(i.value(),NULL,"getitem",fet);
            _nightque.enqueue(_eve1);
            
            ingame_event* _eve2=new ingame_event(NULL,i.value(),"infect",NULL);
            _nightque.enqueue(_eve2);
        }
        a2++;
    }
}

void game::slot_attack(QString who, QString whom){
    //если надо, добавить проверку на наличие
    player* _who = playerlist.value(who);
    player* _whom = playerlist.value(whom);
    if(_who->HP<5) _who->HP+1;
    _whom->HP=_whom->HP-2;
    _who->success_attack=_who->success_attack+1;
    if(_who->success_attack==2){
        if(!_who->itemlist.contains("Fetus")){
            item* fet=new Fetus();
            fet->power=0;
            _who->itemlist.insert("Fetus",fet);
        }
        _who->success_attack=0;
    }
}

void game::slot_infect(QString who, QString whom){
    player* _who=playerlist.value(who);
    player* _whom=playerlist.value(whom);
    if(_who->itemlist.value("Fetus")->power==0 && _who->status==2){
        if(_whom->status==1){
            _whom->itemlist.value("Fetus")->power=2;
        }
        if(_whom->status==0){
            item* fet=new Fetus();
            fet->power=2;
            _whom->itemlist.insert("Fetus",fet);
            _whom->status=1;
        }

        if(_whom->status==2){
            if(_whom.HP<5)_whom->HP+2;
            if(_whom.HP>5)_whom->HP=5;
        }
        _who->itemlist.remove("Fetus");
    }
}

void game::slot_alien(QString who){
    player* _who = playerlist.value(who);
    if (_who->status==1 && _who->itemlist.value("Fetus")->power==0){
        _who->status=2;
        _who->HP=_who->HP+(_who->HP-1);
        _who->success_attack=1;
        _who->itemlist.remove("Fetus");
    }
}

void game::slot_wait(QString who){
    if(playerlist.value(who).waiting==true)playerlist.value(who)->waiting==false;
}

void game::slot_up(QString who){
    playerlist.value(who).healthy=true;
}

void game::slot_down(QString who){
    playerlist.value(who).healthy=false;
}


void game::add_role(player* whom,QString what){
    rolelist.insertMulti(what,whom);
    whom->rolelist.append(what);
    foreach (item* var, itemlist.values()) {
        if(var->role==what){
            whom->itemlist.insert(var->handle,var);
        }
    }

}

void game::delete_role(player* whom,QString what){
    rolelist.remove(what,whom);
    if(rolelist.count(what)==0)rolelist.remove(what);
    whom->rolelist.removeOne(what);
    foreach (item* var, itemlist.values()) {
        if(var->role==what){
            whom->itemlist.remove(var->handle);
        }
    }

}

void game::slot_use_item(QString who,QString whom,QString useit){
    player* _who=playerlist.value(who);
    player* _whom=playerlist.value(whom);

    if(_who->itemlist.value(useit)->power==0){
        if(daytime==true)
            _who->itemlist.value(useit)->use_item_day(_whom);
        else _who->itemlist.value(useit)->use_item_night(_whom);
    }//нужно обдумать использование и переписать!!
}

void game::slot_use_item_cap(QString who,QString whom,QString useit){
    player* _who=playerlist.value(who);
    player* _whom=playerlist.value(whom);
    if(_who->itemlist.value("Badge")->power!=-1){
        if(itemlist.value(useit)->power==0){
            if(daytime==true)
                itemlist.value(useit)->use_item_day(_whom);
            else itemlist.value(useit)->use_item_night(_whom);
            _who->itemlist.value("Badge")->power=-1;
        }
    }
}

void game::slot_ult_item(QString who,QString whom,QString useit){
    player* _who=playerlist.value(who);
    player* _whom=playerlist.value(whom);
    _who->itemlist.value(useit)->ult_item(_whom);
    _who->rolelist.removeOne(itemlist.value(useit)->role);
    _who->itemlist.remove(useit);
    if(_who->rolelist.isEmpty()){
        passengerlist.append(_who);
    }

}


void game::make_events(QString who,QString whm,QString what,QString how,QQueue<QString> rota){
    player _who,_whom;
    item _how;
    ingame_event new_event;
    
    if (playerlist.contains(who)) _who = playerlist.value(who);
    if (who=="")_who=NULL;
    
    if(playerlist.contains(whm)) _whom = playerlist.value(whm);
    if (whm=="")_whom=NULL;
    
    if (how!=""){
        if(playerlist.value(who).itemlist.contains(how)){
            _how = playerlist.value(who).itemlist.value(how);
        }
    } else _how = NULL;
    
    new_event=new ingame_event(who,whom,what,how);
    if (this->daytime){
        _event=new_event;
        _event->do_event();
    } else {
        _nightque.enqueue(new_event);
        if(what=="wait"){
            playerlist.value(who)->waiting==true;
        }
        if(night()==true){
            //тут отправка сообщения об окончании ночи
            day();
        }
    }
}



bool game::makeNightActoins(){//true - продолжать игру, false - game over
    while(!_nightque.isEmpty()){
        _event=_nightque.dequeue();
        _event->do_event();
    }
    if (playerlist.count()>1){
        foreach (player* v, playerlist.values()) {
            if (v->status>=1){
                votingque.enqueue(new voting(playerlist,playerlist.values(),"Alien"));
                return true;
            }
        }
        return false;//все здоровы, чужих больше нет
    } else {
        if(playerlist.begin().value()->status!=1)
            return false;
    }//остался последний игрок, или больше никого не осталось.
}

void game::register_new_player(QString tempname,QString name){
    if(!playerlist.contains(&name)){
        player* noob = new player(name);
        playerlist.insert(&name,noob);
        emit namecorrect(tempname,name);
        emit sendrolelist2all(this->playerlist,this->rolelist);
    }else
        emit nonamecorrect(tempname);
}

void game::registerRolebyPlayer(QString _name, QString role){
    if(role!="Passenger"){
        bool inc=false;
        QMultiMap<QString, player>::iterator jt = rolelist.begin();
        for (;jt != rolelist.end(); ++jt){
            if(jt.value()==NULL){
                inc=true;
                if(jt.key()==role){
                    jt.value()=playerlist.value(_name);
                    playerlist.value(_name).rolelist.append(role);
                    emit rolecorrect(_name);
                }
            }
            if((jt.value()!=NULL)&&(jt.key()==role)){
                emit norolecorrect(_name);
            }
        }
        if((inc==false)&&(rolelist.size()==7)){
            rolelist.insert("Dep_Doctor",NULL);
            rolelist.insert("Dep_Gunmen",NULL);
            rolelist.insert("Dep_Engineer",NULL);
            rolelist.insert("Dep_Scientist",NULL);
            rolelist.insert("Dep_Signalmen",NULL);
            emit startnewsessionenable(true);
        }
        if((inc==false)&&(rolelist.size()==12)){
            rolelist.insert("Passenger",NULL);
        }
    }else{
        passengerlist.append(playerlist.value(_name));
        playerlist.value(_name).rolelist.append(role);
        emit rolecorrect(_name);
    }
    
    emit sendrolelist2all(playerlist,rolelist);
    
}

void game::player_death(player* dead){
    //тут будет отправка о том что игрок мертв
    QList <QString> mainroles;
    mainroles << "Captain"<<"Doctor"<<"Gunmen"<<"Assistant"<<"Engineer"<<"Scientist"<<"Signalmen";
    playerlist.remove(dead->name);
    foreach (QString &var, rolelist.uniqueKeys()) {
        foreach (player* v, rolelist.values(var))
            if(v==dead){

                if(mainroles.contains(var)){
                    rolelist.remove(var);
                    check_for_role(var);
                }
                else rolelist.remove(var,dead);
                //                rolelist.remove(var,dead);
                //                if(rolelist.count(var)==0)rolelist.insertMulti(var,NULL);
                //                if(mainroles.contains(var))votingque.enqueue(new voting(playerlist,var));
            }
    }
    passengerlist.removeAll(dead);

}

bool game::check_for_role(QString role){//передача роли заместителям или кому придется, заодно добавление голосований если нужно
    //дописать то, что после капитана роль принимает на себя заместитель и наоборот!
    //вроде должно сработать. пока не отражено, что капитан назначает первого помощника сам.
    QMap <QString,QString>deprole;
    deprole.insert("Doctor","Deputy of Doctor");
    deprole.insert("Gunmen","Deputy of Gunmen");
    deprole.insert("Engineer","Deputy of Engineer");
    deprole.insert("Scientist","Deputy of Scientist");
    deprole.insert("Signalmen","Deputy of Signalmen");
    deprole.insert("Captain","Assistant");
    deprole.insert("Assistant","Captain");

    int co = rolelist.count(deprole.value(role));
    if(co==1){
        //тут будет отправка сообщения о присвоении роли единственному заму
        add_role(rolelist.value(deprole.value(role)),role);
        delete_role(rolelist.value(deprole.value(role)),deprole.value(role));
    }
    if(co>1){
        //начало голосования среди замов роли
        votingque.enqueue(new voting(playerlist,rolelist.values(deprole.value(role)),role));
    }
    if(co==0){
        QList <player*> cc;
        foreach (QString var, deprole.values()) {
            cc.append(rolelist.values(var));
        }
        cc.append(passengerlist);
        if(cc.count()>1){
            votingque.enqueue(new voting(playerlist,cc,role));
        }
        if(cc.count()==1){
            if(passengerlist.isEmpty()){
                foreach (QString var, deprole.values()) {
                    if(!rolelist.values(var).isEmpty()){
                        //тут будет отправка сообщения о присвоении роли единственному левому заму
                        add_role(rolelist.value(var),role);
                        delete_role(rolelist.value(var),var);
                    }
                }
            } else {
                //тут будет отправка сообщения о присвоении роли единственному пассащиру
                add_role(passengerlist.first(),role);
                passengerlist.clear();
            }
        }
        if(cc.count()==0){
            int i=1;
            do{
                foreach(player* var,rolelist.values()){
                    if(var->rolelist.count()==i){
                        cc.append(var);
                    }
                }
                i++;
            }while(cc.count()<1);
            if (cc.count()==1){
                //отправка сообщения о присвоении роли игроку с наименьшим числом ролей
                add_role(cc.first(),role);
            } else {
                votingque.enqueue(new voting(playerlist,cc,role));
            }
        }

    }
}

void game::sortNightActions(){
    QQueue<ingame_event*>_queue=_nightque;
    qSort(_queue.begin(),_queue.end(),qLe());
    QQueue<ingame_event*>_que;
    QList <QString> playerblock;
    QList <QString> playeritemuse;
    QString itblok;
    QList <QString> playerhunt;
    QList <QString> attackedhuman;
    QList<ingame_event*>::iterator i;
    while (_queue.isEmpty()) {
        ingame_event* _eve=_queue.dequeue();

        if(_eve.what=="useult"&&_eve.who.rolelist.contains("Captain")
                &&_eve.who.itemlist.value("Badge")->power==0){
            _eve->what="useitemCap";
            if(_eve->useit.handle=="Mop"){
                playerblock.append(_eve->whom.name);
            }
            if(_eve->useit.handle=="Battery"){
                playerblock.append(_eve->who.name);
            }
            if(_eve->useit.handle=="Blaster"){
                playerblock.append(_eve->whom.name);
            }
            _que.enqueue(_eve);
            itblok=_eve.useit.handle;
            continue;
        }
        if((_eve.what=="useitem"||_eve.what=="useult")&&
                ((_eve.useit.handle==itblok)||(playeritemuse.contains(_eve->who.name)))){
            continue;
        }
        if((_eve->what=="useitem")&&(_eve->useit.handle=="Scanner")){
            playeritemuse.append(_eve->who.name);
            _que.enqueue(_eve);
            continue;
        }
        if((_eve->what=="useitem"||_eve.what=="useult")&&_eve->useit.handle=="Mop"){
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who.name);
            playerblock.append(_eve->whom.name);
            continue;
        }
        if(((playerblock.contains(_eve->who.name))||(playerblock.contains(_eve->whom.name)))
                &&((_eve->what=="useitem")||(_eve->what=="useult")||(_eve->what=="attack")
                   ||(_eve->what=="infect"))){
            continue;
        }
        if((_eve->what=="useitem")&&(_eve->useit.handle=="Battery")){
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who.name);
            playerblock.append(_eve->who.name);
            continue;
        }
        if((_eve->what=="useitem")&&(_eve->useit.handle=="Blaster")){
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who.name);
            if(_eve->whom!=NULL)playerhunt.append(_eve->whom.name); else
            {
                foreach (player play, playerlist) {
                    if(!play.healthy)playerhunt.append(play.name);
                }
            }
            playerhunt.append(_eve->who.name);
            continue;
        }
        if(((playerhunt.contains(_eve->who.name))^(playerhunt.contains(_eve->whom.name)))
                &&((_eve->what=="useult")||(_eve->what=="attack")
                   ||(_eve->what=="infect"))){
            _eve->who.HP=_eve->who.HP-2;
            continue;
        }

        if((_eve->what=="useult")&&(_eve->useit.handle=="Battery")){
            _que.enqueue(_eve);
            continue;
        }
        if((_eve->what=="useult")&&(_eve->useit.handle=="Injector")){
            playeritemuse.append(_eve->who.name);
            _que.enqueue(_eve);
            continue;
        }
        if((_eve->what=="useult")&&(_eve->useit.handle=="Scanner")){
            playeritemuse.append(_eve->who.name);
            _que.enqueue(_eve);
            continue;
        }
        if((_eve->what=="attack")){
            if(attackedhuman.contains(_eve->whom)){
                continue;
            }
            if(_eve->whom.status!=2){
                attackedhuman.append(_eve->whom.name);}
            _que.enqueue(_eve);
            continue;
        }
        if(_eve->what=="infect"){
            _que.enqueue(_eve);
            continue;
        }
        if(_eve->what=="wait"){
            _que.enqueue(_eve);
            continue;
        }
        if(_eve->what=="alien"||_eve->what=="up"||_eve->what=="down"
                ||_eve->what=="getitem"||_eve->what=="delitem"){
            _que.enqueue(_eve);
            continue;
        }


    }
    _nightque=_que;
}


class qLe
{
public:
    inline bool operator()(ingame_event t1, ingame_event t2) const
    {
        QList<QString>list;
        
        QString tt1;
        if(t1.what=="useitem"||t1.what=="useult"){
            tt1=t1.what+t1.useit.handle;
            if(t1.what=="useult"&&t1.who.rolelist.contains("Captain")
                    &&t1.who.itemlist.value("Badge")->power==0)
                tt1+="Cap";
        }
        else tt1=t1.what;
        
        if(t1.what=="useitem"||t1.what=="useult"){
            tt1=t1.what+t1.useit.handle;
            if(t1.what=="useult"&&t1.who.rolelist.contains("Captain")
                    &&t1.who.itemlist.value("Badge")->power==0)
                tt1+="Cap";
        }
        else tt2=t2.what;
        list <<"useultInjectorCap"<<"useitemInjector" <<"useultScannerCap"<<"useitemScanner"
            <<"useultMopCap"<<"useitemMop"<<"useultBatteryCap"<<"useitemBattery"
           <<"useultBlasterCap"<<"useitemBlaster"
          <<"useultBattery"<<"useultInjector" <<"useultBlaster"<<"useultScanner"<<"attack"
         <<"infect"<<"wait"<<"alien"<<"up"<<"down"<<"getitem"<<"delitem";
        return (list.indexOf(tt1) < list.indexOf(tt2));
    }
};
