#include "../include/Player.h"
#include "../include/Constants.h"

using namespace std;

Player::Player(int _x, int _y)
    : GameObject(_x, _y, 'A', REDISH, OrderLayers::PLAYER){}

void Player::Logic() {}