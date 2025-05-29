#include "../include/ThrownPoison.h"
#include "../include/Puddle.h"
#include "../include/Player.h"
#include "../include/Globals.h"
#include <vector>

extern int puddle_size;
extern int puddle_lifetime;

ThrownPoison::ThrownPoison(int _x, int _y, int _direction, int _endX, int _endY)
    : GameObject(_x, _y, '$', GOLD, OrderLayers::MAIN),
    direction(_direction), endX(_endX), endY(_endY){}

void ThrownPoison::Logic() {
    if (!shattered) {
        switch (direction) {
        case LEFT:  x -= 1; break;
        case RIGHT: x += 1; break;
        case UP:    y -= 1; break;
        case DOWN:  y += 1; break;
        }
        if (x == endX && y == endY) {
            shattered = true;
            SpreadPuddle(x, y, puddle_size);
            to_delete = true;
        }
    }
}

void ThrownPoison::SpreadPuddle(int centerX, int centerY, int radius) {
    std::vector<std::vector<bool>> visited(chars_grid.size(), std::vector<bool>(chars_grid[0].size(), false));
    std::vector<std::pair<int, int>> queue;
    queue.push_back({ centerX, centerY });
    visited[centerY][centerX] = true;

    for (int d = 0; d <= radius; d++) {
        std::vector<std::pair<int, int>> next_queue;
        for (auto& point : queue) {
            int px = point.first;
            int py = point.second;

            if (chars_grid[py][px] != '#') {
                auto puddle = new Puddle(px, py, puddle_lifetime);
                to_add.push_back(puddle);

                int dx[] = { -1, 1, 0, 0 };
                int dy[] = { 0, 0, -1, 1 };

                for (int dir = 0; dir < 4; dir++) {
                    int nx = px + dx[dir];
                    int ny = py + dy[dir];

                    if (ny >= 0 && ny < chars_grid.size() &&
                        nx >= 0 && nx < chars_grid[ny].size() &&
                        !visited[ny][nx] && chars_grid[ny][nx] != '#') {
                        visited[ny][nx] = true;
                        next_queue.push_back({ nx, ny });
                    }
                }
            }
        }
        queue = next_queue;
    }
}