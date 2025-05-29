#pragma once
#include <vector>
#include "GameObject.h"

extern std::vector<GameObject*> to_add;
extern std::vector<GameObject*> to_remove;
extern std::vector<GameObject*> game_objects;
extern std::vector<std::vector<char>> chars_grid;
extern std::vector<char> chars_row;