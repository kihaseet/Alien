#include "event.h"

ingame_event::ingame_event(QString wh, QString whm, QString wht, QString it, QQueue<QString> rot)
{
    if(wh!="")this->who=wh;
    if(whm!="")this->whom=whm;
    if(wht!="")this->what=wht;
    if(it!="")useit=it;
    if(!rot.isEmpty())rota=rot;
}
ingame_event::ingame_event(QString wh, QString whm, QString wht, QString it)
{
    if(wh!="")this->who=wh;
    if(whm!="")this->whom=whm;
    if(wht!="")this->what=wht;
    if(it!="")useit=it;
}

void ingame_event::do_event(){
    qDebug()<<"ingame_event::do_event()"<<this->who<<this->what<<whom<<useit;

    if(this->what=="alien")
    {emit event_alien(this->who);}

    if(this->what=="attack")
    {emit event_attack(this->who,this->whom);}

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
