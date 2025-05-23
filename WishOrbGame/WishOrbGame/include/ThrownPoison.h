#pragma once
#include "Constants.h"
#include "GameObject.h"
#include "Player.h"

class Player;
class Puddle;

class ThrownPoison : public GameObject {
public:
    enum directions { LEFT, RIGHT, UP, DOWN, NONE };

    ThrownPoison(int _x, int _y, int _direction, int _endX, int _endY);

    void Logic() override;

private:
    Puddle* puddle = nullptr;
    int direction;
    int endX, endY;
    int lifetime = 5;
    bool shattered = false;

    void SpreadPuddle(int centerX, int centerY, int radius);
};
