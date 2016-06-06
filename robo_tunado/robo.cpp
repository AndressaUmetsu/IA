#include <cstdlib>

#include "robo.h"
#include "main.h"

void update_pos(_robo *robo, _square **map){
    if ( robo->tomove.size() == 0 ) {
        fprintf(stderr, "Robot has no moves left!!\n");
        abort();
    } else {
        robo->pos = robo->tomove.back();
        robo->tomove.pop_back();
        robo->nMoves++;
        map[robo->pos.x][robo->pos.y].path = false;
    }
}

void init_robo(_robo *robo){
    robo->nMoves    = 0;
    robo->totalCost = 0;
    robo->goingTo.x = -1;
    robo->goingTo.y = -1;
    robo->pos.x     = rand() % 42;
    robo->pos.y     = rand() % 42;
}
