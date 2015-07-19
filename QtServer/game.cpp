#include "game.h"



class qLe
{
public:
    inline bool operator()(TurnObject& t1, TurnObject& t2) const
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
        
        if(t1.type == TT_ATTACK && t2.type == TT_ATTACK){
            if(t1.wh->HP < t2.wh->HP){
                return false;
            }else{
                if (t1.wh->HP == t2.wh->HP){
                    if(t1.wh->invasionday < t2.wh->invasionday){
                        return false;
                    } else{
                        if(t1.wh->invasionday == t2.wh->invasionday){
                            if(t1.wh->whoinvas->invasionday < t2.wh->whoinvas->invasionday){
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
    if(daytime)
    {
        foreach (item* var, who->itemlist)
        {
            switch (var->ID) {
            case IT_BLASTER:
                if(var->power == 0)
                {
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,playerlist->keys(),var->ID));
                }
                break;
            case IT_INJECTOR:
                if(var->power == 0)
                {
                    who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->ID));
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,var->ID));
                }
                break;
            case IT_NOTEBOOK:
                if(!_currvoting->is_over || hardresolve)
                {
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,var->ID));
                    if(var->power == 0 && !_currvoting->is_over)
                    {
                        who->actionlist.append(TurnObject(TT_USE_ITEM,_currvoting->electlist,var->ID));
                    }
                }
                break;
            case IT_BATTERY:
                TurnObject turn1(TT_ULT_ITEM,IT_BATTERY);
                foreach (ITEM item, itemlist)
                {
                    if (itemlist[item]->power == -1)
                    {
                        turn1.targets.append(itemlist[item]->handle);
                    }
                }
                who->actionlist.append(turn1);


                if(var->power == 0)
                {
                    TurnObject turn2(TT_USE_ITEM,IT_BATTERY);
                    foreach (ITEM item, itemlist)
                    {
                        switch (item) {
                        case IT_BADGE:
                        case IT_ROTATION:
                        case IT_BATTERY:
                        case IT_FETUS:
                        case IT_MOP:
                            break;
                        default:
                            turn2.targets.append(itemlist[item]->handle);
                            break;
                        }

                    }
                    who->actionlist.append(turn2);
                }
                break;
            case IT_SCANNER:
                if(var->power == 0)
                {
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,var->ID));
                    who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->ID));
                }
                break;
            case IT_BADGE:
                if(_currvoting->is_over && hardresolve)
                {
                    who->actionlist.append(TurnObject(TT_USE_ITEM,_currvoting->winners,var->ID));
                }
                if(var->power == 0)
                {
                    TurnObject turn;
                    turn.type = TT_USE_BADGE;
                    foreach (ITEM item, itemlist)
                    {
                        if(!brokeitemlist.contains(item)){
                            switch (item) {
                            case IT_BATTERY:
                                turn.item = IT_BATTERY;
                                foreach (ITEM item1, itemlist)
                                {
                                    switch (item1) {
                                    case IT_BADGE:
                                    case IT_ROTATION:
                                    case IT_BATTERY:
                                    case IT_FETUS:
                                    case IT_MOP:
                                        break;
                                    default:
                                        turn.targets.append(itemlist[item1]->handle);
                                        break;
                                    }

                                }
                                who->actionlist.append(turn);
                                break;
                            case IT_BLASTER:
                            case IT_INJECTOR:
                            case IT_SCANNER:
                                turn.item = item;
                                turn.targets = playerlist->keys();
                                who->actionlist.append(turn);
                                break;
                            case IT_NOTEBOOK:
                                if(!_currvoting->is_over && !hardresolve)
                                {
                                    turn.item = IT_NOTEBOOK;
                                    turn.targets.append(_currvoting->electlist);
                                    who->actionlist.append(turn);
                                }
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
                break;
            case IT_ROTATION:
                if(nightrotation.isEmpty())
                {
                    foreach (player* gr, playerlist->values())
                    {
                        gr->ImDuty = false;
                    }
                    QList<QString>deprole;
                    QList<QString>cand;//готовим список дежурных
                    deprole <<"Deputy of Doctor"<<"Deputy of Gunmen"<<"Deputy of Engineer"
                           <<"Deputy of Scientist"<<"Deputy of Signalmen"<<"Assistant";
                    foreach (player* it, playerlist->values())
                    {
                        if(it->ImDuty == false){
                            foreach (QString r, it->rolelist)
                            {
                                if(deprole.contains(r)&&(!cand.contains(it->name) &&
                                                         (!it->rolelist.contains("Captain"))))
                                {
                                    cand.append(it->name);
                                }
                            }
                        }
                    }
                    foreach (QString hth, passengerlist)
                    {
                        if(playerlist->value(hth)->ImDuty == false)
                        {
                            cand.append(hth);
                        }
                    }
                    if(cand.count() <= 1)
                    {
                        foreach (player* jt, playerlist->values())
                        {
                            if(!jt->rolelist.contains("Captain")&&
                                    (!cand.contains(jt->name) && jt->ImDuty == false))
                            {
                                cand.append(jt->name);
                            }
                        }
                    }
                    who->actionlist.append(TurnObject(TT_USE_ITEM,cand,var->ID));
                }
                break;

            default:
                break;
            }
        }

        if(!_currvoting->is_over)
        {
            if(_currvoting->votelist.value(who->name).second == 0)
                who->actionlist.append(TurnObject(TT_VOTE,_currvoting->electlist));
            if(_currvoting->votelist.value(who->name).second == 1)
                who->actionlist.append(TurnObject(TT_UNVOTE));
        }
        if(who->status == 2){
            if(who->healthy)
                who->actionlist.append(TurnObject(TT_DOWN));
            else
                who->actionlist.append(TurnObject(TT_UP));
        }

    }
    else
    {//если ночь
        if(!who->waiting)
        {
            who->actionlist.append(TurnObject(TT_SKIP));
            if(!who->use_night_item)
            {
                foreach (item* var, who->itemlist.values())
                {
                    switch (var->ID) {
                    case IT_BLASTER:
                        if(var->power == 0)
                        {
                            who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->ID));
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,playerlist->keys(),var->ID));
                        }
                        break;
                    case IT_INJECTOR:
                    case IT_SCANNER:
                        if(var->power == 0)
                        {
                            who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->ID));
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,var->ID));
                        }
                        break;
                    case IT_BATTERY:
                        if(!brokeitemlist.isEmpty())
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,brokeitemlist,var->ID));

                        if(var->power == 0)
                        {
                            who->actionlist.append(TurnObject(TT_USE_ITEM,var->ID));
                        }
                        break;
                    case IT_BADGE:
                        if(var->power == 0)
                        {
                            foreach (ITEM item, itemlist)
                            {
                                if(!brokeitemlist.contains(item))
                                {
                                    TurnObject turn;
                                    turn.type = TT_USE_BADGE;
                                    switch (item) {
                                    case IT_BATTERY:
                                        turn.item = IT_BATTERY;
                                        who->actionlist.append(turn);
                                        break;
                                    case IT_BLASTER:
                                    case IT_INJECTOR:
                                    case IT_SCANNER:
                                    case IT_MOP:
                                        turn.item = item;
                                        turn.targets = playerlist->keys();
                                        who->actionlist.append(turn);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    case IT_MOP:
                        who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var->ID));
                        break;
                    default:
                        break;
                    }
                }
            }
            if(who->status == 2)
            {
                if(!who->attack_thisnight)
                {
                    who->actionlist.append(TurnObject(TT_ATTACK,playerlist->keys()));
                }
                if(!who->infecting)
                {
                    if(who->invasion == 0 || who->success_attack == 2 ||
                            (who->success_attack == 1 && who->attack_thisnight))
                    {
                        who->actionlist.append(TurnObject(TT_INFECT,playerlist->keys()));
                    }
                }
                if(who->healthy)
                    who->actionlist.append(TurnObject(TT_DOWN));
                else
                    who->actionlist.append(TurnObject(TT_UP));
            }
        }
        if(who->actionlist.count() == 1)
        {
            who->actionlist.clear();
            who->waiting = true;
        }
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

bool game::night()
{
    qDebug()<<"game::night()";
    foreach (player* v, playerlist->values()){
        make_actionlist(v);
        if(v->waiting == false)
        {
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

void game::slot_attack(TurnObject TO)
{
    qDebug()<<"game::slot_attack"<<who<<" "<<whom;
    //GuiMess2Log(who,"атаковал игрока "+whom);
    if(TO.wh->HP < 5)
        TO.wh->HP += 1;
    playerlist->value(TO.targets.dequeue())->HP -= 2;
    if(TO.wh->success_attack < 2)
        playerlist->value(who)->success_attack += 1;
    
    if(TO.wh->success_attack == 2){
        if(TO.wh->invasion == -1){
            TO.wh->invasion = 0;
        }
        // playerlist->value(who)->success_attack=0;
    }
    // make_actionlist(TO.wh);
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
}

void game::slot_getitem(TurnObject turn){
    qDebug()<<"game::slot_getitem(QString who,QString useit,QString power)";
    foreach (player* var, playerlist->values()) {
        if(var->itemlist.contains(turn.item)){
            var->itemlist.remove(turn.item);
        }
    }
    itemlist.value(turn.item)->power=turn.targets.dequeue().toInt();
    turn.wh->itemlist.insert(turn.item,itemlist.value(turn.item));
}

void game::slot_alien(TurnObject TO)
{
    qDebug()<<"game::slot_alien("+who+")";
    GuiMess2Log(who,"осознался");
    
    TO.wh->status = 2;
    TO.wh->invasion = -1;
    TO.wh->HP += (TO.wh->HP - 1);
    TO.wh->success_attack = 1;
    //make_actionlist(TO.wh);
}

void game::slot_vote(TurnObject turn){
    qDebug()<<"game::slot_vote(QString who,QString whom)";
    if(!_currvoting->is_over)
        _currvoting->on_voting(turn.wh->name,turn.targets.first());
}
void game::slot_unvote(TurnObject turn){
    //qDebug()<<"game::slot_unvote(QString who)";
    if(!_currvoting->is_over)
        _currvoting->off_voting(turn.wh->name);
}



void game::slot_wait(TurnObject TO){
    qDebug()<<"game::slot_wait "<<who;
    GuiMess2Log(TO.wh->name,"ждет");
    if(TO.wh->waiting == true)
        TO.wh->waiting == false;
}

void game::slot_up(TurnObject TO){
    qDebug()<<"game::slot_up "<<TO.wh->name;
    TO.wh->healthy = true;
    if(daytime)
        emit GuiMess2Log(TO.wh->name,"встал из биованны");
}

void game::slot_down(TurnObject TO){
    qDebug()<<"game::slot_down "<<TO.wh->name;
    TO.wh->healthy = false;
    if(daytime)
        emit GuiMess2Log(TO.wh->name,"в биованне");
}


void game::add_role(player* whom,QString what){
    qDebug()<<"game::add_role(player* whom,QString what)";
    emit GuiMess2Log("[Game]","Роль "+what+" отдата игроку "+whom->name);
    if(unclame_rolelist.contains(what))unclame_rolelist.removeOne(what);
    rolelist.insertMulti(what,whom);
    whom->rolelist.append(what);
    foreach (item* var, itemlist.values()) {
        if(var->role == what){
            whom->itemlist.append(var);
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
    foreach (item* var, whom->itemlist) {
        if(var->role == what){
            whom->itemlist.removeAll(var);
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

void game::slot_use_item(TurnObject turn){
    qDebug()<<"game::slot_use_item "<<who<<" "<<whom<<" "<<useit;
    GuiMess2Log(who,"использовал "+useit+" на "+whom);
    
    if(turn.wh->itemlist.value(turn.item)->power == 0)
    {
        if(daytime)
        {
            turn.wh->itemlist.value(turn.item)->use_item_day(turn.targets);
        }
        else
        {
            turn.wh->itemlist.value(turn.item)->use_item_night(turn.targets);
        }
        if(turn.wh->status < 2 && turn.wh->healthy == false)
        {
            turn.wh->HP-=1;
            check_HP(turn.wh);
        }
    }
}

void game::slot_use_item_cap(TurnObject turn)
{
    GuiMess2Log(turn.wh->name," как капитан, использовал "+turn.item+" на "+turn.targets);
    if(turn.wh->itemlist.value("Badge")->power != -2)
    {
        if(itemlist.value(turn.item)->power == 0)
        {
            if(daytime == true)
                itemlist.value(turn.item)->use_item_day(turn.targets);
            else
                itemlist.value(turn.item)->use_item_night(turn.targets);
            if(turn.wh->status < 2 && turn.wh->healthy == false)
            {
                turn.wh->HP -= 1;
                check_HP(turn.wh);
            }
            turn.wh->itemlist.value("Badge")->power = -2;
        }
    }
}

void game::slot_ult_item(TurnObject turn)
{
    qDebug()<<"game::slot_ult_item "<<who<<" "<<whom<<" "<<useit;
    GuiMess2Log(who,"ультанул "+useit+"ом");
    
    //ingame_event*_eve=new ingame_event(who,whom,"useult",useit);
    turn.wh->itemlist.value(turn.item)->ult_item(turn.targets);
    brokeitemlist.append(turn.item);

    delete_role(turn.wh,itemlist.value(turn.item)->role);
    if(turn.wh->status < 2 && turn.wh->healthy == false)
    {
        turn.wh->HP -= 1;
        check_HP(turn.wh);
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

bool game::make_events_check(TurnObject turn)
{
    qDebug()<<"game::make_events_check";
    // QString check_first,check_second;
    if(!playerlist->contains(turn.wh->name))
        return false;

    switch (turn.type) {
    case TT_DOWN:
        if(turn.wh->healthy == false)
            return false;
        break;
    case TT_UP:
        if(turn.wh->healthy == true)
            return false;
        break;
    case TT_NOTHING:
        return false;
    case TT_ATTACK:
    case TT_INFECT:
    case TT_VOTE:
        if(turn.targets.isEmpty())
            return false;
        break;
    default:
        break;
    }

    if(turn.wh->actionlist.contains(turn)){
        return true;
    }
    return false;
}

void game::make_events(int wwh,TurnObject turn)
{
    if(connectedName.contains(wwh))
    {
        QString who = connectedName.value(wwh);
        qDebug()<<"game::make_events "<<who<<" "<<what<<" "<<how<<" "<<whom;

        turn.wh = playerlist->value(who);
        if(make_events_check(turn))
        {
            if (this->daytime)
            {
                do_events(turn);
                make_actionlist(man);
            }
            else
            {
                _nightque.enqueue(turn);
                switch (turn.type) {
                case TT_ATTACK:
                    turn.wh->attack_thisnight = true;
                    break;
                case TT_USE_ITEM:
                case TT_USE_BADGE:
                case TT_ULT_ITEM:
                    turn.wh->use_night_item = true;
                    break;
                case TT_SKIP:
                    turn.wh->waiting = true;
                    break;
                case TT_INFECT:
                    turn.wh->invasion = -1;
                    turn.wh->infecting = true;
                    break;
                case TT_UP:
                    slot_up(turn);
                    break;
                case TT_DOWN:
                    slot_down(turn);
                    break;
                default:
                    break;
                }
                if(night()){
                    day();
                }

            }
        }
    }
}



bool game::makeNightActoins()
{//true - продолжать игру, false - game over
    qDebug()<<"game::makeNightActoins()";
    sortNightActions();
    QQueue <TurnObject> _night = _nightque;
    while(!_nightque.isEmpty())
    {
        do_events(_nightque.dequeue());
    }
    
    foreach (player* it, playerlist->values())
    {
        if(it->HP <= 0){
            player_death(it);
            continue;
        }
        
        if(it->simplebath == true && it->healthy == false)
        {
            it->HP += 1;
        }
        if(it->status == 1){
            it->invasion -= 1;
            if(it->invasion == 0){
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

void game::register_new_player(int tempname, TurnObject turn)
{
    if(!playerlist->contains(turn.item))
    {
        connectedName.insert(tempname,turn.item);
        player* noob = new player(turn.item,tempname);
        playerlist->insert(turn.item,noob);
        //playerlist->value(name)->avatar=avatar.toInt();
        emit namecorrect(tempname);
    }
    else
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

void game::registerRolebyPlayer(int _na, TurnObject turn)
{
    QString _name = connectedName.value(_na);
    if(turn.item != "Passenger")
    {
        if(playerlist->value(_name)->rolelist.isEmpty())
        {
            if(unclame_rolelist.contains(turn.item))
            {
                unclame_rolelist.removeOne(turn.item);
                rolelist.insertMulti(turn.item,playerlist->value(_name));
                playerlist->value(_name)->rolelist.append(turn.item);
                passengerlist.removeOne(_name);
                emit rolecorrect(_na);
            }
            else norolecorrect(_na);
        }
        else
        {
            unclame_rolelist.removeOne(turn.item);
            foreach (QString var,playerlist->value(_name)->rolelist)
            {
                playerlist->value(_name)->rolelist.removeOne(var);
                unclame_rolelist.append(var);
            }
            playerlist->value(_name)->rolelist.append(turn.item);
            emit rolecorrect(_na);
        }
        
        if(unclame_rolelist.count()==0)
        {
            unclame_rolelist.append("Dep_Doctor");
            unclame_rolelist.append("Dep_Gunmen");
            unclame_rolelist.append("Dep_Engineer");
            unclame_rolelist.append("Dep_Scientist");
            unclame_rolelist.append("Dep_Signalmen");
        }
    }
    else
    {
        passengerlist.append(_name);
        playerlist->value(_name)->rolelist.append(turn.item);
        emit rolecorrect(_na);
    }
    slotSendRolelist();
    emit GuiUpdatePlayerlist(playerlist->values());
    
    QList <QString> mainrole;//проверка на запуск новой сессии (заняты ли все основные роли)
    mainrole <<"Captain"<<"Doctor"<<"Signalmen"<<"Gunmen"<<"Assistant"<<"Engineer"<<"Scientist";
    bool check=true;
    foreach (QString var, mainrole)
    {
        if (unclame_rolelist.contains(var))
            check=false;
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

void game::sortNightActions()
{
    qDebug()<<"game::sortNightActions()";

    QQueue<TurnObject>_queue=_nightque;
    _nightque.clear();

    qSort(_queue.begin(),_queue.end(),qLe());

    QList <QString> playerblock; //игроки, чьи действия или действия на которых заблокированы
    QList <QString> playeritemuse;//игроки, пользовавшиеся предмеами этой ночью
    QString itblok;//предмет, использованный капитаном
    QList <QString> playerhunt;//игроки, попадающие под защиту боевика
    QList <QString> attackedhuman;//атакованные чужими люди

    while (!_queue.isEmpty())
    {
        TurnObject _eve = _queue.dequeue();

        if(_eve.type == TT_SKIP)
        {
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.wh->healthy == false) &&
                (_eve.type == TT_UP        ||
                 (_eve.type == TT_USE_ITEM) ||
                 (_eve.type == TT_USE_BADGE)||
                 (_eve.type == TT_ULT_ITEM) ||
                 (_eve.type == TT_ATTACK)   ||
                 (_eve.type == TT_INFECT)))
        {
            _eve.wh->simplebath = false;
        }
        if(_eve.type == TT_ALIEN || _eve.type == TT_UP || _eve.type == TT_DOWN ||
                _eve.type == TT_GETITEM || _eve.type == TT_DELITEM)
        {
            _nightque.enqueue(_eve);
            continue;
        }

        if(((_eve.type == TT_USE_ITEM) ||
            (_eve.type == TT_USE_BADGE)||
            (_eve.type == TT_ULT_ITEM)||
            (_eve.type == TT_ATTACK)||
            (_eve.type == TT_INFECT)))
        {
            if(playerblock.contains(_eve.wh->name))
                continue;
            else if(!_eve.targets.isEmpty())
                if(playerblock.contains(_eve.targets.first()))
                {
                    continue;
                }
        }
        bool AAA = playerhunt.contains(_eve.wh->name);
        bool BBB;
        if(!_eve.targets.isEmpty())
            BBB = playerhunt.contains(_eve.targets.first());
        else BBB = false;
        //адская замена ксору
        if((_eve.type == TT_ULT_ITEM)||
                (_eve.type == TT_ATTACK)||
                (_eve.type == TT_INFECT))
        {
            if((!AAA && BBB) || (!BBB && AAA))
            {
                _eve.wh->HP -= 2;
                continue;
            }
        }
        if(_eve.type == TT_USE_BADGE &&
                _eve.wh->itemlist.value("Badge")->power == 0 &&
                itemlist.value(_eve.item)->power == 0)
        {
            if(_eve.item == "Mop")
            {
                if(!playerlist->value(_eve.targets.first())->rolelist.contains("Doctor"))
                {
                    playerblock.append(_eve.targets.first());
                }
            }
            if(_eve.item == "Battery")
            {
                playerblock.append(_eve.wh->name);
            }
            if(_eve.item == "Blaster")
            {
                playerhunt.append(_eve.targets.first());
                if(playerlist->value(_eve.targets.first())->healthy == false)
                {
                    foreach (player* vavar, playerlist->values()) {
                        if(vavar->healthy == false && vavar->name != _eve.targets.first())
                            playerhunt.append(vavar->name);
                    }
                }
                playerhunt.append(_eve.wh->name);
            }
            _nightque.enqueue(_eve);
            playeritemuse.append(_eve.wh->name);
            itblok = _eve.item;
            continue;
        }
        
        if((_eve.type == TT_USE_ITEM || _eve.type == TT_ULT_ITEM) &&
                ((_eve.item == itblok) || (playeritemuse.contains(_eve.wh->name))))
        {
            continue;
        }
        if((_eve.type == TT_USE_ITEM) && (_eve.item == "Scanner"))
        {
            playeritemuse.append(_eve.wh->name);
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.type == TT_USE_ITEM || _eve.type == TT_ULT_ITEM) && _eve.item == "Mop")
        {
            _nightque.enqueue(_eve);
            playeritemuse.append(_eve.wh->name);
            playerblock.append(_eve.targets.first());
            continue;
        }
        
        if((_eve.type == TT_USE_ITEM) && (_eve.item == "Battery"))
        {
            _nightque.enqueue(_eve);
            playeritemuse.append(_eve.wh->name);
            playerblock.append(_eve.wh->name);
            continue;
        }
        if((_eve.type == TT_USE_ITEM)&&(_eve.item == "Blaster"))
        {
            _nightque.enqueue(_eve);
            playeritemuse.append(_eve.wh->name);
            if(playerlist->value(_eve.targets.first())->healthy == false)
            {
                foreach (player* vavar, playerlist->values()) {
                    if(vavar->healthy == false)
                        playerhunt.append(vavar->name);
                }
            }else playerhunt.append(_eve.targets.first());
            playerhunt.append(_eve.wh->name);
            continue;
        }
        
        if((_eve.type == TT_ULT_ITEM) && (_eve.item == "Battery"))
        {
            playeritemuse.append(_eve.wh->name);
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.type == TT_ULT_ITEM) && (_eve.item == "Injector"))
        {
            playeritemuse.append(_eve.wh->name);
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.type == TT_ULT_ITEM) && (_eve.item == "Scanner"))
        {
            playeritemuse.append(_eve.wh->name);
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.type == TT_ATTACK))
        {
            if(attackedhuman.contains(_eve.targets.first()))
            {
                continue;
            }
            if(playerlist->value(_eve.targets.first())->status != 2)
            {
                attackedhuman.append(_eve.targets.first());
            }
            _nightque.enqueue(_eve);
            continue;
        }
        if(_eve.type == TT_INFECT)
        {
            _nightque.enqueue(_eve);
            continue;
        }

    }
}

void game::do_events(TurnObject TO){
    switch (TO->type) {
    case TT_ALIEN:
        slot_alien(TO);
        break;
    case TT_ATTACK:
        slot_attack(TO);
        break;
    case TT_USE_ITEM:
        slot_use_item(TO);
        break;
    case TT_USE_BADGE:
        slot_use_item_cap(TO);
        break;
    case TT_ULT_ITEM:
        slot_ult_item(TO);
        break;
    case TT_INFECT:
        slot_infect(TO);
        break;
    case TT_VOTE:
        slot_vote(TO);
        break;
    case TT_UNVOTE:
        slot_unvote(TO);
        break;
    case TT_UP:
        slot_up(TO);
        break;
    case TT_DOWN:
        slot_down(TO);
        break;
    case TT_SKIP:
        slot_wait(TO);
        break;
    case TT_GETITEM:
        slot_getitem(TO);
        break;
    default:
        break;
    }
}
