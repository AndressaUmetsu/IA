#ifndef ROBO_H
#define ROBO_H

#include "main.h"

typedef enum {SEARCH, DELIVER, PICKUP} _action;

typedef struct {
    _pos pos;
    _pos goingTo;
    std::vector<_item> bag;
    std::vector<_item> delivered;
    std::vector<_pos>  visited;
    std::vector<_pos>  notVisited;
    std::vector<_pos>  tomove;
    _action action;

    bool canMove;

    int nMoves;
    int totalCost;
}_robo;

void init_robo(_robo *robo);
void update_pos(_robo *robo, _square **map);
void update_visited(_robo *robo, _pos pos);
std::vector<_item_pos> vision(_robo *robo, _square **map);
void robo_pickup_item(_robo *robo, _square **map);

#endif /* ROBO_H */
