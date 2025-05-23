#pragma once
#include "Constants.h"
#include "GameObject.h"

class Player;

class Puddle : public GameObject {
private:
    Player* player = nullptr;
    int lifetime;
public:
    Puddle(int _x, int _y, int _lifetime);
    void Logic() override;
};