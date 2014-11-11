#include "item.h"

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
}

void Badge::use_item(){

}

void Badge::ult_item(){

}

Rotation::Rotation(){
    name="График дежурств";
    handle="Rotation";
}

void Rotation::use_item(){

}

void Rotation::ult_item(){

}

Blaster::Blaster(){
    name="Бластер";
    handle="Blaster";
}

void Blaster::use_item(){

}

void Blaster::ult_item(){

}

Injector::Injector(){
    name="Шприц";
    handle="Injector";
}

void Injector::use_item(){

}

void Injector::ult_item(){

}

Notebook::Notebook(){
    name="Ноутбук";
    handle="Notebook";
}

void Notebook::use_item(){

}

void Notebook::ult_item(){

}

Battery::Battery(){
    name="Батарейка";
    handle="Battery";
}

void Battery::use_item(){

}

void Battery::ult_item(){

}

Scanner::Scanner(){
    name="Сканер";
    handle="Scanner";
}

void Scanner::use_item(){

}

void Scanner::ult_item(){

}

Mop::Mop(){
    name="Швабра";
    handle="Mop";
}

void Mop::use_item(){

}

void Mop::ult_item(){

}
