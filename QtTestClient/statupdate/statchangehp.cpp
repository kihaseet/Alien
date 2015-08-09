#include "statchangehp.h"

StatChangeHP::StatChangeHP(int HP)
{
    this->HP = HP;
}

void StatChangeHP::apply(CurrentPlayer &player)
{
    player.setHP(this->HP);
}
