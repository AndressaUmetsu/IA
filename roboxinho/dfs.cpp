#include "main.h"
#include <vector>
#include <cstdio>
#include <cstdlib>

void dfs(_square** map, _pos start, _pos stop) {
    std::vector<_pos> stack;
    
    //map[start.x][start.y].visited = true;
    map[start.x][start.y].path    = true;

    stack.push_back(start);
    _pos pos;

    while ( stack.size() > 0 ) {
        printf("stack size: %d\n", stack.size());
        pos = stack.back();
        stack.pop_back();
        printf("%d %d\n", pos.x, pos.y);

        if ( !map[pos.x][pos.y].visited ) {
            map[pos.x][pos.y].visited = true;

            if ( pos.x == stop.x && pos.y == stop.y ) {
                break;
            }

            _pos next;

            if ( pos.y > 0 ) {
                next.x = pos.x - 1;
                next.y = pos.y;
                stack.push_back(next);

                if ( !map[pos.x-1][pos.y].visited ) {
                    map[pos.x-1][pos.y].x = pos.x;
                    map[pos.x-1][pos.y].y = pos.y;
                }
            }

            if ( pos.y < 41 ) {
                next.x = pos.x;
                next.y = pos.y + 1;
                stack.push_back(next);

                if ( !map[pos.x][pos.y+1].visited ) {
                    map[pos.x][pos.y+1].x = pos.x;
                    map[pos.x][pos.y+1].y = pos.y;
                }
            }

            if ( pos.x < 41 ) {
                next.x = pos.x + 1;
                next.y = pos.y;
                stack.push_back(next);

                if ( !map[pos.x+1][pos.y].visited ) {
                    map[pos.x+1][pos.y].x = pos.x;
                    map[pos.x+1][pos.y].y = pos.y;
                }
            }

            if ( pos.y > 0 ) {
                next.x = pos.x;
                next.y = pos.y - 1;
                stack.push_back(next);

                if ( !map[pos.x][pos.y-1].visited ) {
                    map[pos.x][pos.y-1].x = pos.x;
                    map[pos.x][pos.y-1].y = pos.y;
                }
            }
        }
    }

    while ( pos.x != start.x || pos.y != start.y ) {
        _pos bos = pos;
        map[bos.x][bos.y].path = true;
        pos.x = map[bos.x][bos.y].x;
        pos.y = map[bos.x][bos.y].y;
        //printf("%d %d  -- %d %d\n", pos.x, pos.y, start.x, start.y);
    }

    return;
}
