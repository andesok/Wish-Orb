#include "../include/Enemy.h"
#include "../include/Puddle.h"
#include "../include/Functions.h"
#include <fstream>
#include <vector>
using namespace std;

extern vector<GameObject*> game_objects;
extern int damage;

Enemy::Enemy(int _x, int _y, string _name) : GameObject(_x, _y, 'R', BLUISH, OrderLayers::MAIN), name(_name) {
    ifstream file("assets/enemies/"+_name+".txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            auto string_vect = split(line, ':');
            string name_var = string_vect[0];
            string value_var = string_vect[1];
            if (name_var == "name") {
                name = value_var;
            }
            else if (name_var == "symbol") {
                symbol = value_var[0];
            }
            else if (name_var == "color") {
                color = stoi(value_var);
            }
            else if (name_var == "damage") {
                damage = stoi(value_var);
            }
            else if (name_var == "maxhp") {
                maxhp = stoi(value_var);
                hp = maxhp;
            }
        }
        file.close();
    }
}
void Enemy::Logic() {
    for (auto obj : game_objects) {
        if (obj->x == x && obj->y == y) {
            if (Puddle* r = dynamic_cast<Puddle*>(obj)) GetDamage(damage);
        }
    }
}
void Enemy::GetDamage(int _dmg) {
    hp -= _dmg;
    if (hp <= 0) {
        Death();
    }
}
void Enemy::Death() {
    to_delete = true;
}