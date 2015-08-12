#include "item.h"

item::item()
{
    this->power = 0;
}

ITEM item::getID()
{
    return this->ID;
}

QString item::getHandle()
{
    return this->handle;
}

QPair<QString, int> item::getLastScan()
{
    return this->lastscan;
}

int item::getPower()
{
    return this->power;
}

void item::setPower(int charge)
{
    this->power = charge;
}

void item::reforge(int i){
    power=i;
}

void item::counter(){
    if (power > 0) power-=1;
}

Badge::Badge(game *_g){
    ID = IT_BADGE;
    handle = "Badge";
    _game = _g;
}

void Badge::use_item_day(QQueue<QString> whom){
    if(_game->hardresolve)
        _game->dayCapCurrVoting(whom.first());
    else
        _game->check_for_role_capDecision(whom.first());
    qDebug()<<"Badge::use_item_day()";
}

//void Badge::use_item_night(QQueue<QString> whom){
//    qDebug()<<"Badge::use_item_night()";
//}

//void Badge::ult_item(){
//    qDebug()<<"Badge::ult_item()";
//}

Rotation::Rotation(game *_g)
{
    ID = IT_ROTATION;
    handle = "Rotation";
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


Blaster::Blaster(game *_g)
{
    ID = IT_BLASTER;
    handle = "Blaster";
    _game = _g;
}

void Blaster::use_item_night(QQueue<QString> whom){
    qDebug()<<"Blaster::use_item_night(QString whom)" <<whom;
    _game->playerlist->value(whom.first())->HP -= 1;
    _game->check_HP(_game->playerlist->value(whom.first()));
    this->power = 2;
}

void Blaster::ult_item(QQueue<QString> whom){
    qDebug()<<"Blaster::ult_item(QString whom)"<<whom;
    _game->playerlist->value(whom.first())->HP -= 1;
    if(_game->daytime)
        _game->slotDown(TurnObject(TT_DOWN,whom));
    _game->check_HP(_game->playerlist->value(whom.first()));

    this->power = -1;
}

Injector::Injector(game *_g)
{
    ID = IT_INJECTOR;
    handle = "Injector";
    _game = _g;
}

void Injector::use_item_day(QQueue<QString> whom)
{
    qDebug()<<"Injector::use_item_day(QString whom)"<<whom;
    _game->playerlist->value(whom.first())->HP += 1;
    _game->check_HP(_game->playerlist->value(whom.first()));
    if(_game->daytime && _game->playerlist->value(whom.first())->status == 2)
        _game->slotUp(TurnObject(TT_UP,whom));
    this->power = 2;
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
            v->HP=2;
        }
        if(v->status==2){
            v->HP=3;
        }
        if(!v->healthy)
        {
            _game->slotUp(TurnObject(TT_UP,v->name));
        }
    }
    this->power = -1;
}

Notebook::Notebook(game *_g)
{
    ID = IT_NOTEBOOK;
    handle="Notebook";
    _game=_g;
}

void Notebook::use_item_day(QQueue<QString> whom){
    qDebug()<<"Notebook::use_item_day(QString whom)"<<whom;
    if(!_game->_currvoting->is_over)
    {
        _game->_currvoting->setNoteName(whom.first());
        this->power = 2;

    }
    else if(_game->hardresolve)
    {
        this->power = 2;
        _game->dayEndCurrVoting(whom.first());
    }
}


void Notebook::ult_item(QQueue<QString> whom){
    qDebug()<<"Notebook::ult_item()";
    if(!_game->_currvoting->is_over || _game->hardresolve)
    {
        this->power=-1;
        _game->dayCanseledVoting();
    }
}

Battery::Battery(game *_g)
{
    ID = IT_BATTERY;
    handle="Battery";
    _game=_g;
}

void Battery::use_item_day(QQueue<QString> whom){
    qDebug()<<"Battery::use_item_day(QString whom)"<<whom;
    _game->forrepowered = TurnObject::ItemDescr.value(whom.first());
}

void Battery::use_item_night(QQueue<QString> whom){
    qDebug()<<"Battery::use_item_night()";
    this->power = 2;
}

void Battery::ult_item(QQueue<QString> whom){
    //qDebug()<<"Battery::ult_item(item *whom)";
    _game->forrepowered = IT_UNKNOW;
    ITEM what = TurnObject::ItemDescr.value(whom.first());
    _game->itemlist.value(what)->reforge(this->power);

    _game->brokeitemlist.removeOne(what);
    if(_game->unclame_rolelist.contains(TurnObject::RoleItem.key(what)))
        _game->check_for_role(TurnObject::RoleItem.key(what));
    this->power = -1;
}

Scanner::Scanner(game *_g)
{
    ID = IT_SCANNER;
    handle="Scanner";
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

    qDebug()<<"Scanner::ult_item()";
    foreach (player* var, _game->playerlist->values()) {
        if(!var->itemlist.contains(IT_SCANNER))
        {
            if(var->status < 2){
                var->HP -= 1;
            }else{
                var->HP -= 2;
                if(_game->daytime)
                {
                    _game->slotDown(TurnObject(TT_DOWN,var->name));
                }
            }
        }
        _game->check_HP(var);
    }
    this->power = -1;
}

Mop::Mop(game *_g)
{
    ID = IT_MOP;
    handle="Mop";
    _game=_g;
}

void Mop::use_item_night(QQueue<QString> whom){
    qDebug()<<"Mop::use_item_night()"<<whom;
}

