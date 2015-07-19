#ifndef TYPES_H
#define TYPES_H

enum TURN_TYPE {
    TT_NOTHING = -1,
    TT_USE_BADGE = 0,
    TT_USE_ITEM,
    TT_ULT_ITEM,
    TT_ATTACK,
    TT_INFECT,
    TT_SKIP,
    TT_ALIEN,
    TT_UP,
    TT_DOWN,
    TT_GETITEM,
    TT_DELITEM,
    TT_VOTE,
    TT_UNVOTE,
    TT_REGNAME,
    TT_REGROLE
};

enum ITEM{
    IT_UNKNOW = -1,
    IT_BADGE = 0,
    IT_INJECTOR,
    IT_SCANNER,
    IT_MOP,
    IT_BATTERY,
    IT_BLASTER,
    IT_NOTEBOOK,
    IT_ROTATION,
    IT_FETUS
};


#endif // TYPES_H
