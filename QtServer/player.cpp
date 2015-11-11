#include "player.h"

player::player(QString n, int id)
{
    this->healthy=true;
    this->waiting=false;
    this->name=n;
    this->SocketId=id;
    this->status=0;
    this->HP=3;
    this->invasion=-1;
    this->success_attack=0;
}
