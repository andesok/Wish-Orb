#include "../include/Puddle.h"

extern int damage;

Puddle::Puddle(int _x, int _y, int _lifetime)
    : GameObject(_x, _y, '*', RED, OrderLayers::BG), lifetime(_lifetime){}

void Puddle::Logic() {
    lifetime--;
    if (lifetime <= 0) to_delete = true;
}