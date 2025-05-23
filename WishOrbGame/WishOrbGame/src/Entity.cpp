#include "../include/Entity.h"

Entity::Entity(int _x, int _y, char _symbol, int _color, int _layer, int _hp) : GameObject(_x, _y, _symbol, _color, _layer), hp(_hp), maxhp(_hp) {}

void Entity::GetDamage(int _dmg) {
        hp -= _dmg;
        if (hp <= 0) {
            Death();
        }
    }