#include "game.h"



class qLe
{
public:
    inline bool operator()(TurnObject& t1, TurnObject& t2) const
    {
        if(t1.type == t2.type)
            if(t1.type == TT_ATTACK){
                if(t1.wh->HP != t2.wh->HP){
                    return t1.wh->HP < t2.wh->HP;
                }else{
                    if(t1.wh->invasionday != t2.wh->invasionday){
                        return t1.wh->invasionday < t2.wh->invasionday;
                    } else{
                        return t1.wh->whoinvas->invasionday < t2.wh->whoinvas->invasionday;
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
    currentday = 0;
    daytime = true;
    playerlist = new QMap <QString,player*>();
    
    unclame_rolelist.append(RT_CAPTAIN);
    unclame_rolelist.append(RT_DOCTOR);
    unclame_rolelist.append(RT_GUNMEN);
    unclame_rolelist.append(RT_ASSISTANT);
    unclame_rolelist.append(RT_ENGINEER);
    unclame_rolelist.append(RT_SCIENTIST);
    unclame_rolelist.append(RT_SIGNALMEN);
}

void game::start(){
    //qDebug()<<"game::start()";
    emit startnewsessionenable(false);
    
    _currvoting=new voting();
    StartRandomEvasion_testing();
    unclame_rolelist.clear();
    emit startgame(playerlist->values());
    getItemByRoleAll();

    day();
}

void game::getItemByRoleAll()
{
    //qDebug()<<"game::getItemByRoleAll()";
    foreach (player* var, playerlist->values())
    {
        foreach (ROLE role, var->rolelist) {
            item* bb;
            switch (role) {
            case RT_CAPTAIN:
                bb = new Badge(this);
                var->itemlist.append(IT_BADGE);
                itemlist.insert(IT_BADGE,bb);
                break;
            case RT_DOCTOR:
                bb = new Injector(this);
                var->itemlist.append(IT_INJECTOR);
                itemlist.insert(IT_INJECTOR,bb);
                break;
            case RT_GUNMEN:
                bb = new Blaster(this);
                var->itemlist.append(IT_BLASTER);
                itemlist.insert(IT_BLASTER,bb);
                break;
            case RT_ASSISTANT:
                bb = new Rotation(this);
                var->itemlist.append(IT_ROTATION);
                itemlist.insert(IT_ROTATION,bb);
                break;
            case RT_ENGINEER:
                bb = new Battery(this);
                bb->setPower(2);
                var->itemlist.append(IT_BATTERY);
                itemlist.insert(IT_BATTERY,bb);
                break;
            case RT_SCIENTIST:
                bb = new Scanner(this);
                var->itemlist.append(IT_SCANNER);
                itemlist.insert(IT_SCANNER,bb);
                break;
            case RT_SIGNALMEN:
                bb = new Notebook(this);
                var->itemlist.append(IT_NOTEBOOK);
                itemlist.insert(IT_NOTEBOOK,bb);
            default:
                break;
            }
            TurnObject turn(TT_GETITEM);
            turn.wh = var;
            turn.item = bb->getID();
            turn.targets.append(QString::number(bb->getPower()));
            emit send_stat(turn);
        }
    }
}


void game::make_actionlist(player* who){
    //qDebug()<<"game::make_actionlist(player* who)"<<who->name;
    who->actionlist.clear();
    TurnObject turn1;

    if(daytime)
    {
        foreach (ITEM var, who->itemlist)
        {
            switch (var) {
            case IT_BLASTER:
                if(itemlist[var]->getPower() == 0)
                {
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,playerlist->keys(),var));
                }
                break;
            case IT_INJECTOR:
                if(itemlist[var]->getPower() == 0)
                {
                    who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var));
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,var));
                }
                break;
            case IT_NOTEBOOK:
                if(!_currvoting->is_over || hardresolve)
                {
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,var));
                    if(itemlist[var]->getPower() == 0)
                    {
                        who->actionlist.append(TurnObject(TT_USE_ITEM,_currvoting->electlist,var));
                    }
                }
                break;
            case IT_BATTERY:
                turn1.type = TT_ULT_ITEM;
                turn1.item = IT_BATTERY;
                foreach (ITEM item, itemlist.keys())
                {
                    if (itemlist[item]->getPower() == -1)
                    {
                        turn1.targets.append(itemlist[item]->getHandle());
                    }
                }
                who->actionlist.append(turn1);


                if(itemlist[var]->getPower() == 0)
                {
                    TurnObject turn2(TT_USE_ITEM,IT_BATTERY);
                    foreach (ITEM item, itemlist.keys())
                    {
                        switch (item) {
                        case IT_BADGE:
                        case IT_ROTATION:
                        case IT_BATTERY:
                        case IT_FETUS:
                        case IT_MOP:
                            break;
                        default:
                            turn2.targets.append(itemlist[item]->getHandle());
                            break;
                        }

                    }
                    who->actionlist.append(turn2);
                }
                break;
            case IT_SCANNER:
                if(itemlist[var]->getPower() == 0)
                {
                    who->actionlist.append(TurnObject(TT_ULT_ITEM,var));
                    who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var));
                }
                break;
            case IT_BADGE:
                if(_currvoting->is_over && hardresolve)
                {
                    who->actionlist.append(TurnObject(TT_USE_ITEM,_currvoting->winners,var));
                } else if(!hardresolve && !passengerlist.isEmpty() && unclame_rolelist.contains(RT_ASSISTANT))
                {
                    who->actionlist.append(TurnObject(TT_USE_ITEM,passengerlist,var));
                }
                if(itemlist[var]->getPower() == 0)
                {
                    TurnObject turn;
                    turn.type = TT_USE_BADGE;
                    foreach (ITEM item, itemlist.keys())
                    {
                        if(!brokeitemlist.contains(item)){
                            switch (item) {
                            case IT_BATTERY:
                                turn.item = IT_BATTERY;
                                foreach (ITEM item1, itemlist.keys())
                                {
                                    switch (item1) {
                                    case IT_BADGE:
                                    case IT_ROTATION:
                                    case IT_BATTERY:
                                    case IT_FETUS:
                                    case IT_MOP:
                                        break;
                                    default:
                                        turn.targets.append(itemlist[item1]->getHandle());
                                        break;
                                    }

                                }
                                who->actionlist.append(turn);
                                break;
                            case IT_BLASTER:
                            case IT_INJECTOR:
                            case IT_SCANNER:
                                turn.item = item;

                                turn.targets.append(playerlist->keys());
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
                    QList<ROLE>deprole;
                    QList<QString>cand;//готовим список дежурных
                    deprole <<RT_DEP_DOCTOR<<RT_DEP_GUNMEN<<RT_DEP_ENGINEER
                           <<RT_DEP_SCIENTIST<<RT_DEP_SIGNALMEN<<RT_ASSISTANT;
                    foreach (player* it, playerlist->values())
                    {
                        if(!it->ImDuty)
                        {
                            foreach (ROLE r, it->rolelist)
                            {
                                if(deprole.contains(r)&&(!cand.contains(it->name) &&
                                                         (!it->rolelist.contains(RT_CAPTAIN))))
                                {
                                    cand.append(it->name);
                                }
                            }
                        }
                    }
                    foreach (QString hth, passengerlist)
                    {
                        if(!playerlist->value(hth)->ImDuty)
                        {
                            cand.append(hth);
                        }
                    }
                    if(cand.count() <= 1)
                    {
                        foreach (player* jt, playerlist->values())
                        {
                            if(!jt->rolelist.contains(RT_CAPTAIN)&&
                                    (!cand.contains(jt->name) && !jt->ImDuty))
                            {
                                cand.append(jt->name);
                            }
                        }
                    }
                    who->actionlist.append(TurnObject(TT_USE_ITEM,cand,var));
                }
                break;

            default:
                break;
            }
        }

        if(!_currvoting->is_over)
        {
            if(!_currvoting->is_vote(who->name))
                who->actionlist.append(TurnObject(TT_VOTE,_currvoting->electlist));
            else
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
                foreach (ITEM var, who->itemlist)
                {
                    switch (var) {
                    case IT_BLASTER:
                        if(itemlist[var]->getPower() == 0)
                        {
                            who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var));
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,playerlist->keys(),var));
                        }
                        break;
                    case IT_INJECTOR:
                    case IT_SCANNER:
                        if(itemlist[var]->getPower() == 0)
                        {
                            who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var));
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,var));
                        }
                        break;
                    case IT_BATTERY:
                        if(!brokeitemlist.isEmpty()){
                            QStringList templist;
                            foreach (ITEM item, brokeitemlist) {
                                templist.append(TurnObject::ItemDescr.key(item));
                            }
                            who->actionlist.append(TurnObject(TT_ULT_ITEM,templist,var));
                        }
                        if(itemlist[var]->getPower() == 0)
                        {
                            who->actionlist.append(TurnObject(TT_USE_ITEM,var));
                        }
                        break;
                    case IT_BADGE:
                        if(itemlist[var]->getPower() == 0)
                        {
                            foreach (ITEM item, itemlist.keys())
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
                                        turn.targets.append(playerlist->keys());
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
                        who->actionlist.append(TurnObject(TT_USE_ITEM,playerlist->keys(),var));
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
    if(_currvoting->is_over && !hardresolve)
    {
        if (!votingque.isEmpty())
        {
            day_next_voting();
        } else
        {
            if(!nightrotation.isEmpty() ||
                    (unclame_rolelist.contains(RT_CAPTAIN) && (unclame_rolelist.contains(RT_ASSISTANT))))
            {
                night_start();
            }else
                if(rolelist.value(RT_ASSISTANT) != rolelist.value(RT_CAPTAIN))
                    emit GuiMess2Log("[Game]","Помощник капитана должен назначить график дежурств!");
                else
                    emit GuiMess2Log("[Game]","Капитан должен назначить график дежурств!");
        }
    }
}


void game::day(){
    //qDebug()<<"game::day()";
    if(makeNightActoins()){
        daytime = true;
        forrepowered = IT_UNKNOW;
        foreach (player* v, playerlist->values()) {
            check_HP(v);
        }
        currentday++;
        emit startPhase(currentday, daytime);
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
        _currvoting->votelist.append(new VoteObject(v->name));
    }
    foreach (QString trt, _currvoting->electlist) {
        if(!playerlist->contains(trt)){
            _currvoting->electlist.removeOne(trt);
        }
    }
    connect (_currvoting,SIGNAL(voting_over(QList<QString>)),this,SLOT(day_resolve_curr_voting(QList<QString>)));
    connect (_currvoting,SIGNAL(voting_canseled()),this,SLOT(day_canseled_voting()));

    foreach (player* var, playerlist->values()) {
        make_actionlist(var);
    }
    emit startvote(_currvoting->targets,_currvoting->electlist);
    if(_currvoting->targets == RT_ALIEN)
        emit GuiMess2Log("[Game]","Выбираем цель диагностической операции");
    else
        emit GuiMess2Log("[Game]","Голосование на передачу должности: "+RegisterObject::RoleDescr.key(_currvoting->targets));
    
}


void game::day_cap_curr_voting(QString win){
    qDebug()<<"game::day_cap_curr_voting";
    if(hardresolve && _currvoting->winners.contains(win))
    {
        day_end_curr_voting(win);
        emit GuiMess2Log("[Game]","Капитан отдал решающий голос в пользу "+win);
    }
}

void game::day_end_curr_voting(QString winner)
{
    qDebug()<<"game::day_end_curr_voting(QString winner)";
    //тут отправка игрокам сообщения
    if (playerlist->contains(winner)){
        hardresolve = false;
        player* win = playerlist->value(winner);
        if (_currvoting->targets == RT_ALIEN)
        {
            if(win->status<2)
            {
                //игрок - человек
                emit GuiMess2Log("[Game]","Игрок "+winner+" - человек");
                win->HP = win->HP-1;
                if(win->status == 1)
                {
                    //оповещение об изъятии эмбриона
                    win->status = 0;
                    win->invasion = -1;
                    emit endvote(_currvoting->targets,winner,"fetus");
                    emit GuiMess2Log("[Game]","Из игрока "+winner+" извлечен эмбрион");
                }
                else
                {
                    emit endvote(_currvoting->targets,winner,"human");
                }
                check_HP(win);
            }
            if(win->status == 2){
                emit GuiMess2Log("[Game]","Игрок "+winner+" - чужой!");
                emit endvote(_currvoting->targets,winner,"alien");
                player_death(win);
            }
        }
        else{
            //оповещение о присуждении роли
            add_role(win,_currvoting->targets);

            emit endvote(_currvoting->targets,winner,"");
        }

        foreach (player* var, playerlist->values()) {
            make_actionlist(var);
        }
        _currvoting->is_over = true;

        disconnect (_currvoting,SIGNAL(voting_over(QList<QString>)),this,SLOT(day_resolve_curr_voting(QList<QString>)));
        disconnect (_currvoting,SIGNAL(voting_canseled()),this,SLOT(day_canseled_voting()));



        day_check_over();
    }
}


void game::day_resolve_curr_voting(QList<QString> win){
    
    qDebug()<<"game::day_resolve_curr_voting(QList<QString> win)";
    
    emit GuiMess2Log("[Game]","Подсчет голосов завершен");
    //disconnect (_event,SIGNAL(event_vote(QString,QString)),_currvoting,SLOT(on_voting(QString,QString)));
    //disconnect (_event,SIGNAL(event_unvote(QString)),_currvoting,SLOT(off_voting(QString)));
    _currvoting->is_over=true;
    if(win.count()==1){
        day_end_curr_voting(win.first());
    } else
    if(win.count()>1 && rolelist.keys().contains(RT_CAPTAIN)){
        //connect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(day_cap_curr_voting(QString,QString,QString)));
        //тут будет предложение капитану определить итог голосования лично
        emit GuiMess2Log("[Game]","Капитан должен сделать решающий выбор");
        hardresolve=true;
        foreach (player* var, playerlist->values()) {
            make_actionlist(var);
        }
    }else day_canseled_voting();
}


void game::day_canseled_voting(){
    qDebug()<<"game::day_canseled_voting()";
    emit GuiMess2Log("[Game]","Голосование было отменено по техническим причинам!");
    _currvoting->is_over = true;
    hardresolve = false;

    disconnect (_currvoting,SIGNAL(voting_over(QList<QString>)),this,SLOT(day_resolve_curr_voting(QList<QString>)));
    disconnect (_currvoting,SIGNAL(voting_canseled()),this,SLOT(day_canseled_voting()));
    foreach (player* var, playerlist->values()) {
        make_actionlist(var);
    }
    emit endvote(_currvoting->targets,"","");
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
    daytime = false;
    forrepowered = IT_UNKNOW;
    mopper = "";
    while(mopper == "" && !nightrotation.isEmpty())
    {
        mopper = nightrotation.dequeue();
        if(!playerlist->keys().contains(mopper))
            mopper = "";
    }
    if(mopper != "")
    {
        emit GuiMess2Log("[Game]","Сегодня дежурит "+mopper);

        TurnObject turn(TT_DUTY);
        turn.wh = playerlist->value(mopper);
        emit send_changes(turn);

        item* bb = new Mop(this);
        playerlist->value(mopper)->itemlist.append(IT_MOP);
        itemlist.insert(IT_MOP,bb);
    } else
        emit GuiMess2Log("[Game]","Сегодня никто не дежурит");
    
    foreach (player* v, playerlist->values())
    {
        if(!v->healthy)
        {
            v->simplebath = true;
        }
        v->waiting = false;
        v->attack_thisnight = false;
        v->use_night_item = false;
        v->infecting = false;
        make_actionlist(v);
    }
    emit startPhase(currentday, daytime);
}

void game::StartRandomEvasion(){
    //qDebug()<<"game::StartRandomEvasion()";
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    int sizeoflist=playerlist->count();
    int a1=qrand()%(sizeoflist);//первый чужой
    player* A1;
    int a2 = 0;
    int a3;//первый зараженный
    int a4;//первый раненый
    while(true){
        a3=qrand()%(sizeoflist);
        a4=qrand()%(sizeoflist);
        if(a1!=a3 && a1!=a4)break;
    }
    
    foreach (player* var, playerlist->values()) {
        if(a2==a1)
        {
            TurnObject _eve(TT_ALIEN);
            _eve.wh = var;
            _nightque.enqueue(_eve);
            A1=var;
            var->invasionday=-1;
        }
        a2++;
    }
    
    a2=0;
    foreach (player* var, playerlist->values()) {
        if(a2==a4){
            var->HP=1;
        }
        if(a2 == a3)
        {
            var->status=1;
            var->invasion=2;
            TurnObject _eve(TT_INFECT);
            _eve.targets.append(var->name);
            _eve.wh = A1;
            _nightque.enqueue(_eve);
        }
        a2++;
    }
    
}

void game::StartRandomEvasion_testing()
{
    int a1=1;//первый чужой
    int a2=0;
    int a3=2;//первый зараженный
    int a4=2;//первый раненый
    foreach (player* play, playerlist->values())
    {
        if (a2 == a1)
        {
            TurnObject eve(TT_ALIEN);
            eve.wh = play;
            play->invasionday=-1;
            _nightque.enqueue(eve);
        }
        if (a2 == a3)
        {
            play->status=1;
            play->invasion=2;
            TurnObject eve(TT_INFECT);
            eve.targets.append(play->name);
            eve.wh = play;
            _nightque.enqueue(eve);
        }
        if(a2 == a4)
        {
            play->HP = 1;
        }
        a2++;
    }
}

void game::slot_attack(TurnObject TO)
{
    //qDebug()<<"game::slot_attack"<<who<<" "<<whom;
    //GuiMess2Log(who,"атаковал игрока "+whom);
    if(TO.wh->HP < 3)
        TO.wh->HP += 1;
    playerlist->value(TO.targets.dequeue())->HP -= 1;
    if(TO.wh->success_attack < 2)
        TO.wh->success_attack += 1;
    
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
        //qDebug()<<who<<" заражает игрока "<<whom;
        TO.wh->invasion = -1;
        TO.wh->success_attack = 0;
        //GuiMess2Log(who,"заражает игрока "+whom);
        player* whom = playerlist->value(TO.targets.dequeue());
        if(whom->status < 2){
            whom->status = 1;
            whom->invasionday = currentday;
            whom->invasion = 2;
            whom->whoinvas = TO.wh;
        }
        if(whom->status == 2){
            //GuiMess2Log(whom,"поглощает эмбрион");
            whom->HP += 1;
            check_HP(whom);
        }
    }
}

void game::slot_getitem(TurnObject turn){
    qDebug()<<"game::slot_getitem(QString who,QString useit,QString power)";
    foreach (player* var, playerlist->values()) {
        if(var->itemlist.contains(turn.item)){
            var->itemlist.removeOne(turn.item);
        }
    }
    itemlist.value(turn.item)->setPower(turn.targets.dequeue().toInt());
    turn.wh->itemlist.append(turn.item);
}

void game::slot_alien(TurnObject TO)
{
    //qDebug()<<"game::slot_alien("+who+")";
    //GuiMess2Log(who,"осознался");
    
    TO.wh->status = 2;
    TO.wh->invasion = -1;
    TO.wh->HP += 1;
    TO.wh->success_attack = 1;

    emit send_stat(TO);
    //make_actionlist(TO.wh);
}

void game::slot_vote(TurnObject turn){
    qDebug()<<"game::slot_vote(QString who,QString whom)";
    if(!_currvoting->is_over)
    {
        _currvoting->on_voting(turn.wh->name,turn.TARGET);
    }
}

void game::slot_unvote(TurnObject turn){
    //qDebug()<<"game::slot_unvote(QString who)";
    if(!_currvoting->is_over)
    {
        _currvoting->off_voting(turn.wh->name);
        //emit send_votelist(_currvoting->votelist);
    }
}



void game::slot_wait(TurnObject TO){
    //qDebug()<<"game::slot_wait "<<who;
    GuiMess2Log(TO.wh->name,"ждет");
    if(TO.wh->waiting == true)
        TO.wh->waiting == false;
}

void game::slot_up(TurnObject TO){
    qDebug()<<"game::slot_up "<<TO.wh->name;
    if(TO.targets.isEmpty())
        TO.wh->healthy = true;
    else
        playerlist->value(TO.TARGET)->healthy = true;
    if(daytime)
        emit GuiMess2Log(TO.wh->name,"встал из биованны");
}

void game::slot_down(TurnObject TO){
    qDebug()<<"game::slot_down "<<TO.wh->name;
    if(TO.targets.isEmpty())
        TO.wh->healthy = false;
    else
        playerlist->value(TO.TARGET)->healthy = false;
    if(daytime)
        emit GuiMess2Log(TO.wh->name,"в биованне");
}


void game::add_role(player* whom,ROLE what)
{
    qDebug()<<"game::add_role(player* whom,QString what)";
    emit GuiMess2Log("[Game]","Роль "+RegisterObject::RoleDescr.key(what) + " отдата игроку "+whom->name);
    TurnObject turn(TT_GETROLE);
    turn.wh = whom;
    turn.targets.append(RegisterObject::RoleDescr.key(what));
    emit send_changes(turn);

    if(unclame_rolelist.contains(what))
        unclame_rolelist.removeOne(what);
    rolelist.insertMulti(what,whom);
    whom->rolelist.append(what);
    if(what <= 7)
        whom->itemlist.append(TurnObject::RoleItem[what]);
    make_actionlist(whom);
}

void game::delete_role(player* whom,ROLE what)
{
    qDebug()<<"game::delete_role(player* whom,QString what)";
    QList <ROLE> mainrole;
    mainrole <<RT_CAPTAIN<<RT_DOCTOR<<RT_SIGNALMEN<<RT_GUNMEN<<RT_ASSISTANT<<RT_ENGINEER<<RT_SCIENTIST;

    emit GuiMess2Log("[Game]","Игрок "+whom->name+ "потерял роль "+RegisterObject::RoleDescr.key(what));

    TurnObject turn(TT_DELROLE);
    turn.wh = whom;
    turn.targets.append(RegisterObject::RoleDescr.key(what));
    emit send_changes(turn);

    rolelist.remove(what,whom);
    if(rolelist.count(what) == 0)
        rolelist.remove(what);
    whom->rolelist.removeOne(what);
    foreach (item* var, itemlist.values())
    {
        if(what <= 7)
        {
            whom->itemlist.removeAll(TurnObject::RoleItem[what]);
            turn.type = TT_DELITEM;
            turn.item = TurnObject::RoleItem[what];
            emit send_stat(turn);
        }
    }
    if(mainrole.contains(what))
    {
        unclame_rolelist.append(what);
    }
    if(whom->rolelist.isEmpty())
    {
        passengerlist.append(whom->name);
        if(!whom->ImDuty)
        {
            nightrotation.enqueue(whom->name);
            whom->ImDuty = true;
        }
    }
    make_actionlist(whom);
}

void game::slot_use_item(TurnObject turn){
    qDebug()<<"game::slot_use_item ";
    //GuiMess2Log(who,"использовал "+useit+" на "+whom);
    {
        if(daytime)
        {
            if(turn.item == forrepowered)
            {
                itemlist.value(turn.item)->use_item_day(turn.targets);
                forrepowered = IT_UNKNOW;
                itemlist.value(IT_BATTERY)->setPower(2);

                TurnObject t(TT_CORRECT,IT_BATTERY);
                t.wh = rolelist.value(RT_ENGINEER);
                emit send_stat(t);

                if((turn.type == TT_USE_BADGE || turn.type == TT_USE_ITEM) && turn.item == IT_SCANNER)
                    sendMsg(turn.wh,QString::number(itemlist[IT_SCANNER]->getLastScan().second));
            }
            else if(itemlist.value(turn.item)->getPower() == 0) {
                itemlist.value(turn.item)->use_item_day(turn.targets);

                if((turn.type == TT_USE_BADGE || turn.type == TT_USE_ITEM) && turn.item == IT_SCANNER)
                    sendMsg(turn.wh,QString::number(itemlist[IT_SCANNER]->lastscan.second));
            }
        }
        else
        {
            itemlist.value(turn.item)->use_item_night(turn.targets);
        }



        if(!turn.wh->healthy &&
                (turn.item != IT_BADGE && turn.item != IT_ROTATION))
        {
            player_death(turn.wh);
        }
    }
}

void game::slot_use_item_cap(TurnObject turn)
{
    //GuiMess2Log(turn.wh->name," как капитан, использовал "+itemlist.value(turn.item)->name+" на "+turn.targets);
    if(itemlist.value(IT_BADGE)->getPower() != -2)
    {
        slot_use_item(turn);
        itemlist.value(IT_BADGE)->setPower(-2);
    }
}

void game::slot_ult_item(TurnObject turn)
{
    itemlist.value(turn.item)->ult_item(turn.targets);
    brokeitemlist.append(turn.item);

    delete_role(turn.wh,TurnObject::RoleItem.key(turn.item));
    if(turn.wh->status < 2 && turn.wh->healthy == false)
    {
        turn.wh->HP -= 1;
        check_HP(turn.wh);
    }
    
}


/*void game::make_events(int wwh,QString what,QString whom,QString how,QQueue<QString> rota){
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
}*/

bool game::make_events_check(TurnObject turn)
{
    qDebug()<<"game::make_events_check";
    // QString check_first,check_second;
    if(!playerlist->contains(turn.wh->name))
        return false;

    switch (turn.type) {
    case TT_USE_ITEM:
    case TT_ULT_ITEM:
        if(!turn.wh->itemlist.contains(turn.item))
            return false;
        break;
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
        qDebug()<<"game::make_events "<<who<<" "<<TurnObject::TurnDescr.key(turn.type);
        if(playerlist->keys().contains(who))
        {
            turn.wh = playerlist->value(who);
            if(make_events_check(turn))
            {
                if (this->daytime)
                {
                    do_events(turn);
                    make_actionlist(turn.wh);
                    emit send_changes(turn);
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
            if(it->invasion == 0)
            {
                TurnObject event(TT_ALIEN);
                event.targets.append(it->name);
                event.wh = it;
                slot_alien(event);
            }
        }
        it->itemlist.removeAll(IT_MOP);
    }
    itemlist[IT_MOP]->deleteLater();//скорее всего нужно будет удалить и сам объект из памяти
    itemlist.remove(IT_MOP);
    foreach (item* ii, itemlist.values()) {
        ii->counter();
    }
    
    //emit send_nightmare(_night,playerlist->values());
    if (playerlist->count()>1){
        foreach (player* v, playerlist->values()) {
            if (v->status>=1){
                votingque.enqueue(new voting(playerlist->keys(),RT_ALIEN));
                return true;
            }
        }
        return false;//все здоровы, чужих больше нет
    } else {
        if(playerlist->begin().value()->status!=1)
            return false;
    }//остался последний игрок, или больше никого не осталось.
}

void game::register_new_player(RegisterObject reg)//(int tempname, TurnObject turn)
{
    if(reg.targets == TT_REGNAME) {
        bool ok = playerlist->contains(reg.name);
        if(!ok)
        {
            connectedName.insert(reg.ID,reg.name);
            player* noob = new player(reg.name,reg.ID);
            playerlist->insert(noob->name,noob);
        }
        emit namecorrect(reg.ID,!ok);

        slotSendRolelist();

        emit GuiUpdatePlayerlist(playerlist->values());
    }
    else
        registerRolebyPlayer(reg);
}

void game::slotSendRolelist(){
    emit sendrolelist2all(playerlist->values());
}

void game::slot_disconnected(int na){
    if(connectedName.contains(na)){
        QString name = connectedName.value(na);
        if(currentday == 0) {

            foreach (ROLE var,playerlist->value(name)->rolelist){
                playerlist->value(name)->rolelist.removeOne(var);
                unclame_rolelist.append(var);
            }
            playerlist->remove(name);
            connectedName.remove(na);
            slotSendRolelist();
        } else
            player_death(playerlist->value(name));
    }

    emit GuiUpdatePlayerlist(playerlist->values());
}

void game::registerRolebyPlayer(RegisterObject reg)
{
    reg.name = connectedName.value(reg.ID);
    player *pl = playerlist->value(reg.name);
    if(reg.role != RT_PASSENGER)
    {
        if(pl->rolelist.isEmpty())
        {
            bool ok = unclame_rolelist.contains(reg.role);
            if(ok)
            {
                unclame_rolelist.removeOne(reg.role);
                rolelist.insertMulti(reg.role,pl);
                pl->rolelist.append(reg.role);
                passengerlist.removeOne(reg.name);
                if((int)reg.role <= 7 && (int)reg.role >= 3) {
                    unclame_rolelist.append((ROLE)((int)reg.role+5));
                } else if((int)reg.role > 7)
                    unclame_rolelist.append(reg.role);
            }
            rolecorrect(reg.ID,ok);
        }
        else
        {
            unclame_rolelist.removeOne(reg.role);
            foreach (ROLE var,pl->rolelist)
            {
                pl->rolelist.removeOne(var);
                unclame_rolelist.append(var);
            }
            pl->rolelist.append(reg.role);
            emit rolecorrect(reg.ID,true);
        }
    }
    else
    {
        passengerlist.append(reg.name);
        pl->rolelist.append(reg.role);
        emit rolecorrect(reg.ID,true);
    }
    slotSendRolelist();
    emit GuiUpdatePlayerlist(playerlist->values());
    
    QList <ROLE> mainrole;//проверка на запуск новой сессии (заняты ли все основные роли)
    mainrole <<RT_CAPTAIN<<RT_DOCTOR<<RT_SIGNALMEN<<RT_GUNMEN<<RT_ASSISTANT<<RT_ENGINEER<<RT_SCIENTIST;
    bool check = true;
    foreach (ROLE var, mainrole)
    {
        if (unclame_rolelist.contains(var))
        {
            check = false;
            break;
        }

    }
    emit startnewsessionenable(check);
}

void game::player_death(player* dead)
{
    qDebug()<<"game::player_death(player* dead)";
    //тут будет отправка о том что игрок мертв
    emit GuiMess2Log("[Game]","Погиб игрок "+dead->name);
    TurnObject turn(TT_DIED);
    turn.wh = dead;
    emit send_changes(turn);

    QList <ROLE> mainroles;//проверка на запуск новой сессии (заняты ли все основные роли)
    mainroles <<RT_CAPTAIN<<RT_DOCTOR<<RT_SIGNALMEN<<RT_GUNMEN<<RT_ASSISTANT<<RT_ENGINEER<<RT_SCIENTIST;
    playerlist->remove(dead->name);
    foreach (ROLE var, rolelist.uniqueKeys())
    {
        foreach (player* v, rolelist.values(var))
            if(v == dead)
            {
                if(mainroles.contains(var))
                {
                    unclame_rolelist.append(var);
                    rolelist.remove(var);
                    check_for_role(var);
                }
                else rolelist.remove(var,dead);
                break;
            }
    }
    passengerlist.removeAll(dead->name);
    if(!_currvoting->is_over)
    {
        _currvoting->electlist.removeOne(dead->name);
        foreach (VoteObject* vote, _currvoting->votelist) {
            if(vote->who == dead->name)
            {
                _currvoting->votelist.removeAll(vote);
            }
            else if(vote->whom == dead->name)
            {
                vote->status = 0;
                vote->whom = vote->who;
            }

        }
        if(_currvoting->electlist.count() == 1)
        {
            day_resolve_curr_voting(_currvoting->electlist);
        }
    }
    if(hardresolve)
    {
        if(dead->rolelist.contains(RT_CAPTAIN))
        {
            votingque.append(new voting(playerlist->keys(),RT_ALIEN));
            day_canseled_voting();
        }
        else {
            _currvoting->winners.removeOne(dead->name);
            if(_currvoting->winners.count() == 1)
            {
                day_end_curr_voting(_currvoting->winners.first());
            }
        }
    }
    emit GuiUpdatePlayerlist(playerlist->values());
}

void game::check_HP(player* w)
{
    if(w->HP < 0)
        w->HP = 0;
    switch (w->HP) {
    case 0:
        if(w->itemlist.contains(IT_INJECTOR) && itemlist[IT_INJECTOR]->getPower() == 0)
        {
            do_events(TurnObject(TT_USE_ITEM,w->name,IT_INJECTOR));
        } else if (w->status == 2 && w->invasion == 0)
        {
            w->invasion = -1;
            w->HP = 1;
        } else
            player_death(w);
        break;
    case 1:
    case 2:
        if(w->healthy && w->status <= 1)
        {
            TurnObject turn(TT_DOWN);
            turn.wh = w;
            slot_down(turn);
            emit send_changes(turn);
        }
        break;
    case 3:
    case 4:
    case 5:
        if(!w->healthy && w->status <= 1)
        {
            TurnObject turn(TT_UP);
            turn.wh = w;
            slot_up(turn);
            emit send_changes(turn);
        }
    default:
        if(w->status<=1)
            w->HP = 3;
        else
            w->HP = 5;
        break;
    }
    TurnObject turn(TT_HP,QString::number(w->HP));
    turn.wh = w;
    emit send_stat(turn);
}

void game::check_for_role_capDecision(QString whom){//капитан выбирает старпома из числа пассажиров
    if(!hardresolve)
    {
        //disconnect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(check_for_role_capDecision(QString,QString,QString)));
        if(playerlist->contains(whom) && passengerlist.contains(whom)){
            add_role(playerlist->value(whom),RT_ASSISTANT);
        }else{
            check_for_role(RT_ASSISTANT);
        }
    }
}

void game::check_for_role(ROLE role)
{
    //передача роли заместителям или кому придется, заодно добавление голосований если нужно
    //дописать то, что после капитана роль принимает на себя заместитель и наоборот!
    //вроде должно сработать. пока не отражено, что капитан назначает первого помощника сам.
    qDebug()<<"game::check_for_role(QString role)";

    QMap <ROLE,ROLE>deprole;
    deprole.insert(RT_DOCTOR,RT_DEP_DOCTOR);
    deprole.insert(RT_GUNMEN,RT_DEP_GUNMEN);
    deprole.insert(RT_ENGINEER,RT_DEP_ENGINEER);
    deprole.insert(RT_SCIENTIST,RT_DEP_SCIENTIST);
    deprole.insert(RT_SIGNALMEN,RT_DEP_SIGNALMEN);
    //deprole.insert("Captain","Assistant");
    deprole.insert(RT_ASSISTANT,RT_CAPTAIN);
    
    if(role == RT_ASSISTANT && (!unclame_rolelist.contains(RT_CAPTAIN)))
    {
        //тут отправка капитану сообщения о том что он должен назначить персонажа-старпома
        //QList<QString> forAssistant;
        if(passengerlist.isEmpty())
        {
            add_role(rolelist.value(RT_CAPTAIN),role);
        }else{
            //connect (_event,SIGNAL(event_useitem(QString,QString,QString)),this,SLOT(check_for_role_capDecision(QString,QString,QString)));
        }
    }else{
        int co = rolelist.count(deprole.value(role));
        if(co == 1)
        {
            //тут будет отправка сообщения о присвоении роли единственному заму
            add_role(rolelist.value(deprole.value(role)),role);
            if(role != RT_CAPTAIN && role != RT_ASSISTANT)
                delete_role(rolelist.value(deprole.value(role)),deprole.value(role));
        }
        if(co > 1)
        {
            //начало голосования среди замов роли
            QList <QString> tmp;
            foreach (player* vvv, playerlist->values()) {
                if(vvv->rolelist.contains(deprole.value(role))){
                    tmp.append(vvv->name);
                }
            }
            votingque.enqueue(new voting(tmp,role));
        }
        if(co == 0){
            //QList <player*> cc;
            QList<QString>cc;
            foreach (ROLE var, deprole.values())
            {
                foreach (player* vvv, playerlist->values())
                {
                    if(vvv->rolelist.contains(deprole.value(var))){
                        if(var != RT_CAPTAIN && var != RT_ASSISTANT)
                            cc.append(vvv->name);
                    }
                }
            }
            cc.append(passengerlist);
            if(cc.count() > 1)
            {
                votingque.enqueue(new voting(cc,role));
            }
            if(cc.count() == 1){
                if(passengerlist.isEmpty()){
                    foreach (ROLE var, deprole.values())
                    {
                        if(!rolelist.values(var).isEmpty())
                        {
                            //тут будет отправка сообщения о присвоении роли единственному левому заму
                            add_role(rolelist.value(var),role);
                            delete_role(rolelist.value(var),var);
                        }
                    }
                } else
                {
                    //тут будет отправка сообщения о присвоении роли единственному пассащиру
                    add_role(playerlist->value(passengerlist.first()),role);
                    passengerlist.clear();
                }
            }
            if(cc.count() == 0){
                int i = 1;
                do{
                    foreach(player* var,rolelist.values()){
                        if(var->rolelist.count() == i){
                            cc.append(var->name);
                        }
                    }
                    i++;
                }while(cc.count() < 1);
                if (cc.count() == 1)
                {
                    //отправка сообщения о присвоении роли игроку с наименьшим числом ролей
                    add_role(playerlist->value(cc.first()),role);
                } else {
                    votingque.enqueue(new voting(cc,role));
                }
            }
        }
    }
}

bool game::isHunted(QStringList playerhunt, TurnObject turn){
    if(!playerhunt.contains(turn.TARGET))
        return false;
    else {
        if (playerlist->value(turn.TARGET)->healthy == false && turn.wh->healthy == false)
            return false;
        else {
            return true;
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
    ITEM itblock;//предмет, использованный капитаном
    QList <QString> playerhunt;//игроки, попадающие под защиту боевика
    QList <QString> attackedhuman;//атакованные чужими люди


    /*while (!_queue.isEmpty()) {
        TurnObject eve = _queue.dequeue();

        if(playerblock.contains(eve.wh->name)) {
            continue;
        } else
            if (playerhunt.contains(eve.wh->name) ) {

            }
            else {
                switch (eve.type) {
                case TT_USE_BADGE:
                    itblock = eve.item;

                case TT_USE_ITEM:
                    if((itblock != eve.item && eve.type == TT_USE_ITEM)
                            || eve.type == TT_USE_BADGE) {
                        if(!playeritemuse.contains(eve.wh->name))
                    }
                default:
                    break;
                }
            }
    }*/

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
                if(playerblock.contains(_eve.TARGET))
                {
                    continue;
                }
        }
        bool AAA = playerhunt.contains(_eve.wh->name);
        bool BBB;
        if(!_eve.targets.isEmpty())
            BBB = playerhunt.contains(_eve.TARGET);
        else BBB = false;
        //адская замена ксору
        if((_eve.type == TT_ULT_ITEM)||
                (_eve.type == TT_ATTACK)||
                (_eve.type == TT_INFECT))
        {
            if((!AAA && BBB) || (!BBB && AAA))
            {
                _eve.wh->HP -= 1;
                continue;
            }
        }
        if(_eve.type == TT_USE_BADGE &&
                itemlist.value(IT_BADGE)->getPower() == 0 &&
                itemlist.value(_eve.item)->getPower() == 0)
        {
            if(_eve.item == IT_MOP)
            {
                if(!playerlist->value(_eve.TARGET)->rolelist.contains(RT_DOCTOR))
                {
                    playerblock.append(_eve.TARGET);
                }
            }
            if(_eve.item == IT_BATTERY)
            {
                playerblock.append(_eve.wh->name);
            }
            if(_eve.item == IT_BLASTER)
            {
                playerhunt.append(_eve.TARGET);
                if(playerlist->value(_eve.TARGET)->healthy == false)
                {
                    foreach (player* vavar, playerlist->values()) {
                        if(vavar->healthy == false && vavar->name != _eve.TARGET)
                            playerhunt.append(vavar->name);
                    }
                }
                playerhunt.append(_eve.wh->name);
            }
            _nightque.enqueue(_eve);
            playeritemuse.append(_eve.wh->name);
            itblock = _eve.item;
            continue;
        }
        
        if((_eve.type == TT_USE_ITEM || _eve.type == TT_ULT_ITEM) &&
                ((_eve.item == itblock) || (playeritemuse.contains(_eve.wh->name))))
        {
            continue;
        }
        if((_eve.type == TT_USE_ITEM) && (_eve.item == IT_SCANNER))
        {
            playeritemuse.append(_eve.wh->name);
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.type == TT_USE_ITEM || _eve.type == TT_ULT_ITEM) && _eve.item == IT_MOP)
        {
            _nightque.enqueue(_eve);
            playeritemuse.append(_eve.wh->name);
            playerblock.append(_eve.TARGET);
            continue;
        }
        
        if((_eve.type == TT_USE_ITEM) && (_eve.item == IT_BATTERY))
        {
            _nightque.enqueue(_eve);
            playeritemuse.append(_eve.wh->name);
            playerblock.append(_eve.wh->name);
            continue;
        }
        if((_eve.type == TT_USE_ITEM)&&(_eve.item == IT_BLASTER))
        {
            _nightque.enqueue(_eve);
            playeritemuse.append(_eve.wh->name);
            if(playerlist->value(_eve.TARGET)->healthy == false)
            {
                foreach (player* vavar, playerlist->values()) {
                    if(vavar->healthy == false)
                        playerhunt.append(vavar->name);
                }
            }else playerhunt.append(_eve.TARGET);
            playerhunt.append(_eve.wh->name);
            continue;
        }
        
        if((_eve.type == TT_ULT_ITEM) && (_eve.item == IT_BATTERY))
        {
            playeritemuse.append(_eve.wh->name);
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.type == TT_ULT_ITEM) && (_eve.item == IT_INJECTOR))
        {
            playeritemuse.append(_eve.wh->name);
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.type == TT_ULT_ITEM) && (_eve.item == IT_SCANNER))
        {
            playeritemuse.append(_eve.wh->name);
            _nightque.enqueue(_eve);
            continue;
        }
        if((_eve.type == TT_ATTACK))
        {
            if(attackedhuman.contains(_eve.TARGET))
            {
                continue;
            }
            if(playerlist->value(_eve.TARGET)->status != 2)
            {
                attackedhuman.append(_eve.TARGET);
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
    switch (TO.type) {
    case TT_ALIEN:
        slot_alien(TO);
        break;
    case TT_ATTACK:
        slot_attack(TO);
        break;
    case TT_USE_ITEM:
        slot_use_item(TO);
        TO.type = TT_CORRECT;
        emit send_stat(TO);
        break;
    case TT_USE_BADGE:
        slot_use_item_cap(TO);
        TO.type = TT_CORRECT;
        emit send_stat(TO);
        break;
    case TT_ULT_ITEM:
        slot_ult_item(TO);
        TO.type = TT_CORRECT;
        emit send_stat(TO);
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

void game::sendMsg(player *who, QString msg)
{
    emit send_mess(who,msg);
}
