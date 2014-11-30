#include "event.h"

ingame_event::ingame_event(QString wh, QString whm, QString wht, QString it,QList rot)
{
    if(wh!="")this->who=wh;
    if(whm!="")this->whom=whm;
    if(wht!="")this->what=wht;
    if(it!="")useit=it;
    if(!rot.isEmpty())rota=rot;
}

void ingame_event::do_event(){
    switch (this->what){
    case "alien":
    {emit event_alien(this->who);break;}

    case "attack":
    {emit event_attack(this->who,this->whom);break;}

    case "useitem":
    {
        if(rota.isEmpty())emit event_useitem(this->who,this->whom,this->useit);
        else emit event_useitemrot(this->rota);
        break;
    }

    case "useitemCap":
    {emit event_useitemcap(this->who,this->whom,this->useit);break;}

    case "ultitem":
    {emit event_ultitem(this->who,this->whom,this->useit);break;}

    case "wait":
    {emit event_wait(this->who);break;}

    case "up":
    {emit event_up(this->who);break;}

    case "down":
    {emit event_down(this->who);break;}

    case "infect":
    {emit event_infect(this->who,this->whom);break;}

    case "vote":
    {emit event_vote(this->who,this->whom);break;}

    case "unvote":
    {emit event_unvote(this->who);break;}

    default:{emit event_norecognize();}
    }
}
