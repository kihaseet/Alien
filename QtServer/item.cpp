#include "item.h"
#include "player.h"

item::item()
{
    this->power=0;
}

void item::reforge(int i){
    power=i;
}

void item::counter(){
    if (power>0) power=power-1;
}

Badge::Badge(){
    name="Капитанский значок";
    handle="Badge";
    role="Captain";
}

void Badge::use_item_day(){

}

void Badge::use_item_night(){

}

void Badge::ult_item(){

}

Rotation::Rotation(){
    name="График дежурств";
    handle="Rotation";
    role="Assistant";
}

void Rotation::use_item_day(){

}

void Rotation::use_item_night(){

}

void Rotation::ult_item(){

}

Blaster::Blaster(){
    name="Бластер";
    handle="Blaster";
    role="Gunmen";
}

void Blaster::use_item_day(){
}

void Blaster::use_item_night(player* whom){
    whom->HP=whom->HP-2;
    this->power=2;
}

void Blaster::ult_item(player* whom){
    whom->HP=whom->HP-2;
    this->power=-1;
}

Injector::Injector(){
    name="Шприц";
    handle="Injector";
    role="Doctor";
}

void Injector::use_item_day(player* whom){
    whom->HP=whom->HP+2;
    if(whom->HP>3 && whom->status!=2){
        whom->HP=3;
    }

    if(whom->HP>5 && whom->status==2){
        whom->HP=5;
    }
    this->power=2;

}

void Injector::use_item_night(player* whom){
    whom->HP=whom->HP+2;
    if(whom->HP>3 && whom->status!=2){
        whom->HP=3;
    }

    if(whom->HP>5 && whom->status==2){
        whom->HP=5;
    }
    this->power=2;

}

void Injector::ult_item(){
    emit item_heal_all();
    this->power=-1;
}

Notebook::Notebook(){
    name="Ноутбук";
    handle="Notebook";
    role="Signalmen";
}

void Notebook::use_item_day(player *whom){

}

void Notebook::use_item_night(){

}

void Notebook::ult_item(){
    emit item_voting_all();
    this->power=-1;
}

Battery::Battery(){
    name="Батарейка";
    handle="Battery";
    role="Engineer";
}

void Battery::use_item_day(item* whom){
        this->forrepower=whom->handle;
}

void Battery::use_item_night(){
    this->power=2;
}

void Battery::ult_item(item *whom){

}

Scanner::Scanner(){
    name="Сканер";
    handle="Scanner";
    role="Scientist";
}

void Scanner::use_item_day(player* whom){
    lastscan=whom->status;
    this->power=2;
}

void Scanner::use_item_night(player* whom){
    lastscan=whom->status;
    this->power=2;
}

void Scanner::ult_item(){
    emit item_scan_all();
    this->power=-1;
}

Mop::Mop(){
    name="Швабра";
    handle="Mop";
}

void Mop::use_item_day(){

}

void Mop::use_item_night(player* whom){

}

void Mop::ult_item(){

}

Fetus::Fetus(){
    name="Эмбрион";
    handle="fetus";
}

void Fetus::use_item_day(){

}

void Fetus::use_item_night(player *whom){

}

void Fetus::ult_item(){

}
