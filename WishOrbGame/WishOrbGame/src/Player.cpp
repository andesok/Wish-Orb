#include "../include/Player.h"
#include "../include/ThrownPoison.h"

Player::Player(int _x, int _y, int _hp)
    : Entity(_x, _y, 'A', REDISH, OrderLayers::PLAYER, _hp){}

void Player::Logic() {}

void Player::Death() {
    to_delete = true;
}