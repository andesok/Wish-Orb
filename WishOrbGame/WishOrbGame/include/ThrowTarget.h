#pragma once
#include "Constants.h"
#include "GameObject.h"

class ThrowTarget : public GameObject {
public:
    ThrowTarget(int _x, int _y);

    void Logic() override;
};