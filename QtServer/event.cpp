#include "event.h"

ingame_event::ingame_event(player wh, player whm, QString wht, item it)
{
    this->who=wh;
    this->whom=whm;
    this->what=wht;
    if(it!=NULL)useit=it;
}

void ingame_event::do_event(){
    switch (this->what){
    case "attack":
    {emit event_attack();break;}

    case "useitem":
    {emit event_useitem();break;}

    case "ultitem":
    {emit event_ultitem();break;}

    case "wait":
    {emit event_wait();break;}

    case "up":
    {emit event_up();break;}

    case "down":
    {emit event_down();break;}

    case "infect":
    {emit event_infect();break;}

    case "vote":
    {emit event_vote();break;}

    default:{emit event_norecognize();}
    }
}
