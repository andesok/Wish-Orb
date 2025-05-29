#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>

#include "../include/Functions.h"
#include "../include/GameObject.h"
#include "../include/Player.h"
#include "../include/Puddle.h"
#include "../include/ThrownPoison.h"
#include "../include/ThrowTarget.h"
#include "../include/Enemy.h"
#include "../include/Globals.h"

using namespace std;

int game_delay = 300;
int damage;
int puddle_size;
int puddle_lifetime;
int throw_distance;
int maxhp;
int hp;

vector<GameObject*> to_add;
vector<GameObject*> to_remove;
vector<GameObject*> game_objects;
vector<vector<char>> chars_grid;
vector<char> chars_row;

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void DeleteObject(GameObject* obj) {
    if (!obj) return;  
    game_objects.erase(remove(game_objects.begin(), game_objects.end(), obj), game_objects.end());
    delete obj;
}
void Setup() {
    ifstream playerstats_file("assets/playerstats.txt");
    if (playerstats_file.is_open()) {
        string line;
        while (getline(playerstats_file, line)) {
            auto string_vect = split(line, ':');
            string name_var = string_vect[0];
            int value_var = stoi(string_vect[1]);
            if (name_var == "damage") {
                damage = value_var;
            }
            else if (name_var == "puddle_size") {
                puddle_size = value_var;
            }
            else if (name_var == "puddle_lifetime") {
                puddle_lifetime = value_var;
            }
            else if (name_var == "throw_distance") {
                throw_distance = value_var;
            }
            else if (name_var == "maxhp") {
                maxhp = value_var;
                hp = maxhp;
            }
        }
        playerstats_file.close();
    }

    ifstream level_file("assets/levels/level0.txt");
    if (level_file.is_open()) {
        string line;
        while (getline(level_file, line)) {
            chars_row.clear();
            for (char c : line) {
                chars_row.push_back(c);
            }
            chars_grid.push_back(chars_row);
        }
        level_file.close();
    }

}

void Draw(Player& player) {
    system("cls");
    SetColor(WHITE);
    cout << "Objects: " << game_objects.size() << endl;
    cout << "HP: " << hp << "/" << maxhp << endl;
    cout << endl;
    int x_check = 0, y_check = 0;
    for (auto& chars_row : chars_grid) {
        x_check = 0;
        for (char c : chars_row) {
            GameObject* top_object = nullptr;
            for (auto obj : game_objects) {
                if (obj->x == x_check && obj->y == y_check) {
                    if (!top_object || obj->layer > top_object->layer) {
                        top_object = obj;
                    }
                }
            }
            if (top_object) {
                SetColor(top_object->color);
                cout << top_object->symbol;
            }
            else {
                SetColor(CharColors::GREY);
                cout << chars_grid[y_check][x_check];
            }
            cout << " ";
            x_check++;
        }
        y_check++;
        cout << endl;
    }
}
void Input(Player& player) {
    player.direction = player.directions::NONE;
    if (_kbhit()) {
        switch (_getch()) {
        case 224:
            if (!player.poison_throw) {
                switch (_getch()) {
                case 75:
                    player.direction = player.directions::LEFT;
                    player.poison_throw_dir = player.direction;
                    break;
                case 77:
                    player.direction = player.directions::RIGHT;
                    player.poison_throw_dir = player.direction;
                    break;
                case 72:
                    player.direction = player.directions::UP;
                    player.poison_throw_dir = player.direction;
                    break;
                case 80:
                    player.direction = player.directions::DOWN;
                    player.poison_throw_dir = player.direction;
                    break;
                }
            }
            else if (player.poison_throw) {
                switch (_getch()) {
                case 75: player.poison_throw_dir = player.directions::LEFT; break;
                case 77: player.poison_throw_dir = player.directions::RIGHT; break;
                case 72: player.poison_throw_dir = player.directions::UP; break;
                case 80: player.poison_throw_dir = player.directions::DOWN; break;
                }
            }
            break;
        case 'z':
            if (!player.poison_throw) player.poison_throw = true;
            else if ((chars_grid[player.y][player.x - 1] != '#' && player.poison_throw_dir == player.directions::LEFT)
                || (chars_grid[player.y][player.x + 1] != '#' && player.poison_throw_dir == player.directions::RIGHT)
                || (chars_grid[player.y - 1][player.x] != '#' && player.poison_throw_dir == player.directions::UP)
                || (chars_grid[player.y + 1][player.x] != '#' && player.poison_throw_dir == player.directions::DOWN)) {
                player.poison_throw_fire = true;
            }
            break;
        case 'x':
            if (player.poison_throw && !player.poison_throw_fire) {
                player.poison_throw = false;
                player.target_created = false;
                DeleteObject(player.target);
                player.target = nullptr;
            }
            break;
        }
    }

}
void PlayerMovement(Player& player) {

    //Движение игрока
    player.vspd = 0;
    player.hspd = 0;
    switch (player.direction) {
    case player.directions::LEFT: player.hspd = -1; break;
    case player.directions::RIGHT: player.hspd = 1; break;
    case player.directions::UP: player.vspd = -1; break;
    case player.directions::DOWN: player.vspd = 1; break;
    }
    int newX = player.x + player.hspd;
    int newY = player.y + player.vspd;
    if (newY >= 0 && newY < chars_grid.size() &&
        newX >= 0 && newX < chars_grid[newY].size()) {
        if (chars_grid[newY][newX] != '#') {
            player.x = newX;
            player.y = newY;
        }
    }

    // Бросок зелья
    if (player.poison_throw) {
        int targetX = player.x; int targetY = player.y;
        switch (player.poison_throw_dir) {
        case player.directions::LEFT:
            for (int i = 0; i < throw_distance; i++) {
                if (chars_grid[targetY][targetX - 1] == '#') break;
                targetX -= 1;
            }
            break;
        case player.directions::RIGHT:
            for (int i = 0; i < throw_distance; i++) {
                if (chars_grid[targetY][targetX + 1] == '#') break;
                targetX += 1;
            }
            break;
        case player.directions::UP:
            for (int i = 0; i < throw_distance; i++) {
                if (chars_grid[targetY - 1][targetX] == '#') break;
                targetY -= 1;
            }
            break;
        case player.directions::DOWN:
            for (int i = 0; i < throw_distance; i++) {
                if (chars_grid[targetY + 1][targetX] == '#') break;
                targetY += 1;
            }
            break;
        }

        if (targetY >= 0 && targetY < chars_grid.size() &&
            targetX >= 0 && targetX < chars_grid[targetY].size() && !player.target_created) {
            player.target_created = true;
            player.target = new ThrowTarget(targetX, targetY);
            to_add.push_back(player.target);
        }

        if (player.target) {
            player.target->x = targetX;
            player.target->y = targetY;
        }

        if (player.poison_throw_fire && player.target) {
            auto thrown_poison = new ThrownPoison(player.x, player.y, player.poison_throw_dir, player.target->x, player.target->y);
            to_add.push_back(thrown_poison);
            DeleteObject(player.target);
            player.target = nullptr;
            player.poison_throw = false;
            player.poison_throw_fire = false;
            player.target_created = false;
        }
    }
}
void WorldLogic() {

    //Удаление объектов
    for (auto obj : game_objects) {
        if (obj->to_delete) to_remove.push_back(obj);;
    }
    if (!to_remove.empty()) {
        for (auto obj : to_remove) {
            DeleteObject(obj);
        }
        to_remove.clear();
    }

    //Добавление объектов
    if (!to_add.empty()) {
        game_objects.insert(game_objects.end(), to_add.begin(), to_add.end());
        to_add.clear();
    }

    //Обработка объектов
    for (auto obj : game_objects) {
        obj->Logic();
    }

};

int main()
{
    Setup();
    Player* player = new Player(5,5);
    Enemy* enemy = new Enemy(15,5,"megaslime");
    game_objects.push_back(player);
    game_objects.push_back(enemy);
    while (true) {
        Input(*player);
        PlayerMovement(*player);
        WorldLogic();
        Draw(*player);

        Sleep(game_delay);
    }

    return 0;
}