#include "statchangehp.h"

StatChangeHP::StatChangeHP(int HP)
{
    this->HP = HP;
}

StatChangeHP::StatChangeHP(const StatChangeHP &s)
{
    this->HP = s.HP;
}

void StatChangeHP::apply(CurrentPlayer &player) const
{
    player.setHP(this->HP);
}
