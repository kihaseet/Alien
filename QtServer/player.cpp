#include "player.h"

player::player(QString n)
{
    this->healthy=true;
    this->waiting=false;
    this->name=n;
    this->status=0;
    this->HP=0;
    this->success_attack=0;
}
