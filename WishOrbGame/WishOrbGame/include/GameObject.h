#pragma once

class GameObject {
public:
    int x, y, layer;
    char symbol;
    int color;
    bool to_delete = false;

    GameObject(int _x, int _y, char _symbol, int _color, int _layer);
    virtual void Logic() = 0;
    virtual ~GameObject();
};