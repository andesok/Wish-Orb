#pragma once
#include "GameObject.h"

class Entity : public GameObject {
public:
    int hp, maxhp;
    Entity(int _x, int _y, char _symbol, int _color, int _layer, int _hp);
    virtual void Logic() = 0;
    virtual void Death() = 0;
    void GetDamage(int _dmg);
};