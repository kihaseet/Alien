#include "game.h"



class qLe
{
public:
    inline bool operator()(TurnObject* t1, TurnObject* t2) const
    {
        // QStringList list;
        
        /*QString tt1,tt2;
        if(t1->what=="useitem"||t1->what=="useult"||t1->what=="useitemCap"){
            tt1=t1->what+t1->useit;
        }
        else tt1=t1->what;
        
        if(t2->what=="useitem"||t2->what=="useult"||t2->what=="useitemCap"){
            tt2=t2->what+t2->useit;
        }
        else tt2=t2->what;*/
        
        /*list <<"useitemCapInjector"<<"useitemInjector" <<"useitemCapScanner"<<"useitemScanner"
            <<"useitemCapMop"<<"useitemMop"<<"useitemCapBattery"<<"useitemBattery"
           <<"useitemCapBlaster"<<"useitemBlaster"
          <<"useultBattery"<<"useultInjector" <<"useultBlaster"<<"useultScanner"<<"attack"
         <<"infect"<<"wait"<<"alien"<<"up"<<"down"<<"getitem"<<"delitem";*/
        
        if(t1->type == TT_ATTACK && t2->type == TT_ATTACK){
            if(t1->wh->HP < t2->wh->HP){
                return false;
            }else{
                if (t1->wh->HP == t2->wh->HP){
                    if(t1->wh->invasionday < t2->wh->invasionday){
                        return false;
                    } else{
                        if(t1->wh->invasionday == t2->wh->invasionday){
                            if(t1->wh->whoinvas->invasionday < t2->wh->whoinvas->invasionday){
                                return false;
                            }
                        }
                    }
                }
            }
        }
        
        return t1 < t2;
    }
};



game::game()
{
    qDebug()<<"game::game()";
    votingque.clear();
    _nightque.clear();
    currentday=0;
    daytime=true;
    playerlist = new QMap <QString,player*>();
    
    unclame_rolelist.append("Captain");
    unclame_rolelist.append("Doctor");
    unclame_rolelist.append("Gunmen");
    unclame_rolelist.append("Assistant");
    unclame_rolelist.append("Engineer");
    unclame_rolelist.append("Scientist");
    unclame_rolelist.append("Signalmen");
    
    connect(this,SIGNAL(startday()),SLOT(day()));
    connect(this,SIGNAL(startnight()),SLOT(night_start()));
    connect(this,SIGNAL(startgame()),SLOT(start()));
    
}

void game::start(){
    //qDebug()<<"game::start()";
    emit startnewsessionenable(false);
    
    _event=new TurnObject();
    _currvoting=new voting();
    connect(_event,SIGNAL(event_attack(QString,QString)),this,SLOT(slot_attack(QString,QString)));
    connect(_event,SIGNAL(event_down(QString)),this,SLOT(slot_down(QString)));
    connect(_event,SIGNAL(event_infect(QString,QString)),this,SLOT(slot_infect(QString,QString)));
    connect(_event,SIGNAL(event_ultitem(QString,QString,QString)),this,SLOT(slot_ult_item(QString,QString,QString)));
    connect(_event,SIGNAL(event_up(QString)),this,SLOT(slot_up(QString)));
    connect(_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(slot_use_item(QString,QString,QString)));
    connect(_event,SIGNAL(event_useitemcap(QString,QString,QString)),this,SLOT(slot_use_item_cap(QString,QString,QString)));
    connect(_event,SIGNAL(event_wait(QString)),this,SLOT(slot_wait(QString)));
    connect(_event,SIGNAL(event_alien(QString)),this,SLOT(slot_alien(QString)));
    connect(_event,SIGNAL(event_getitem(QString,QString,QString)),this,SLOT(slot_getitem(QString,QString,QString)));
    StartRandomEvasion();
    unclame_rolelist.clear();
    getItemByRoleAll();
    emit startday();
}

void game::getItemByRoleAll(){
    //qDebug()<<"game::getItemByRoleAll()";
    foreach (player* var, playerlist->values()) {
        if(var->rolelist.contains("Captain")){
            item* bb=new Badge(this);
            bb->power=0;
            var->itemlist.insert("Badge",bb);
            itemlist.insert("Badge",bb);
        }
        if(var->rolelist.contains("Doctor")){
            item* bb=new Injector(this);
            bb->power=0;
            var->itemlist.insert("Injector",bb);
            itemlist.insert("Injector",bb);
            connect(bb,SIGNAL(item_heal_all()),this,SLOT(slot_heal_all()));
        }
        if(var->rolelist.contains("Gunmen")){
            item* bb=new Blaster(this);
            bb->power=0;
            var->itemlist.insert("Blaster",bb);
            itemlist.insert("Blaster",bb);
        }
        if(var->rolelist.contains("Assistant")){
            item* bb=new Rotation(this);
            bb->power=0;
            var->itemlist.insert("Rotation",bb);
            itemlist.insert("Rotation",bb);
        }
        if(var->rolelist.contains("Engineer")){
            item* bb=new Battery(this);
            bb->power=2;
            var->itemlist.insert("Battery",bb);
            itemlist.insert("Battery",bb);
        }
        if(var->rolelist.contains("Scientist")){
            item* bb=new Scanner(this);
            bb->power=0;
            var->itemlist.insert("Scanner",bb);
            itemlist.insert("Scanner",bb);
        }
        if(var->rolelist.contains("Signalmen")){
            item* bb=new Notebook(this);
            bb->power=0;
            var->itemlist.insert("Notebook",bb);
            itemlist.insert("Notebook",bb);
        }
    }
}


void game::make_actionlist(player* who){
    //qDebug()<<"game::make_actionlist(player* who)"<<who->name;
    who->actionlist.clear();
    QList<QString> tmp;
    if(daytime){
        foreach (item* var, who->itemlist.values()) {
            if(var->handle == "Blaster"){
                if(var->power==0){
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,playerlist->keys(),var->handle));
                    //who->actionlist.append(qMakePair(QString("ultBlaster"),playerlist->keys()));
                }
                continue;}
            if(var->handle == "Injector"){
                if(var->power==0){
                    who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->handle));
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,var->handle));
                    //who->actionlist.append(qMakePair(QString("useInjector"),playerlist->keys()));
                    //who->actionlist.append(qMakePair(QString("ultInjector"),tmp)); 
                }
                continue;
            }
            if(var->handle == "Notebook"){
                if(_currvoting->is_over!=true || hardresolve==true){
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,var->handle));
                    //who->actionlist.append(qMakePair(QString("ultNotebook"),tmp));}
                    if(var->power==0 && _currvoting->is_over!=true){
                        who->actionlist.append(TurnObject(TT_USE_ITEM,_currvoting->electlist,var->handle));
                        //who->actionlist.append(qMakePair(QString("useNotebook"),_currvoting->electlist));
                    }
                    continue;}
                if(var->handle == "Battery"){
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,brokeitemlist,var->handle));
                    //who->actionlist.append(qMakePair(QString("ultBattery"),brokeitemlist));
                    if(var->power==0){
                        QList<QString> gtr;
                        foreach (QString st, itemlist.keys()) {
                            if(st!="Badge" && st!="Rotation" && st!="Battery")
                                gtr.append(st);
                        }
                        who->actionlist.append(TurnObject(TT_USE_ITEM,gtr,var->handle));
                        //who->actionlist.append(qMakePair(QString("useBattery"),gtr));
                    }
                    continue;}
                if(var->handle == "Scanner"){
                    if(var->power==0){
                        who->actionlist.append(TurnObject(TT_ULT_ITEM,var->handle));
                        //who->actionlist.append(qMakePair(QString("ultScanner"),tmp));
                        
                        who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->handle));
                        //who->actionlist.append(qMakePair(QString("useScanner"),playerlist->keys()));
                    }
                    continue;}
                if(var->handle == "Badge"){
                    if(_currvoting->is_over==true && hardresolve==true){
                        who->actionlist.append(TurnObject(TT_USE_ITEM,_currvoting->winners,var->handle));
                        //who->actionlist.append(qMakePair(QString("useBadge"),_currvoting->winners));
                    }
                    if(var->power==0){
                        QList<QString> gtr;
                        foreach (QString st, itemlist.keys()) {
                            if(!brokeitemlist.contains(st)&&st!="Badge"&&st!="Rotation")
                                gtr.append(st);
                        }
                        who->actionlist.append(TurnObject(TT_ULT_ITEM,gtr,var->handle));
                        //who->actionlist.append(qMakePair(QString("ultBadge"),gtr));
                    }
                    continue;}
                if(var->handle == "Rotation"){
                    if(nightrotation.isEmpty()){
                        foreach (player* gr, playerlist->values()) {
                            gr->ImDuty=false;
                        }
                        QList<QString>deprole;
                        QList<QString>cand;//готовим список дежурных
                        deprole <<"Deputy of Doctor"<<"Deputy of Gunmen"<<"Deputy of Engineer"
                               <<"Deputy of Scientist"<<"Deputy of Signalmen"<<"Assistant";
                        foreach (player* it, playerlist->values()) {
                            if(it->ImDuty==false){
                                foreach (QString r, it->rolelist) {
                                    if(deprole.contains(r)&&(!cand.contains(it->name)&&
                                                             (!it->rolelist.contains("Captain")))){
                                        cand.append(it->name);
                                        //it->ImDuty=true;
                                    }
                                }
                            }
                        }
                        foreach (QString hth, passengerlist) {
                            if(playerlist->value(hth)->ImDuty==false){
                                cand.append(hth);
                                //it->ImDuty=true;
                            }
                        }
                        if(cand.count()<=1){
                            foreach (player* jt, playerlist->values()) {
                                if(!jt->rolelist.contains("Captain")&&(!cand.contains(jt->name)&&jt->ImDuty==false)){
                                    cand.append(jt->name);
                                    //jt->ImDuty=true;
                                }
                            }
                        }
                        who->actionlist.append(TurnObject(TT_USE_ITEM,cand,var->handle));
                        //who->actionlist.append(qMakePair(QString("useRotation"),cand));
                    }
                    continue;//если добавить дефолт, то там буде обработка ошибок
                }
                
            }
            if(_currvoting->is_over!=true){
                if(_currvoting->votelist.value(who->name).second==0)
                    who->actionlist.append(TurnObject(TT_VOTE,_currvoting->electlist));
                //who->actionlist.append(qMakePair(QString("vote"),_currvoting->electlist));
                if(_currvoting->votelist.value(who->name).second==1)
                    who->actionlist.append(TurnObject(TT_UNVOTE));
                //who->actionlist.append(qMakePair(QString("unvote"),tmp));
            }
            if(who->status==2){
                if(who->healthy==true)
                    who->actionlist.append(TurnObject(TT_DOWN));
                //who->actionlist.append(qMakePair(QString("down"),tmp));
                else
                    who->actionlist.append(TurnObject(TT_UP));
                //who->actionlist.append(qMakePair(QString("up"),tmp));
            }
        }
    }else{//если ночь
        if(who->waiting==false){
            who->actionlist.append(TurnObject(TT_SKIP));
            //who->actionlist.append(qMakePair(QString("wait"),tmp));
            if(who->use_night_item==false){
                foreach (item* var, who->itemlist.values()) {
                    if(var->handle == "Blaster"){
                        if(var->power==0){
                            who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->handle));
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,playerlist->keys(),var->handle));
                            //who->actionlist.append(qMakePair(QString("useBlaster"),playerlist->keys()));
                            //who->actionlist.append(qMakePair(QString("ultBlaster"),playerlist->keys()));
                        }
                        continue;}
                    if(var->handle == "Injector"){
                        if(var->power==0){
                            who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->handle));
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,var->handle));
                            //who->actionlist.append(qMakePair(QString("useInjector"),playerlist->keys()));
                            //who->actionlist.append(qMakePair(QString("ultInjector"),tmp));
                            
                        }
                        continue;}
                    if(var->handle == "Battery"){
                        if(!brokeitemlist.isEmpty())
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,brokeitemlist,var->handle));
                        //who->actionlist.append(qMakePair(QString("ultBattery"),brokeitemlist));
                        if(var->power==0){
                            QList <QString> tmp;
                            tmp.append(who->name);
                            who->actionlist.append(TurnObject(TT_USE_ITEM,var->handle));
                            //who->actionlist.append(qMakePair(QString("useBattery"),tmp));
                        }
                        continue;}
                    if(var->handle == "Scanner"){
                        if(var->power==0){
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,var->handle));
                            who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->handle));
                            //who->actionlist.append(qMakePair(QString("ultScanner"),tmp));
                            //who->actionlist.append(qMakePair(QString("useScanner"),playerlist->keys()));
                        }
                        continue;}
                    if(var->handle == "Badge"){
                        if(var->power==0){
                            QList <QString> iitemlist;
                            foreach (QString iitem, itemlist.keys()) {
                                if(iitem!="Rotation" && iitem!="Badge" && iitem!="Notebook"){
                                    iitemlist.append(iitem);
                                }
                            }
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,iitemlist,var->handle));
                            //who->actionlist.append(qMakePair(QString("ultBadge"),iitemlist));
                        }
                        continue;}
                    if(var->handle == "Mop"){
                        who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->handle));
                        //who->actionlist.append(qMakePair(QString("useMop"),playerlist->keys()));
                        continue;
                    }
                }
                
            }
            if(who->status==2)
            {
                if(who->attack_thisnight==false){
                    who->actionlist.append(TurnObject(TT_ATTACK,playerlist->keys()));
                    //who->actionlist.append(qMakePair(QString("attack"),playerlist->keys()));
                }
                if(who->infecting==false) {
                    if(who->invasion==0 || who->success_attack==2 ||
                            (who->success_attack==1 && who->attack_thisnight==true)){
                        who->actionlist.append(TurnObject(TT_INFECT,playerlist->keys()));
                        // who->actionlist.append(qMakePair(QString("infect"),playerlist->keys()));
                    }
                }
                if(who->healthy==true)
                    who->actionlist.append(TurnObject(TT_DOWN));
                //who->actionlist.append(qMakePair(QString("down"),tmp));
                else
                    who->actionlist.append(TurnObject(TT_UP));
                //who->actionlist.append(qMakePair(QString("up"),tmp));
            }
        }
        //тут возможна вставка автоматической отправки события wait, если игрок ничего не может сделать ночью
        if(who->actionlist.count()==1){
            who->actionlist.clear();
            who->waiting=true;
        }
        
        //emit send_actionlist(who);
    }
}

void game::day_check_over(){
    if(_currvoting->is_over==true && hardresolve==false){
        if (!votingque.isEmpty()){
            day_next_voting();
        } else {
            if(!nightrotation.isEmpty()||
                    (unclame_rolelist.contains("Captain")&&(unclame_rolelist.contains("Assistant")))){
                night_start();
            }else
                if(rolelist.value("Assistant")!=rolelist.value("Captain"))
                    emit GuiMess2Log("[Game]","Помощник капитана должен назначить график дежурств!");
                else
                    emit GuiMess2Log("[Game]","Капитан должен назначить график дежурств!");
        }
    }
}


void game::day(){
    //qDebug()<<"game::day()";
    if(makeNightActoins()){
        daytime=true;
        foreach (player* v, playerlist->values()) {
            check_HP(v);
        }
        currentday++;
        // _currvoting->is_over=true;
        
        emit GuiMess2Log("[Game]","Start Day "+QString::number(currentday));
        day_check_over();
    }else emit game_over();
}



void game::day_next_voting(){
    qDebug()<<"game::day_next_voting()";
    //voting* new_voting = votingque.dequeue();
    _currvoting = votingque.dequeue();
    //QPair<QString,int>  ttmp;
    _currvoting->votelist.clear();
    foreach (player* v,playerlist->values()) {
        _currvoting->votelist.insert(v->name,qMakePair(v->name,0));
    }
    foreach (QString trt, _currvoting->electlist) {
        if(!playerlist->contains(trt)){
            _currvoting->electlist.removeOne(trt);
        }
    }
    //_currvoting->electlist=new_voting->electlist;
    // _currvoting->votelist=new_voting->votelist;
    //_currvoting->target=new_voting->target;
    
    connect (_event,SIGNAL(event_useitem(QString,QString,QString)),_currvoting,SLOT(use_notebook(QString,QString,QString)));
    connect (_event,SIGNAL(event_ultitem(QString,QString,QString)),_currvoting,SLOT(ult_notebook(QString,QString,QString)));
    
    connect (_event,SIGNAL(event_vote(QString,QString)),_currvoting,SLOT(on_voting(QString,QString)));
    connect (_event,SIGNAL(event_unvote(QString)),_currvoting,SLOT(off_voting(QString)));
    //connect (_event,SIGNAL(event_vote(QString,QString)),this,SLOT(slot_vote(QString,QString)));
    //connect (_event,SIGNAL(event_unvote(QString)),this,SLOT(slot_unvote(QString)));
    
    connect (_currvoting,SIGNAL(voting_over(QList<QString>)),this,SLOT(day_resolve_curr_voting(QList<QString>)));
    connect (_currvoting,SIGNAL(voting_canseled()),this,SLOT(day_canseled_voting()));
    foreach (player* var, playerlist->values()) {
        make_actionlist(var);
    }
    
    if(_currvoting->target=="Alien")emit GuiMess2Log("[Game]","Выбираем цель диагностической операции");
    else emit GuiMess2Log("[Game]","Голосование на передачу должности: "+_currvoting->target);
    
}


void game::day_cap_curr_voting(QString who,QString win,QString useit){
    qDebug()<<"game::day_cap_curr_voting";
    if(playerlist->value(who)->rolelist.contains("Captain")
            && useit=="Badge"
            && _currvoting->winners.contains(win)){
        day_end_curr_voting(win);
        emit GuiMess2Log("[Game]","Капитан отдал решающий голос в пользу "+win);
    }
}

void game::day_end_curr_voting(QString winner){
    qDebug()<<"game::day_end_curr_voting(QString winner)";
    //тут отправка игрокам сообщения
    if (playerlist->contains(winner)){
        player* win = playerlist->value(winner);
        if (_currvoting->target=="Alien"){
            if(win->status<2){
                //игрок - человек
                emit GuiMess2Log("[Game]","Игрок "+winner+" - человек");
                win->HP=win->HP-1;
                if(win->status==1){
                    //оповещение об изъятии эмбриона
                    win->status=0;
                    win->invasion=-1;
                    emit GuiMess2Log("[Game]","Из игрока "+winner+" извлечен эмбрион");
                    //win->itemlist.remove("Fetus");
                }
                //                if(win->HP>0){
                //                    win->healthy=false;
                //                    make_events(win->name,"down","","");
                //                }
                //                else player_death(win);
                check_HP(win);
            }
            if(win->status==2){
                //оповещение о том, что игрок - чужой
                emit GuiMess2Log("[Game]","Игрок "+winner+" - чужой!");
                player_death(win);
            }
        }
        else{
            //оповещение о присуждении роли
            add_role(win,_currvoting->target);
        }
    }
    foreach (player* var, playerlist->values()) {
        make_actionlist(var);
    }
    _currvoting->is_over=true;
    hardresolve=false;
    disconnect (_event,SIGNAL(event_useitem(QString,QString,QString)),_currvoting,SLOT(use_notebook(QString,QString,QString)));
    disconnect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(day_cap_curr_voting(QString,QString,QString)));
    
    disconnect (_event,SIGNAL(event_ultitem(QString,QString,QString)),_currvoting,SLOT(ult_notebook(QString,QString,QString)));
    
    disconnect (_currvoting,SIGNAL(voting_over(QList<QString>)),this,SLOT(day_resolve_curr_voting(QList<QString>)));
    disconnect (_currvoting,SIGNAL(voting_canseled()),this,SLOT(day_canseled_voting()));
    
    day_check_over();
}


void game::day_resolve_curr_voting(QList<QString> win){
    
    qDebug()<<"game::day_resolve_curr_voting(QList<QString> win)";
    
    emit GuiMess2Log("[Game]","Подсчет голосов завершен");
    disconnect (_event,SIGNAL(event_vote(QString,QString)),_currvoting,SLOT(on_voting(QString,QString)));
    disconnect (_event,SIGNAL(event_unvote(QString)),_currvoting,SLOT(off_voting(QString)));
    _currvoting->is_over=true;
    if(win.count()==1){
        day_end_curr_voting(win.first());
    }
    if(win.count()>1){
        connect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(day_cap_curr_voting(QString,QString,QString)));
        //тут будет предложение капитану определить итог голосования лично
        emit GuiMess2Log("[Game]","Капитан должен сделать решающий выбор");
        hardresolve=true;
        
    }
    
    foreach (player* var, playerlist->values()) {
        make_actionlist(var);
    }
    
}


void game::day_canseled_voting(){
    qDebug()<<"game::day_canseled_voting()";
    //тут будет сообщение игрокам об отмене голосования
    
    emit GuiMess2Log("[Game]","Голосование было отменено по техническим причинам!");
    _currvoting->is_over=true;
    disconnect (_event,SIGNAL(event_vote(QString,QString)),_currvoting,SLOT(on_voting(QString,QString)));
    disconnect (_event,SIGNAL(event_unvote(QString)),_currvoting,SLOT(off_voting(QString)));
    disconnect (_event,SIGNAL(event_useitem(QString,QString,QString)),_currvoting,SLOT(use_notebook(QString,QString,QString)));
    disconnect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(day_cap_curr_voting(QString,QString,QString)));
    disconnect (_event,SIGNAL(event_ultitem(QString,QString,QString)),_currvoting,SLOT(ult_notebook(QString,QString,QString)));
    disconnect (_currvoting,SIGNAL(voting_over(QList<QString>)),this,SLOT(day_resolve_curr_voting(QList<QString>)));
    disconnect (_currvoting,SIGNAL(voting_canseled()),this,SLOT(day_canseled_voting()));
    foreach (player* var, playerlist->values()) {
        make_actionlist(var);
    }
    
    day_check_over();
}

void game::slot_game_over(){
    
    if(playerlist->begin().value()->status==0){
        //отправка всем сообщение о победе людей
        emit GuiMess2Log("[Game]","Игра завершена победой людей!");
    } else {
        //отправка всем сообщения о победе чужих
        emit GuiMess2Log("[Game]","Игра завершена победой чужих!");
    }
    //статистика, ачивки, прочее дерьмо
}

bool game::night(){
    qDebug()<<"game::night()";
    foreach (player* v, playerlist->values()){
        make_actionlist(v);
        if(v->waiting==false){
            return false;
        }
    }
    return true;
}

void game::night_start(){
    emit GuiMess2Log("[Game]","Началась ночь "+QString::number(currentday));
    qDebug()<<"game::night_start()";
    daytime=false;
    mopper="";
    while(mopper==""){
        if(!nightrotation.isEmpty()){
            mopper = nightrotation.dequeue();
            if(!playerlist->keys().contains(mopper)) mopper="";
        }else break;
    }
    if(mopper!=""){
        emit GuiMess2Log("[Game]","Сегодня дежурит "+mopper);
        item* bb=new Mop(this);
        bb->power=0;
        playerlist->value(mopper)->itemlist.insert("Mop",bb);
        itemlist.insert("Mop",bb);
    } else emit GuiMess2Log("[Game]","Сегодня никто не дежурит");
    
    foreach (player* v, playerlist->values()) {
        if(v->healthy==false){
            v->simplebath=true;
        }
        v->waiting=false;
        v->attack_thisnight=false;
        v->use_night_item=false;
        v->infecting=false;
        make_actionlist(v);
    }
}

void game::StartRandomEvasion(){
    //qDebug()<<"game::StartRandomEvasion()";
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    int sizeoflist=playerlist->count();
    int a1=qrand()%(sizeoflist);//первый чужой
    QString A1;
    int a2=0;
    int a3;//первый зараженный
    int a4;//первый раненый
    while(true){
        a3=qrand()%(sizeoflist);
        a4=qrand()%(sizeoflist);
        if(a1!=a3 && a1!=a4)break;
    }
    
    foreach (player* var, playerlist->values()) {
        if(a2==a1){
            ingame_event* _eve=new ingame_event(var->name,var->name,"alien","");
            _nightque.enqueue(_eve);
            A1=var->name;
            var->invasionday=-1;
        }
        a2++;
    }
    
    a2=0;
    foreach (player* var, playerlist->values()) {
        if(a2==a4){
            var->HP=1;
        }
        if(a2==a3){
            var->status=1;
            var->invasion=2;
            ingame_event* _eve=new ingame_event(A1,var->name,"infect","");
            _nightque.enqueue(_eve);
        }
        a2++;
    }
    
}

void game::StartRandomEvasion_testing(){
    //qDebug()<<"game::StartRandomEvasion()";
    // QTime midnight(0,0,0);
    // qsrand(midnight.secsTo(QTime::currentTime()));
    //    int sizeoflist=playerlist->count();
    //    int a1=qrand()%(sizeoflist);//первый чужой
    //    int a2=0;
    //    int a3;//первый зараженный
    //    int a4;//первый раненый
    //    while(true){
    //        a3=qrand()%(sizeoflist);
    //        a4=qrand()%(sizeoflist);
    //        if(a1!=a3 && a1!=a4)break;
    //    }
    
    //    foreach (player* var, playerlist->values()) {
    //        if(a2==a4){
    //            var->HP=1;
    //        }
    //        if(a2==a3){
    //            ingame_event* _eve=new ingame_event(var->name,var->name,"infect","");
    //            _nightque.enqueue(_eve);
    //        }
    //        if(a2==a1){
    //            ingame_event* _eve=new ingame_event(var->name,var->name,"alien","");
    //            _nightque.enqueue(_eve);
    //        }
    //        a2++;
    //    }
    
    //playerlist->value("1")  //капитан
    //playerlist->value("2")  //доктор
    //playerlist->value("3")  //боевик
    //playerlist->value("4")  //старпом
    //playerlist->value("5")  //инженер
    //playerlist->value("6")  //ученый
    //playerlist->value("7")  //связист
}

void game::slot_attack(TurnObject TO){
    qDebug()<<"game::slot_attack"<<who<<" "<<whom;
    GuiMess2Log(who,"атаковал игрока "+whom);
    if(TO.wh->HP < 5) TO.wh->HP += 1;
    playerlist->value(TO.targets.dequeue())->HP -= 2;
    if(TO.wh->success_attack < 2) 
        playerlist->value(who)->success_attack += 1;
    
    if(TO.wh->success_attack == 2){
        if(TO.wh->invasion == -1){
            TO.wh->invasion = 0;
        }
        // playerlist->value(who)->success_attack=0;
    }
    make_actionlist(TO.wh);
}

void game::slot_infect(TurnObject TO){
    qDebug()<<"game::slot_infect(QString who, QString whom)";
    if(TO.wh->status == 2 && TO.wh->invasion == 0){
        qDebug()<<who<<" заражает игрока "<<whom;
        TO.wh->invasion = -1;
        TO.wh->success_attack = 0;
        GuiMess2Log(who,"заражает игрока "+whom);
        player* whom = playerlist->value(TO.targets.dequeue());
        if(whom->status < 2){
            whom->status = 1;
            whom->invasionday = currentday;
            whom->invasion = 2;
            whom->whoinvas = TO.wh;
        }
        if(whom->status == 2){
            GuiMess2Log(whom,"поглощает эмбрион");
            whom->HP += 2;
            check_HP(whom);
        }
    }
    make_actionlist(TO.wh);
}

void game::slot_getitem(QString who,QString useit,QString power){
    qDebug()<<"game::slot_getitem(QString who,QString useit,QString power)";
    foreach (player* var, playerlist->values()) {
        if(var->itemlist.contains(useit)){
            var->itemlist.remove(useit);
        }
    }
    itemlist.value(useit)->power=power.toInt();
    playerlist->value(who)->itemlist.insert(useit,itemlist.value(useit));
    make_actionlist(playerlist->value(who));
}

void game::slot_alien(TurnObject TO){
    qDebug()<<"game::slot_alien("+who+")";
    GuiMess2Log(who,"осознался");
    
    TO.wh->status = 2;
    TO.wh->invasion = -1;
    TO.wh->HP += (TO.wh->HP - 1);
    TO.wh->success_attack = 1;
    
    make_actionlist(TO.wh);
}

void game::slot_vote(QString who,QString whom){
    qDebug()<<"game::slot_vote(QString who,QString whom)";
    foreach (player* var, playerlist->values()) {
        make_actionlist(var);
    }
}
void game::slot_unvote(QString who){
    //qDebug()<<"game::slot_unvote(QString who)";
    foreach (player* var, playerlist->values()) {
        make_actionlist(var);
    }
}



void game::slot_wait(TurnObject TO){
    qDebug()<<"game::slot_wait "<<who;
    GuiMess2Log(who,"ждет");
    if(TO.wh->waiting == true)
        TO.wh->waiting == false;
    make_actionlist(TO.wh);
}

void game::slot_up(TurnObject TO){
    qDebug()<<"game::slot_up "<<who;
    TO.wh->healthy = true;
    make_actionlist(TO.wh);
    if(daytime)
        emit GuiMess2Log(who,"встал из биованны");
}

void game::slot_down(TurnObject TO){
    qDebug()<<"game::slot_down "<<who;
    TO.wh->healthy = false;
    make_actionlist(TO.wh);
    if(daytime)
        emit GuiMess2Log(who,"в биованне");
}


void game::add_role(player* whom,QString what){
    qDebug()<<"game::add_role(player* whom,QString what)";
    emit GuiMess2Log("[Game]","Роль "+what+" отдата игроку "+whom->name);
    if(unclame_rolelist.contains(what))unclame_rolelist.removeOne(what);
    rolelist.insertMulti(what,whom);
    whom->rolelist.append(what);
    foreach (item* var, itemlist.values()) {
        if(var->role==what){
            whom->itemlist.insert(var->handle,var);
        }
    }
    make_actionlist(whom);
}

void game::delete_role(player* whom,QString what){
    qDebug()<<"game::delete_role(player* whom,QString what)";
    QList<QString>mainrole;
    mainrole <<"Captain"<<"Gunmen"<<"Engineer"
            <<"Scientist"<<"Signalmen"<<"Assistant"<<"Doctor";
    emit GuiMess2Log("[Game]","Игрок "+whom->name+ "потерял роль "+what);
    rolelist.remove(what,whom);
    if(rolelist.count(what)==0)rolelist.remove(what);
    whom->rolelist.removeOne(what);
    foreach (item* var, itemlist.values()) {
        if(var->role==what){
            whom->itemlist.remove(var->handle);
        }
    }
    if(mainrole.contains(what)){
        unclame_rolelist.append(what);
    }
    if(whom->rolelist.isEmpty()){
        passengerlist.append(whom->name);
        if(whom->ImDuty==false){
            nightrotation.enqueue(whom->name);
            whom->ImDuty=true;
        }
    }
    make_actionlist(whom);
}

void game::slot_use_item(QString who,QString whom,QString useit){
    qDebug()<<"game::slot_use_item "<<who<<" "<<whom<<" "<<useit;
    GuiMess2Log(who,"использовал "+useit+" на "+whom);
    player* _who=playerlist->value(who);
    player* _whom=playerlist->value(whom);
    
    if(_who->itemlist.value(useit)->power==0 && useit!="Rotation" && useit!="Badge"){
        if(daytime){
            _who->itemlist.value(useit)->use_item_day(whom);
        }
        else {
            _who->itemlist.value(useit)->use_item_night(whom);
        }
        if(_who->status<2 && _who->healthy==false){
            _who->HP-=1;
            check_HP(_who);
        }
    }//нужно обдумать использование и переписать!!
    if(useit=="Rotation"){
        _who->itemlist.value(useit)->rotation=nightrotation;
        if(_currvoting->is_over==true && hardresolve==false)
            day_check_over();
    }
    make_actionlist(playerlist->value(who));
}

void game::slot_use_item_cap(QString who,QString whom,QString useit){
    //qDebug()<<"game::slot_use_item_cap(QString who,QString whom,QString useit)";
    //player* _who=playerlist->value(who);
    //player* _whom=playerlist->value(whom);
    GuiMess2Log(who," как капитан, использовал "+useit+" на "+whom);
    if(playerlist->value(who)->itemlist.value("Badge")->power!=-1){
        if(itemlist.value(useit)->power==0){
            if(daytime==true)
                itemlist.value(useit)->use_item_day(whom);
            else itemlist.value(useit)->use_item_night(whom);
            if(playerlist->value(who)->status<2 && playerlist->value(who)->healthy==false){
                playerlist->value(who)->HP-=1;
                check_HP(_who);
            }
            playerlist->value(who)->itemlist.value("Badge")->power=-1;
        }
    }
    make_actionlist(playerlist->value(who));
}

void game::slot_ult_item(QString who,QString whom,QString useit){
    QStringList target;
    if(whom!="")
        target.append(whom);
    TurnObject TO(TT_ULT_ITEM,target,useit);
    qDebug()<<"game::slot_ult_item "<<who<<" "<<whom<<" "<<useit;
    GuiMess2Log(who,"ультанул "+useit+"ом");
    
    //ingame_event*_eve=new ingame_event(who,whom,"useult",useit);
    if(make_events_check(who,TO)){
        player* _who=playerlist->value(who);
        _who->itemlist.value(useit)->ult_item(whom);
        brokeitemlist.append(useit);
        // _who->rolelist.removeOne(itemlist.value(useit)->role);
        // _who->itemlist.remove(useit);
        // if(_who->rolelist.isEmpty()){
        //     passengerlist.append(who);
        //     nightrotation.enqueue(who);
        // }
        
        delete_role(_who,itemlist.value(useit)->role);
        if(_who->status<2 && _who->healthy==false){
            _who->HP-=1;
            check_HP(_who);
        }
    }
    foreach (player* iy, playerlist->values()) {
        make_actionlist(iy);
    }
    
    
    
}


void game::make_events(int wwh,QString what,QString whom,QString how,QQueue<QString> rota){
    //player* _who,_whom;
    //item _how;
    QString who = connectedName.value(wwh);
    qDebug()<<"game::make_events "<<who<<" "<<what<<" "<<how<<" "<<whom<<" "<<rota;
    ingame_event* new_event=new ingame_event(who,whom,what,how,rota);
    if (this->daytime){
        
        //_event=new_event;
        _event->who=who;
        _event->whom=whom;
        _event->what=what;
        _event->useit=how;
        _event->rota=rota;
        if(make_events_check(_event)){
            if(nightrotation.isEmpty()){
                nightrotation=rota;
                foreach (player* gtr, playerlist->values()){
                    if(nightrotation.contains(gtr->name)){
                        gtr->ImDuty=true;
                    }
                }
            }
            do_event();
            make_actionlist(playerlist->value(who));
        }
    } else {
        if(make_events_check(new_event)){
            _nightque.enqueue(new_event);
            make_actionlist(playerlist->value(who));
            if(what=="wait"){
                playerlist->value(who)->waiting=true;
            }
            if(night()==true){
                //тут отправка сообщения об окончании ночи
                day();
            }
        }
    }
}

bool game::make_events_check(QString who, TurnObject TO){
    qDebug()<<"game::make_events_check";
    QString check_first,check_second;
    if(!playerlist->contains(who))
        return false;
    
    //if(_event->whom!="")check_second=_event->whom;
    if(_event->whom!="")
        TO.targets.append(_event->whom);
    
    if(_event->what=="useitem"){
        check_first="use"+_event->useit;
    } else
        if(_event->what=="useult"){
            check_first="ult"+_event->useit;
        } else
            if (_event->what=="useitemCap"){
                check_first="ultBadge";
                check_second=_event->useit;
            }
            else
            {
                check_first = _event->what;
            }
    if(check_first=="down"){
        if (playerlist->value(_event->who)->healthy!=false)
            return true;
        else return false;
    }
    if(check_first=="up"){
        if (playerlist->value(_event->who)->healthy!=true)
            return true;
        else return false;
    }
    QPair <QString,QList<QString> > tmp;
    foreach (tmp, playerlist->value(_event->who)->actionlist) {
        if (tmp.first==check_first){
            if(!tmp.second.isEmpty() && check_first!="useRotation"){
                if(tmp.second.contains(check_second))return true;
                else return false;
            }else return true;//тут проверка роты
        }
    }
    return false;
}

void game::make_events(int wwh,QString what,QString whom,QString how){
    //player* _who,_whom;
    //item _how;
    QString who = connectedName.value(wwh);
    qDebug()<<"game::make_events "<<who<<" "<<what<<" "<<how<<" "<<whom;
    ingame_event* new_event=new ingame_event(who,whom,what,how);
    if (this->daytime){
        
        //_event=new_event;
        _event->who=who;
        _event->whom=whom;
        _event->what=what;
        _event->useit=how;
        if(make_events_check(_event)){
            do_event();
            make_actionlist(playerlist->value(who));
        }
    } else {
        if(make_events_check(new_event)){
            _nightque.enqueue(new_event);
            if(what=="attack"){
                new_event->wh= playerlist->value(who);
                playerlist->value(who)->attack_thisnight=true;
            }
            if(what=="useitem"||what=="useult"||what=="useitemCap")
                playerlist->value(who)->use_night_item=true;
            if(what=="wait"){
                playerlist->value(who)->waiting=true;
            }
            if(what=="infect"){
                playerlist->value(who)->invasion=-1;
                playerlist->value(who)->infecting=true;
            }
            if(what=="up"){
                //playerlist->value(who)->healthy=true;
                slot_up(who);
            }
            if(what=="down"){
                //playerlist->value(who)->healthy=false;
                slot_down(who);
            }
            make_actionlist(playerlist->value(who));
            if(night()){
                
                //тут отправка сообщения об окончании ночи
                day();
            }
        }
    }
    
}



bool game::makeNightActoins(){//true - продолжать игру, false - game over
    qDebug()<<"game::makeNightActoins()";
    sortNightActions();
    QQueue <ingame_event*> _night = _nightque;
    while(!_nightque.isEmpty()){
        ingame_event* _eve=_nightque.dequeue();
        _event->what=_eve->what;
        _event->who=_eve->who;
        _event->whom=_eve->whom;
        _event->useit=_eve->useit;
        //     _event->rota=_eve->rota;
        
        
        //_event=_nightque.dequeue();
        if(playerlist->keys().contains(_event->who))
            do_event();
    }
    
    foreach (player* it, playerlist->values()) {
        if(it->HP<=0){
            player_death(it);
            continue;
        }
        
        if(it->simplebath==true && it->healthy==false){
            it->HP+=1;
        }
        if(it->status==1){
            it->invasion-=1;
            if(it->invasion==0){
                slot_alien(it->name);
            }
        }
        it->itemlist.remove("Mop");
    }
    itemlist.remove("Mop");//скорее всего нужно будет удалить и сам объект из памяти
    foreach (item*ii, itemlist.values()) {
        ii->counter();
    }
    
    emit send_nightmare(_night,playerlist->values());
    if (playerlist->count()>1){
        foreach (player* v, playerlist->values()) {
            if (v->status>=1){
                votingque.enqueue(new voting(playerlist->keys(),playerlist->keys(),"Alien"));
                return true;
            }
        }
        return false;//все здоровы, чужих больше нет
    } else {
        if(playerlist->begin().value()->status!=1)
            return false;
    }//остался последний игрок, или больше никого не осталось.
}

void game::register_new_player(int tempname,QString name,QString avatar){
    if(!playerlist->contains(name)){
        connectedName.insert(tempname,name);
        player* noob = new player(name,tempname);
        playerlist->insert(name,noob);
        //playerlist->value(name)->avatar=avatar.toInt();
        emit namecorrect(tempname);
    }else//подумал, возможно замена не нужна
        emit nonamecorrect(tempname);
    slotSendRolelist();
    
    emit GuiUpdatePlayerlist(playerlist->values());
}

void game::slotSendRolelist(){
    emit sendrolelist2all(playerlist->values());
}

void game::slot_disconnected(int na){
    if(connectedName.contains(na)){
        QString name = connectedName.value(na);
        foreach (QString var,playerlist->value(name)->rolelist){
            playerlist->value(name)->rolelist.removeOne(var);
            unclame_rolelist.append(var);
        }
        playerlist->remove(name);
        connectedName.remove(na);
    }
    slotSendRolelist();
    emit GuiUpdatePlayerlist(playerlist->values());
}

void game::registerRolebyPlayer(int _na, QString role){
    QString _name = connectedName.value(_na);
    if(role!="Passenger"){
        if(playerlist->value(_name)->rolelist.isEmpty())
        {
            if(unclame_rolelist.contains(role)){
                unclame_rolelist.removeOne(role);
                rolelist.insertMulti(role,playerlist->value(_name));
                playerlist->value(_name)->rolelist.append(role);
                passengerlist.removeOne(_name);
                emit rolecorrect(_na);
            }else norolecorrect(_na);
        }else{
            unclame_rolelist.removeOne(role);
            foreach (QString var,playerlist->value(_name)->rolelist){
                playerlist->value(_name)->rolelist.removeOne(var);
                unclame_rolelist.append(var);
            }
            playerlist->value(_name)->rolelist.append(role);
            emit rolecorrect(_na);
        }
        
        if(unclame_rolelist.count()==0){
            unclame_rolelist.append("Dep_Doctor");
            unclame_rolelist.append("Dep_Gunmen");
            unclame_rolelist.append("Dep_Engineer");
            unclame_rolelist.append("Dep_Scientist");
            unclame_rolelist.append("Dep_Signalmen");
            
        }
    }else{
        passengerlist.append(_name);
        playerlist->value(_name)->rolelist.append(role);
        emit rolecorrect(_na);
    }
    slotSendRolelist();
    emit GuiUpdatePlayerlist(playerlist->values());
    
    QList <QString> mainrole;//проверка на запуск новой сессии (заняты ли все основные роли)
    mainrole <<"Captain"<<"Doctor"<<"Signalmen"<<"Gunmen"<<"Assistant"<<"Engineer"<<"Scientist";
    bool check=true;
    foreach (QString var, mainrole) {
        if (unclame_rolelist.contains(var))check=false;
    }
    emit startnewsessionenable(check);
}

void game::player_death(player* dead){
    qDebug()<<"game::player_death(player* dead)";
    //тут будет отправка о том что игрок мертв
    emit GuiMess2Log("[Game]","Погиб игрок "+dead->name);
    QList <QString> mainroles;
    mainroles << "Captain"<<"Doctor"<<"Gunmen"<<"Assistant"<<"Engineer"<<"Scientist"<<"Signalmen";
    playerlist->remove(dead->name);
    foreach (QString var, rolelist.uniqueKeys()) {
        foreach (player* v, rolelist.values(var))
            if(v==dead){
                
                
                if(mainroles.contains(var)){
                    unclame_rolelist.append(var);
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
    if(_currvoting->is_over==false){
        _currvoting->electlist.removeOne(dead->name);
        _currvoting->votelist.remove(dead->name);
        if(_currvoting->electlist.count()==1){
            _currvoting->send_voting_over(_currvoting->electlist);
        }
    }
    if(hardresolve==true){
        _currvoting->winners.removeOne(dead->name);
        if(_currvoting->winners.count()==1){
            day_end_curr_voting(_currvoting->winners.first());
        }
    }
    emit GuiUpdatePlayerlist(playerlist->values());
}

void game::check_HP(player* w){   
    if(w->status<=1){//для людей и зараженных
        if(w->HP>=3){
            w->HP=3;
            if(w->healthy==false){
                slot_up(who);
            }
        }
        if(w->HP<=0){
            if(w->itemlist.contains("Injector")){
                if(w->itemlist.value("Injector")->power==0){
                    w->HP=2;
                }
            } else player_death(w);
        }
        if(w->HP<3 && w->HP>0){
            if(w->healthy==true){
                slot_down(who);
            }
        }
    }
    if(w->status==2){//для чужих
        if(w->HP>=5){
            w->HP=5;
            if(daytime && w->healthy==false){
                slot_up(who);
            }
        }
        //            if(w->HP>0 && w->HP<5){
        //                if(w->healthy==true){
        //                    slot_down(who);
        //                }
        //            }
        else
            if(w->HP>0&&w->HP<5){
                if(daytime && w->healthy==true){
                    slot_down(who);
                }
            }
            else{
                if(w->HP<=0){
                    if(w->itemlist.contains("Injector")){
                        if(w->itemlist.value("Injector")->power==0){
                            w->HP=2;
                        }
                    }else
                        if(w->invasion==0){
                            //тут будет отправка игроку сообщения об автоматическом поглощении эмбриона
                            w->invasion=-1;
                            w->HP=2;
                        }
                        else
                            player_death(w);
                }
            }
    }
}

void game::check_for_role_capDecision(QString who,QString whom,QString useit){//капитан выбирает старпома из числа пассажиров
    if(playerlist->value(who)->rolelist.contains("Captain") && useit=="Badge" && hardresolve==false){
        disconnect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(check_for_role_capDecision(QString,QString,QString)));
        if(playerlist->contains(whom) && passengerlist.contains(whom)){
            add_role(playerlist->value(whom),"Assistant");
        }else{
            check_for_role("Assistant");
        }
    }
}

void game::check_for_role(QString role){//передача роли заместителям или кому придется, заодно добавление голосований если нужно
    //дописать то, что после капитана роль принимает на себя заместитель и наоборот!
    //вроде должно сработать. пока не отражено, что капитан назначает первого помощника сам.
    qDebug()<<"game::check_for_role(QString role)";
    QMap <QString,QString>deprole;
    deprole.insert("Doctor","Deputy of Doctor");
    deprole.insert("Gunmen","Deputy of Gunmen");
    deprole.insert("Engineer","Deputy of Engineer");
    deprole.insert("Scientist","Deputy of Scientist");
    deprole.insert("Signalmen","Deputy of Signalmen");
    //deprole.insert("Captain","Assistant");
    deprole.insert("Assistant","Captain");
    
    if(role=="Assistant" && (!unclame_rolelist.contains("Captain"))){
        //тут отправка капитану сообщения о том что он должен назначить персонажа-старпома
        //QList<QString> forAssistant;
        if(passengerlist.count()==0){
            add_role(rolelist.value("Captain"),role);
        }else{
            connect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(check_for_role_capDecision(QString,QString,QString)));
        }
    }else{
        int co = rolelist.count(deprole.value(role));
        if(co==1){
            //тут будет отправка сообщения о присвоении роли единственному заму
            add_role(rolelist.value(deprole.value(role)),role);
            if(role!="Captain" && role !="Assistant")delete_role(rolelist.value(deprole.value(role)),deprole.value(role));
        }
        if(co>1){
            //начало голосования среди замов роли
            QList <QString> tmp;
            foreach (player* vvv, playerlist->values()) {
                if(vvv->rolelist.contains(deprole.value(role))){
                    tmp.append(vvv->name);
                }
            }
            votingque.enqueue(new voting(playerlist->keys(),tmp,role));
        }
        if(co==0){
            //QList <player*> cc;
            QList<QString>cc;
            foreach (QString var, deprole.values()) {
                foreach (player* vvv, playerlist->values()) {
                    if(vvv->rolelist.contains(deprole.value(var))){
                        if(var!="Captain" && var!="Assistant")
                            cc.append(vvv->name);
                    }
                }
                // cc.append(rolelist.values(var));
            }
            cc.append(passengerlist);
            if(cc.count()>1){
                votingque.enqueue(new voting(playerlist->keys(),cc,role));
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
                    add_role(playerlist->value(passengerlist.first()),role);
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
                    add_role(playerlist->value(cc.first()),role);
                } else {
                    votingque.enqueue(new voting(playerlist->keys(),cc,role));
                }
            }
            
        }
    }
}

void game::sortNightActions(){
    qDebug()<<"game::sortNightActions()";
    QQueue<ingame_event*>_queue=_nightque;
    qSort(_queue.begin(),_queue.end(),qLe());
    QQueue<ingame_event*>_que;
    QList <QString> playerblock; //игроки, чьи действия или действия на которых заблокированы
    QList <QString> playeritemuse;//игроки, пользовавшиеся предмеами этой ночью
    QString itblok;//предмет, использованный капитаном
    QList <QString> playerhunt;//игроки, попадающие под защиту боевика
    QList <QString> attackedhuman;//атакованные чужими люди
    //QList<ingame_event*>::iterator i;
    while (!_queue.isEmpty()) {
        ingame_event* _eve=_queue.dequeue();
        
        if(_eve->what=="wait"){
            _que.enqueue(_eve);
            continue;
        }
        if((playerlist->value(_eve->who)->healthy==false)&&(_eve->what=="up"||(_eve->what=="useitem")
                                                            ||(_eve->what=="useitemCap")||(_eve->what=="useult")
                                                            ||(_eve->what=="attack")||(_eve->what=="infect"))){
            playerlist->value(_eve->who)->simplebath=false;
        }
        if(_eve->what=="alien"||_eve->what=="up"||_eve->what=="down"
                ||_eve->what=="getitem"||_eve->what=="delitem"){
            _que.enqueue(_eve);
            continue;
        }
        if(((playerblock.contains(_eve->who))||(playerblock.contains(_eve->whom)))
                &&((_eve->what=="useitem")||(_eve->what=="useitemCap")||(_eve->what=="useult")||(_eve->what=="attack")
                   ||(_eve->what=="infect"))){
            continue;
        }
        bool AAA = playerhunt.contains(_eve->who);
        bool BBB = playerhunt.contains(_eve->whom);
        if(((!AAA&&BBB)||(!BBB&&AAA))//адская замена ксору
                &&((_eve->what=="useult")||(_eve->what=="attack")
                   ||(_eve->what=="infect"))){
            playerlist->value(_eve->who)->HP-=2;
            continue;
        }
        if(_eve->what=="useitemCap"
                && playerlist->value(_eve->who)->itemlist.value("Badge")->power==0
                && itemlist.value(_eve->useit)->power==0){
            if(_eve->useit=="Mop"){
                if(!playerlist->value(_eve->whom)->rolelist.contains("Doctor")){
                    playerblock.append(_eve->whom);
                }
            }
            if(_eve->useit=="Battery"){
                playerblock.append(_eve->who);
            }
            if(_eve->useit=="Blaster"){
                playerhunt.append(_eve->whom);
                if(playerlist->value(_eve->whom)->healthy==false){
                    foreach (player* vavar, playerlist->values()) {
                        if(vavar->healthy==false && vavar->name!=_eve->whom)playerhunt.append(vavar->name);
                    }
                }
                playerhunt.append(_eve->who);
            }
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who);
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
        
        if((_eve->what=="useitem")&&(_eve->useit=="Battery")){
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who);
            playerblock.append(_eve->who);
            continue;
        }
        if((_eve->what=="useitem")&&(_eve->useit=="Blaster")){
            _que.enqueue(_eve);
            playeritemuse.append(_eve->who);
            if(playerlist->value(_eve->whom)->healthy==false){
                foreach (player* vavar, playerlist->values()) {
                    if(vavar->healthy==false)playerhunt.append(vavar->name);
                }
            }else playerhunt.append(_eve->whom);
            playerhunt.append(_eve->who);
            continue;
        }
        
        if((_eve->what=="useult")&&(_eve->useit=="Battery")){
            playeritemuse.append(_eve->who);
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
            if(playerlist->value(_eve->whom)->status!=2){
                attackedhuman.append(_eve->whom);}
            _que.enqueue(_eve);
            continue;
        }
        if(_eve->what=="infect"){
            _que.enqueue(_eve);
            continue;
        }
        
        
        
    }
    _nightque=_que;
}

void game::do_events(TurnObject TO){
    switch (TO->type) {
    case TT_ALIEN:
        emit event_alien(this->who);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    case TT_USE_ITEM:
        emit event_useitem(this->who,this->whom,this->useit);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    case TT_ATTACK:
        emit event_attack(this->who,this->whom);
        break;
    default:
        break;
    }
    
    
    if(this->what=="useitem")
    {
        //if(rota.isEmpty())
        emit event_useitem(this->who,this->whom,this->useit);
        //else emit event_useitemrot(this->rota);
    }
    
    if(this->what=="useitemCap")
    {emit event_useitemcap(this->who,this->whom,this->useit);}
    
    if(this->what=="useult")
    {emit event_ultitem(this->who,this->whom,this->useit);}
    
    if(this->what=="wait")
    {emit event_wait(this->who);}
    
    if(this->what=="up")
    {emit event_up(this->who);}
    
    if(this->what=="down")
    {emit event_down(this->who);}
    
    if(this->what=="infect")
    {emit event_infect(this->who,this->whom);}
    
    if(this->what=="vote")
    {emit event_vote(this->who,this->whom);}
    
    if(this->what=="unvote")
    {emit event_unvote(this->who);}
    
    if(this->what=="getitem")
    {emit event_getitem(this->who,this->useit,this->whom);}//whom - заряд
}
