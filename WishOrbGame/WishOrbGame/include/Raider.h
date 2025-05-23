#pragma once
#include "Constants.h"
#include "Entity.h"
#include "Puddle.h"

class Raider : public Entity {
public:
    Raider(int _x, int _y, int _hp);
    void Logic() override;
    void Death() override;
};