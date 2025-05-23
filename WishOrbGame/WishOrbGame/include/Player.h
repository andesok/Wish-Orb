#pragma once
#include "Entity.h"

class Player : public Entity {
public:
    enum directions { LEFT, RIGHT, UP, DOWN, NONE };
    int vspd = 0, hspd = 0, direction = directions::NONE, poison_throw_dir = directions::RIGHT;
    bool poison_throw = false, target_created = false, poison_throw_fire = false;
    class ThrowTarget* target = nullptr;

    Player(int _x, int _y, int _hp);

    void Logic() override;
    void Death() override;
};