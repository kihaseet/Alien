#include "item.h"

item::item()
{
    this->power=0;
}

void item::reforge(int i){
    power=i;
}

void item::counter(){
    if (power > 0) power-=1;
}

Badge::Badge(game *_g){
    ID = IT_BADGE;
    name = "Значок";
    handle = "Badge";
    role = RT_CAPTAIN;
    _game = _g;
}

void Badge::use_item_day(QQueue<QString> whom){
    if(_game->hardresolve)
        _game->day_cap_curr_voting(whom.first());
    else
        _game->check_for_role_capDecision(whom.first());
    qDebug()<<"Badge::use_item_day()";
}

void Badge::use_item_night(){
    qDebug()<<"Badge::use_item_night()";
}

void Badge::ult_item(){
    qDebug()<<"Badge::ult_item()";
}

Rotation::Rotation(game *_g)
{
    ID = IT_ROTATION;
    name = "График";
    handle = "Rotation";
    role = RT_ASSISTANT;
    _game = _g;
}

void Rotation::use_item_day(QQueue<QString> whom){
    qDebug()<<"Rotation::use_item_day()";
    if(_game->nightrotation.isEmpty())
    {
        _game->nightrotation.append(whom);
        foreach (player* gtr, _game->playerlist->values()){
            if(_game->nightrotation.contains(gtr->name)){
                gtr->ImDuty = true;
            }
        }
    }
    _game->day_check_over();
}

void Rotation::use_item_night(){
    qDebug()<<"Rotation::use_item_night()";
}

void Rotation::ult_item(){
    qDebug()<<"Rotation::ult_item()";
}

Blaster::Blaster(game *_g)
{
    ID = IT_BLASTER;
    name = "Бластер";
    handle = "Blaster";
    role = RT_GUNMEN;
    _game = _g;
}

void Blaster::use_item_day(){
    qDebug()<<"Blaster::use_item_day()";
}

void Blaster::use_item_night(QQueue<QString> whom){
    qDebug()<<"Blaster::use_item_night(QString whom)" <<whom;
    _game->playerlist->value(whom.first())->HP-=2;
    _game->check_HP(_game->playerlist->value(whom.first()));
    this->power=2;
}

void Blaster::ult_item(QQueue<QString> whom){
    qDebug()<<"Blaster::ult_item(QString whom)"<<whom;
    _game->playerlist->value(whom.first())->HP-=2;
    _game->check_HP(_game->playerlist->value(whom.first()));
    this->power=-1;
}

Injector::Injector(game *_g)
{
    ID = IT_INJECTOR;
    name = "Шприц";
    handle = "Injector";
    role = RT_DOCTOR;
    _game = _g;
}

void Injector::use_item_day(QQueue<QString> whom){
    qDebug()<<"Injector::use_item_day(QString whom)"<<whom;
    _game->playerlist->value(whom.first())->HP+=2;
    //    if(_game->playerlist.value(whom)->HP>3 && _game->playerlist.value(whom)->status!=2){
    //        _game->playerlist.value(whom)->HP=3;
    //    }

    //    if(_game->playerlist.value(whom)->HP>5 && _game->playerlist.value(whom)->status==2){
    //        _game->playerlist.value(whom)->HP=5;
    //    }
    _game->check_HP(_game->playerlist->value(whom.first()));
    this->power=2;

}

void Injector::use_item_night(QQueue<QString> whom){
    qDebug()<<"Injector::use_item_night(QString whom)";
    this->use_item_day(whom);
}

void Injector::ult_item(QQueue<QString> whom){
    qDebug()<<"Injector::ult_item()";
    //emit item_heal_all();
    foreach (player* v, _game->playerlist->values()) {
        if(v->status<2){
            v->HP=3;
        }
        if(v->status==2){
            v->HP=5;
        }
        if(v->healthy==false)
        {
            TurnObject turn;
            turn.wh = v;
            _game->slot_up(turn);
        }
        _game->check_HP(v);
    }
    this->power=-1;
}

Notebook::Notebook(game *_g)
{
    ID = IT_NOTEBOOK;
    name="Ноутбук";
    handle="Notebook";
    role = RT_SIGNALMEN;
    _game=_g;
}

void Notebook::use_item_day(QQueue<QString> whom){
    qDebug()<<"Notebook::use_item_day(QString whom)"<<whom;
    if(!_game->_currvoting->is_over)
    {
        _game->_currvoting->noteName = whom.first();
        this->power = 2;

    }
    else if(_game->hardresolve)
    {
        this->power = 2;
        _game->day_end_curr_voting(whom.first());
    }
}

void Notebook::use_item_night(QQueue<QString> whom){
    qDebug()<<"Notebook::use_item_night()";

}

void Notebook::ult_item(QQueue<QString> whom){
    qDebug()<<"Notebook::ult_item()";
    if(!_game->_currvoting->is_over || _game->hardresolve)
    {
        this->power=-1;
        _game->day_canseled_voting();
    }
}

Battery::Battery(game *_g)
{
    ID = IT_BATTERY;
    name="Батарейка";
    handle="Battery";
    role = RT_ENGINEER;
    _game=_g;
}

void Battery::use_item_day(QQueue<QString> whom){
    qDebug()<<"Battery::use_item_day(QString whom)"<<whom;
    this->forrepower = TurnObject::ItemDescr.value(whom.first());
}

void Battery::use_item_night(QQueue<QString> whom){
    qDebug()<<"Battery::use_item_night()";
    this->power=2;
}

void Battery::ult_item(QQueue<QString> whom){
    //qDebug()<<"Battery::ult_item(item *whom)";
    ITEM what = TurnObject::ItemDescr.value(whom.first());
    _game->itemlist.value(what)->reforge(this->power);

    _game->brokeitemlist.removeOne(what);
    if(_game->unclame_rolelist.contains(_game->itemlist.value(what)->role))
        _game->check_for_role(_game->itemlist.value(what)->role);
    this->power=-1;
}

Scanner::Scanner(game *_g)
{
    ID = IT_SCANNER;
    name="Сканер";
    handle="Scanner";
    role = RT_SCIENTIST;
    _game=_g;
}

void Scanner::use_item_day(QQueue<QString> whom){
    qDebug()<<"Scanner::use_item_day(QString whom)"<<whom;
    lastscan=qMakePair(whom.first(),_game->playerlist->value(whom.first())->status);
    //emit _game->GuiMess2Log("[Scanner]","показания сканера - "+lastscan.first+" "+QString::number(lastscan.second));
    this->power=2;
}

void Scanner::use_item_night(QQueue<QString> whom){
    qDebug()<<"Scanner::use_item_night(QString whom)"<<whom;
    this->use_item_day(whom);
}

void Scanner::ult_item(QQueue<QString> whom){
    //emit item_scan_all();
    qDebug()<<"Scanner::ult_item()";
    foreach (player* var, _game->playerlist->values()) {
        if(!var->itemlist.contains(IT_SCANNER))
        {
            if(var->status<2){
                var->HP-=1;
            }else{
                var->HP-=3;
                if(_game->daytime)
                {
                    TurnObject turn;
                    turn.wh = var;
                    _game->slot_down(turn);
                }
            }
        }
        _game->check_HP(var);
    }
    this->power=-1;
}

Mop::Mop(game *_g)
{
    ID = IT_MOP;
    name="Швабра";
    handle="Mop";
    _game=_g;
}

void Mop::use_item_day(){
    qDebug()<<"Mop::use_item_day()";
}

void Mop::use_item_night(QQueue<QString> whom){
    qDebug()<<"Mop::use_item_night()"<<whom;
}

void Mop::ult_item(){
    qDebug()<<"Mop::ult_item()";
}
