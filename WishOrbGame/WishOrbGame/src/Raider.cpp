#include "../include/Raider.h"
#include "../include/GameObject.h"
#include <vector>
using namespace std;

extern vector<GameObject*> game_objects;
extern int damage;

Raider::Raider(int _x, int _y, int _hp) : Entity(_x, _y, 'R', BLUISH, OrderLayers::MAIN, _hp) {}
void Raider::Logic() {
    for (auto obj : game_objects) {
        if (obj->x == x && obj->y == y) {
            if (Puddle* r = dynamic_cast<Puddle*>(obj)) GetDamage(damage);
        }
    }
}
void Raider::Death() {
    to_delete = true;
}