#pragma once
#include "GameObject.h"
#include <string>
using namespace std;

class Enemy : public GameObject {
public:
    int hp, maxhp, damage;
    string name;
    Enemy(int _x, int _y,string _name);
    void GetDamage(int _dmg);
    void Logic() override;
    void Death();
};