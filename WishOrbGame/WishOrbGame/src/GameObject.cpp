#include "../include/GameObject.h"

GameObject::GameObject(int _x, int _y, char _symbol, int _color, int _layer)
    : x(_x), y(_y), symbol(_symbol), color(_color), layer(_layer), to_delete(false) {}
GameObject::~GameObject() {}