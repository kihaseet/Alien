#include "game.h"

game::game()
{
    votingque.clear();
    daytime=true;
    rolelist.insert("Captain",NULL);
    rolelist.insert("Doctor",NULL);
    rolelist.insert("Gunmen",NULL);
    rolelist.insert("Assistant",NULL);
    rolelist.insert("Engineer",NULL);
    rolelist.insert("Scientist",NULL);
    rolelist.insert("Signalmen",NULL);

    connect(this,SIGNAL(startday()),SLOT(day()));
    connect(this,SIGNAL(startnight()),SLOT(night()));
    connect(this,SIGNAL(startgame()),SLOT(start()));

}

void game::day(){
    daytime=true;
    while (!votingque.isEmpty())
    {
        voting* current_voting = votingque.dequeue();
        connect (_event,SIGNAL(event_vote()),current_voting,SLOT(on_voting(player,player)));
        connect (_event,SIGNAL(event_useitem()),this,SLOT(use_item(QString)));
    }
}

void game::night(){

}

void game::start(){
    votingque.enqueue(new voting(playerlist,"Alien"));
}

void game::make_events(QString who,QString whm,QString what,QString how){
    player _who,_whom;
    item _how;
    ingame_event new_event;

    if (playerlist.contains(who) && playerlist.contains(whm)){
        _who = playerlist.value(who);
        _whom = playerlist.value(whm);
        if (!how.isNull()){
            if(playerlist.value(who).itemlist.contains(how)){
                _how = playerlist.value(who).itemlist.value(how);
            }
        } else _how = NULL;
        new_event=new ingame_event(_who,_whom,what,_how);
        if (this->daytime){
            _event=new_event;
            _event->do_event();
        }
    }
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
