#include "game.h"


class qLe
{
public:
    inline bool operator()(ingame_event* t1, ingame_event* t2) const
    {
        QList<QString>list;

        QString tt1,tt2;
        if(t1->what=="useitem"||t1->what=="useult"||t1->what=="useultCap"){
            tt1=t1->what+t1->useit;
        }
        else tt1=t1->what;

        if(t2->what=="useitem"||t2->what=="useult"||t2->what=="useultCap"){
            tt2=t2->what+t2->useit;
        }
        else tt2=t2->what;
        list <<"useultCapInjector"<<"useitemInjector" <<"useultCapScanner"<<"useitemScanner"
            <<"useultCapMop"<<"useitemMop"<<"useultCapBattery"<<"useitemBattery"
           <<"useultCapBlaster"<<"useitemBlaster"
          <<"useultBattery"<<"useultInjector" <<"useultBlaster"<<"useultScanner"<<"attack"
         <<"infect"<<"wait"<<"alien"<<"up"<<"down"<<"getitem"<<"delitem";
        return (list.indexOf(tt1) < list.indexOf(tt2));
    }
};

game::game()
{
    votingque.clear();
    _nightque.clear();
    currentday=0;
    //daytime=true;
    player* defolt;
    defolt->name="";
    rolelist.insert("Captain",defolt);
    rolelist.insert("Doctor",defolt);
    rolelist.insert("Gunmen",defolt);
    rolelist.insert("Assistant",defolt);
    rolelist.insert("Engineer",defolt);
    rolelist.insert("Scientist",defolt);
    rolelist.insert("Signalmen",defolt);
    
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
    QList<QString> tmp;
    if(daytime){
        foreach (item* var, who->itemlist.values()) {

            if(var->handle == "Blaster"){
                if(var->power==0){
                    who->actionlist.append(qMakePair(QString("ultBlaster"),playerlist.keys()));
                }
                break;}
            if(var->handle == "Injector"){
                if(var->power==0){
                    who->actionlist.append(qMakePair(QString("useInjector"),playerlist.keys()));
                    who->actionlist.append(qMakePair(QString("ultInjector"),tmp));

                }
                break;}
            if(var->handle == "Notebook"){
                if(_currvoting->is_over!=true){
                    who->actionlist.append(qMakePair(QString("ultNotebook"),tmp));
                    if(var->power==0)
                        who->actionlist.append(qMakePair(QString("useNotebook"),_currvoting->electlist));
                }
                break;}
            if(var->handle == "Battery"){
                who->actionlist.append(qMakePair(QString("ultBattery"),brokeitemlist));
                if(var->power==0){
                    who->actionlist.append(qMakePair(QString("useBattery"),itemlist.keys()));
                }
                break;}
            if(var->handle == "Scanner"){
                who->actionlist.append(qMakePair(QString("ultScanner"),tmp));
                if(var->power==0){
                    who->actionlist.append(qMakePair(QString("useScanner"),playerlist.keys()));
                }
                break;}
            if(var->handle == "Badge"){
                if(_currvoting->is_over!=true && hardresolve==true){
                    who->actionlist.append(qMakePair(QString("useBadge"),_currvoting->winners));
                }
                if(var->power==0){
                    who->actionlist.append(qMakePair(QString("ultBadge"),itemlist.keys()));
                }
                break;}
            if(var->handle == "Rotation"){
                if(nightrotation.isEmpty()){
                    who->actionlist.append(qMakePair(QString("useRotation"),playerlist.keys()));
                }
                break;//если добавить дефолт, то там буде обработка ошибок
            }

        }
        if(_currvoting->is_over!=true){
            if(_currvoting->votelist.value(who->name).second==0)
                who->actionlist.append(qMakePair(QString("vote"),_currvoting->electlist));
            if(_currvoting->votelist.value(who->name).second==1)
                who->actionlist.append(qMakePair(QString("unvote"),tmp));
        }
        if(who->status==2){
            if(who->healthy==true)
                who->actionlist.append(qMakePair(QString("down"),tmp));
            else
                who->actionlist.append(qMakePair(QString("up"),tmp));
        }
    }else{//если ночь
        if(who->use_night_item==0){
            foreach (item* var, who->itemlist.values()) {
                if(var->handle == "Blaster"){
                    if(var->power==0){
                        who->actionlist.append(qMakePair(QString("useBlaster"),playerlist.keys()));
                        who->actionlist.append(qMakePair(QString("ultBlaster"),playerlist.keys()));
                    }
                    break;}
                if(var->handle == "Injector"){
                    if(var->power==0){
                        who->actionlist.append(qMakePair(QString("useInjector"),playerlist.keys()));
                        who->actionlist.append(qMakePair(QString("ultInjector"),tmp));

                    }
                    break;}
                if(var->handle == "Battery"){
                    who->actionlist.append(qMakePair(QString("ultBattery"),brokeitemlist));
                    if(var->power==0){
                        QList <QString> tmp;
                        tmp.append(who->name);
                        who->actionlist.append(qMakePair(QString("useBattery"),tmp));
                    }
                    break;}
                if(var->handle == "Scanner"){
                    who->actionlist.append(qMakePair(QString("ultScanner"),tmp));
                    if(var->power==0){
                        who->actionlist.append(qMakePair(QString("useScanner"),playerlist.keys()));
                    }
                    break;}
                if(var->handle == "Badge"){
                    if(var->power==0){
                        who->actionlist.append(qMakePair(QString("ultBadge"),itemlist.keys()));
                    }
                    break;}
                if(var->handle == "Mop"){
                    who->actionlist.append(qMakePair(QString("useMop"),playerlist.keys()));
                    break;
                }
                if(var->handle == "Fetus"){
                    if(var->power==0){
                        who->actionlist.append(qMakePair(QString("infect"),playerlist.keys()));
                    }
                }

            }

        }
        if(who->status==2)
        {
            if(who->attack_thisnight==0){
                who->actionlist.append(qMakePair(QString("attack"),playerlist.keys()));
            }
            if(who->healthy==true)
                who->actionlist.append(qMakePair(QString("down"),tmp));
            else
                who->actionlist.append(qMakePair(QString("up"),tmp));
        }
        if(who->waiting==false)
            who->actionlist.append(qMakePair(QString("wait"),tmp));
    }
}


void game::day(){
    if(makeNightActoins()){
        daytime=true;
        currentday++;
        _currvoting->is_over=true;

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
    _currvoting->is_over=true;
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
    player* first;
    do{
        a3=rand()%(sizeoflist)+1;
        a4=rand()%(sizeoflist)+1;
    }
    while(a3==a1);
    
    foreach (player* var, playerlist.values()) {
        if(a2==a4){
            var->HP=1;
            first=var;
        }
        a2++;
    }
    //    QMap<QString, player>::const_iterator i;
    //    for (i = playerlist.constBegin(); i != playerlist.constEnd(); ++i){
    //        if(a2==a4){
    //            i.value().HP=1;
    //            first=i.value();
    //        }
    //        a2++;
    //    }
    a2=0;
    QQueue<QString>tmp;
    //for (i = playerlist.constBegin(); i != playerlist.constEnd(); ++i){
    foreach (player* i, playerlist.values()) {
        if (a2==a1){
            i->status=2;
            i->invasionday=0;
            i->HP=5;

            item* fet=new Fetus();
            fet->power=2;
            i->itemlist.insert("Fetus",fet);
            ingame_event* _eve1=new ingame_event(i->name,"","getitem",fet->handle,tmp);
            _nightque.enqueue(_eve1);
            
            ingame_event* _eve=new ingame_event("",i->name,"alien","",tmp);
            _nightque.enqueue(_eve);
            
        }
        if(a2==a3){
            i->status=1;
            
            item* fet=new Fetus();
            fet->power=2;
            i->itemlist.insert("Fetus",fet);
            ingame_event* _eve1=new ingame_event(i->name,"","getitem",fet->handle,tmp);
            _nightque.enqueue(_eve1);
            
            ingame_event* _eve2=new ingame_event("",i->name,"infect","",tmp);
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
            if(_whom->HP<5)_whom->HP=_whom->HP+2;
            if(_whom->HP>5)_whom->HP=5;
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
    if(playerlist.value(who)->waiting==true)playerlist.value(who)->waiting==false;
}

void game::slot_up(QString who){
    playerlist.value(who)->healthy=true;
}

void game::slot_down(QString who){
    playerlist.value(who)->healthy=false;
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
            _who->itemlist.value(useit)->use_item_day(whom);
        else _who->itemlist.value(useit)->use_item_night(whom);
    }//нужно обдумать использование и переписать!!
}

void game::slot_use_item_cap(QString who,QString whom,QString useit){
    player* _who=playerlist.value(who);
    player* _whom=playerlist.value(whom);
    if(_who->itemlist.value("Badge")->power!=-1){
        if(itemlist.value(useit)->power==0){
            if(daytime==true)
                itemlist.value(useit)->use_item_day(whom);
            else itemlist.value(useit)->use_item_night(whom);
            _who->itemlist.value("Badge")->power=-1;
        }
    }
}

void game::slot_ult_item(QString who,QString whom,QString useit){
    player* _who=playerlist.value(who);
    player* _whom=playerlist.value(whom);
    _who->itemlist.value(useit)->ult_item(whom);
    _who->rolelist.removeOne(itemlist.value(useit)->role);
    _who->itemlist.remove(useit);
    if(_who->rolelist.isEmpty()){
        passengerlist.append(who);
    }

}


void game::make_events(QString who,QString whom,QString what,QString how,QQueue<QString> rota){
    //player* _who,_whom;
    //item _how;
    ingame_event* new_event=new ingame_event(who,whom,what,how,rota);
    if (this->daytime){
        _event=new_event;
        _event->do_event();
    } else {
        _nightque.enqueue(new_event);
        if(what=="wait"){
            playerlist.value(who)->waiting=true;
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
                votingque.enqueue(new voting(playerlist.keys(),playerlist.keys(),"Alien"));
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
    if(!playerlist.contains(name)){
        player* noob = new player(name);
        playerlist.insert(name,noob);
        emit namecorrect(tempname,name);
        emit sendrolelist2all(this->playerlist,this->rolelist);
    }else
        emit nonamecorrect(tempname);
}

void game::registerRolebyPlayer(QString _name, QString role){
    if(role!="Passenger"){
        bool inc=false;
        //QMultiMap<QString, player*>::iterator jt = rolelist.begin();
        foreach (player* jt, rolelist.values()) {


       // for (;jt != rolelist.end(); ++jt){
            if(jt->name==""){
                inc=true;
                if(rolelist.key(jt)==role){
                    jt=playerlist.value(_name);
                    playerlist.value(_name)->rolelist.append(role);
                    emit rolecorrect(_name);
                }
            }
            if((jt->name!="")&&(rolelist.key(jt)==role)){
                emit norolecorrect(_name);
            }
        }
        if((inc==false)&&(rolelist.size()==7)){
            player* defolt;
            defolt->name="";
            rolelist.insert("Dep_Doctor",defolt);
            rolelist.insert("Dep_Gunmen",defolt);
            rolelist.insert("Dep_Engineer",defolt);
            rolelist.insert("Dep_Scientist",defolt);
            rolelist.insert("Dep_Signalmen",defolt);
            emit startnewsessionenable(true);
        }
        if((inc==false)&&(rolelist.size()==12)){
            rolelist.insert("Passenger",NULL);
        }
    }else{
        passengerlist.append(_name);
        playerlist.value(_name)->rolelist.append(role);
        emit rolecorrect(_name);
    }
    
    emit sendrolelist2all(playerlist,rolelist);
    
}

void game::player_death(player* dead){
    //тут будет отправка о том что игрок мертв
    QList <QString> mainroles;
    mainroles << "Captain"<<"Doctor"<<"Gunmen"<<"Assistant"<<"Engineer"<<"Scientist"<<"Signalmen";
    playerlist.remove(dead->name);
    foreach (QString var, rolelist.uniqueKeys()) {
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
    passengerlist.removeAll(dead->name);

}

void game::check_for_role(QString role){//передача роли заместителям или кому придется, заодно добавление голосований если нужно
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
        QList <QString> tmp;
        foreach (player* vvv, playerlist.values()) {
            if(vvv->rolelist.contains(deprole.value(role))){
                tmp.append(vvv->name);
            }
        }
        votingque.enqueue(new voting(playerlist.keys(),tmp,role));
    }
    if(co==0){
        //QList <player*> cc;
        QList<QString>cc;
        foreach (QString var, deprole.values()) {
            foreach (player* vvv, playerlist.values()) {
                if(vvv->rolelist.contains(deprole.value(var))){
                    cc.append(vvv->name);
                }
            }
            // cc.append(rolelist.values(var));
        }
        cc.append(passengerlist);
        if(cc.count()>1){
            votingque.enqueue(new voting(playerlist.keys(),cc,role));
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
                add_role(playerlist.value(passengerlist.first()),role);
                passengerlist.clear();
            }
        }
        if(cc.count()==0){
            int i=1;
            do{
                foreach(player* var,rolelist.values()){
                    if(var->rolelist.count()==i){
                        cc.append(var->name);
                    }
                }
                i++;
            }while(cc.count()<1);
            if (cc.count()==1){
                //отправка сообщения о присвоении роли игроку с наименьшим числом ролей
                add_role(playerlist.value(cc.first()),role);
            } else {
                votingque.enqueue(new voting(playerlist.keys(),cc,role));
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
    //QList<ingame_event*>::iterator i;
    while (_queue.isEmpty()) {
        ingame_event* _eve=_queue.dequeue();

        if(_eve->what=="useult"&&playerlist.value(_eve->who)->rolelist.contains("Captain")
                &&playerlist.value(_eve->who)->itemlist.value("Badge")->power==0){
            _eve->what="useitemCap";
            if(_eve->useit=="Mop"){
                playerblock.append(_eve->whom);
            }
            if(_eve->useit=="Battery"){
                playerblock.append(_eve->who);
            }
            if(_eve->useit=="Blaster"){
                playerblock.append(_eve->whom);
            }
            _que.enqueue(_eve);
            itblok=_eve->useit;
            continue;
        }
        if((_eve->what=="useitem"||_eve->what=="useult")&&
                ((_eve->useit==itblok)||(playeritemuse.contains(_eve->who)))){
            continue;
        }
        if((_eve->what=="useitem")&&(_eve->useit=="Scanner")){
            playeritemuse.append(_eve->who);
            _que.enqueue(_eve);
            continue;
        }
        if((_eve->what=="useitem"||_eve->what=="useult")&&_eve->useit=="Mop"){
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who);
            playerblock.append(_eve->whom);
            continue;
        }
        if(((playerblock.contains(_eve->who))||(playerblock.contains(_eve->whom)))
                &&((_eve->what=="useitem")||(_eve->what=="useult")||(_eve->what=="attack")
                   ||(_eve->what=="infect"))){
            continue;
        }
        if((_eve->what=="useitem")&&(_eve->useit=="Battery")){
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who);
            playerblock.append(_eve->who);
            continue;
        }
        if((_eve->what=="useitem")&&(_eve->useit=="Blaster")){
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who);
            if(_eve->whom!="")playerhunt.append(_eve->whom); else//опасная для логики зона
            {
                foreach (player* play, playerlist.values()) {
                    if(!play->healthy)playerhunt.append(play->name);
                }
            }
            playerhunt.append(_eve->who);
            continue;
        }
        bool AAA = playerhunt.contains(_eve->who);
        bool BBB = playerhunt.contains(_eve->whom);
        if(((!AAA&&BBB)||(!BBB&&AAA))//адская замена ксору
                &&((_eve->what=="useult")||(_eve->what=="attack")
                   ||(_eve->what=="infect"))){
            playerlist.value(_eve->who)->HP=playerlist.value(_eve->who)->HP-2;
            continue;
        }

        if((_eve->what=="useult")&&(_eve->useit=="Battery")){
            _que.enqueue(_eve);
            continue;
        }
        if((_eve->what=="useult")&&(_eve->useit=="Injector")){
            playeritemuse.append(_eve->who);
            _que.enqueue(_eve);
            continue;
        }
        if((_eve->what=="useult")&&(_eve->useit=="Scanner")){
            playeritemuse.append(_eve->who);
            _que.enqueue(_eve);
            continue;
        }
        if((_eve->what=="attack")){
            if(attackedhuman.contains(_eve->whom)){
                continue;
            }
            if(playerlist.value(_eve->who)->status!=2){
                attackedhuman.append(_eve->whom);}
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



