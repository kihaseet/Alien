#include "item.h"

item::item()
{
    this->power=0;
}

void item::reforge(int i){
    power=i;
}

void item::counter(){
    if (power>0) power-=1;
}

Badge::Badge(game *_g){
    ID = IT_BADGE;
    name="Значок";
    handle="Badge";
    role="Captain";
    _game=_g;
}

void Badge::use_item_day(){
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
    role = "Assistant";
    _game = _g;
}

void Rotation::use_item_day(QQueue<QString> whom){
    qDebug()<<"Rotation::use_item_day()";
    if(_game->nightrotation.isEmpty()){
        _game->nightrotation = whom;
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
    role = "Gunmen";
    _game = _g;
}

void Blaster::use_item_day(){
    qDebug()<<"Blaster::use_item_day()";
}

void Blaster::use_item_night(QQueue<QString> whom){
    qDebug()<<"Blaster::use_item_night(QString whom)" <<whom;
    _game->playerlist->value(whom)->HP-=2;
    _game->check_HP(whom);
    this->power=2;
}

void Blaster::ult_item(QQueue<QString> whom){
    qDebug()<<"Blaster::ult_item(QString whom)"<<whom;
    _game->playerlist->value(whom)->HP-=2;
    _game->check_HP(whom);
    this->power=-1;
}

Injector::Injector(game *_g)
{
    ID = IT_INJECTOR;
    name = "Шприц";
    handle = "Injector";
    role = "Doctor";
    _game = _g;
}

void Injector::use_item_day(QQueue<QString> whom){
    qDebug()<<"Injector::use_item_day(QString whom)"<<whom;
    _game->playerlist->value(whom)->HP+=2;
    //    if(_game->playerlist.value(whom)->HP>3 && _game->playerlist.value(whom)->status!=2){
    //        _game->playerlist.value(whom)->HP=3;
    //    }

    //    if(_game->playerlist.value(whom)->HP>5 && _game->playerlist.value(whom)->status==2){
    //        _game->playerlist.value(whom)->HP=5;
    //    }
    _game->check_HP(whom);
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
        if(v->healthy==false){
            _game->slot_up(v->name);
        }
        _game->check_HP(v->name);
    }
    this->power=-1;
}

Notebook::Notebook(game *_g)
{
    ID = IT_NOTEBOOK;
    name="Ноутбук";
    handle="Notebook";
    role="Signalmen";
    _game=_g;
}

void Notebook::use_item_day(QQueue<QString> whom){
    qDebug()<<"Notebook::use_item_day(QString whom)"<<whom;
    this->power=2;
}

void Notebook::use_item_night(QQueue<QString> whom){
    qDebug()<<"Notebook::use_item_night()";

}

void Notebook::ult_item(QQueue<QString> whom){
    qDebug()<<"Notebook::ult_item()";
    emit item_voting_all();
    this->power=-1;
}

Battery::Battery(game *_g)
{
    ID = IT_BATTERY;
    name="Батарейка";
    handle="Battery";
    role="Engineer";
    _game=_g;
}

void Battery::use_item_day(QQueue<QString> whom){
    qDebug()<<"Battery::use_item_day(QString whom)"<<whom;
    this->forrepower=_game->itemlist.value(whom)->handle;
}

void Battery::use_item_night(QQueue<QString> whom){
    qDebug()<<"Battery::use_item_night()";
    this->power=2;
}

void Battery::ult_item(QQueue<QString> whom){
    //qDebug()<<"Battery::ult_item(item *whom)";
    _game->itemlist.value(whom)->reforge(this->power);

    _game->brokeitemlist.removeOne(whom);
    if(_game->unclame_rolelist.contains(_game->itemlist.value(whom)->role))
        _game->check_for_role(_game->itemlist.value(whom)->role);
    this->power=-1;
}

Scanner::Scanner(game *_g)
{
    ID = IT_SCANNER;
    name="Сканер";
    handle="Scanner";
    role="Scientist";
    _game=_g;
}

void Scanner::use_item_day(QQueue<QString> whom){
    qDebug()<<"Scanner::use_item_day(QString whom)"<<whom;
    lastscan=qMakePair(whom,_game->playerlist->value(whom)->status);
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
        if(!var->itemlist.keys().contains("Scanner")){
            if(var->status<2){
                var->HP-=1;
            }else{
                var->HP-=3;
                if(_game->daytime)
                    _game->slot_down(var->name);
            }
        }
        _game->check_HP(var->name);
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
