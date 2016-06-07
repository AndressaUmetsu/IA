#include <cstdio>
#include <cstdlib>

#include "robo.h"
#include "main.h"

void update_pos(_robo *robo, _square **map){
    if ( robo->tomove.size() == 0 ) {
        fprintf(stderr, "Robot has no moves left!!\n");
        abort();
        //robo_pickup_item(robo, map);
    } else if ( robo->canMove ) {
        robo->pos = robo->tomove.back();
        robo->tomove.pop_back();
        robo->nMoves++;
        map[robo->pos.x][robo->pos.y].path = false;
    } else {
        robo->canMove = true;
    }
}

void init_robo(_robo *robo){
    robo->nMoves    = 0;
    robo->totalCost = 0;
    robo->goingTo.x = -1;
    robo->goingTo.y = -1;
    robo->canMove   = false;
    robo->pos.x     = rand() % 42;
    robo->pos.y     = rand() % 42;
    robo->action    = SEARCH;

    for (int i = 0; i < 42; ++i) {
        for (int j = 0; j < 42; ++j) {
            _pos pos;
            pos.x = i;
            pos.y = j;
            robo->notVisited.push_back(pos);
        }
    }
}

void update_visited(_robo *robo, _pos pos){
    for (int i = 0; i < (int)robo->visited.size(); ++i) {
        if ( robo->visited[i].x == pos.x && robo->visited[i].y == pos.y ) {

        } else {
            robo->visited.push_back(pos);
            for (int j = 0; j < (int)robo->notVisited.size(); ++j) {
                if ( robo->notVisited[i].x == pos.x && robo->notVisited[i].y == pos.y ) {
                    robo->notVisited.erase(robo->notVisited.begin() + i);
                    break;
                }
            }
        }
    }
}

std::vector<_item_pos> vision(_robo *robo, _square **map){
    std::vector<_item_pos> saw;
    int radius = 4;

    for (int i = -radius + robo->pos.x; i < radius + robo->pos.x; ++i) {
        if ( i < 0 || i > 41 ) continue;
        for (int j = -radius + robo->pos.y; j < radius + robo->pos.y; ++j) {
            if ( j < 0 || j > 41 ) continue;

            _pos pos;
            pos.x  = i;
            pos.y  = j;

            update_visited(robo, pos);

            if ( map[i][j].item != NENHUM && map[i][j].isItem ) {
                _item_pos s;
                s.pos  = pos;
                s.item = map[i][j].item;
                saw.push_back(s);
            }
        }
    }

    return saw;
}

void robo_pickup_item(_robo *robo, _square **map){
    int x = robo->pos.x;
    int y = robo->pos.y;

    if ( map[x][y].isItem || ( !map[x][y].isFabrica && map[x][y].item != NENHUM ) ) {
        robo->bag.push_back(map[x][y].item);
        map[x][y].isItem = false;
        printf("Robot @ (%2d, %2d) picked up %d\n", x, y, map[x][y].item);
        map[x][y].item   = NENHUM;
    } else {
        fprintf(stderr, "NOOOOOOO\n");
        abort();
    }
}

_pos get_random_pos(_robo robo){
    double chance = 1.0/(double)robo.notVisited.size();
    _pos pos;
    pos.x = -1;
    pos.y = -1;
    while ( true ) {
        for (int i = 0; i < (int)robo.notVisited.size(); ++i) {
            if ( drand48() < chance ) {
                pos = robo.notVisited[i];
                return pos;
            }
        }
    }
}
