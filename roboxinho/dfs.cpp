#include "main.h"
#include <vector>
#include <cstdio>
#include <cstdlib>

void dfs(_square** map, _pos start, _pos stop) {
    std::vector<_pos> stack;
    
    map[start.x][start.y].path    = true;

    stack.push_back(start);
    _pos pos;

    while ( stack.size() > 0 ) {
        //printf("stack size: %d\n", stack.size());
        pos = stack.back();
        stack.pop_back();
        //printf("%d %d\n", pos.x, pos.y);

        if ( !map[pos.x][pos.y].visited ) {
            map[pos.x][pos.y].visited = true;

            if ( pos.x == stop.x && pos.y == stop.y ) {
                break;
            }

            _pos next;

            if ( pos.x > 0 ) {
                next.x = pos.x - 1;
                next.y = pos.y;
                stack.push_back(next);

                if ( !map[pos.x-1][pos.y].visited ) {
                    map[pos.x-1][pos.y].xx = pos.x;
                    map[pos.x-1][pos.y].yy = pos.y;
                }
            }

            if ( pos.y < 41 ) {
                next.x = pos.x;
                next.y = pos.y + 1;
                stack.push_back(next);

                if ( !map[pos.x][pos.y+1].visited ) {
                    map[pos.x][pos.y+1].xx = pos.x;
                    map[pos.x][pos.y+1].yy = pos.y;
                }
            }

            if ( pos.x < 41 ) {
                next.x = pos.x + 1;
                next.y = pos.y;
                stack.push_back(next);

                if ( !map[pos.x+1][pos.y].visited ) {
                    map[pos.x+1][pos.y].xx = pos.x;
                    map[pos.x+1][pos.y].yy = pos.y;
                }
            }

            if ( pos.y > 0 ) {
                next.x = pos.x;
                next.y = pos.y - 1;
                stack.push_back(next);

                if ( !map[pos.x][pos.y-1].visited ) {
                    map[pos.x][pos.y-1].xx = pos.x;
                    map[pos.x][pos.y-1].yy = pos.y;
                }
            }
        }
    }

    int custo_total = 0;

    while ( pos.x != start.x || pos.y != start.y ) {
        _pos bos = pos;

        int custo = 0; 
        if (map[pos.x][pos.y].type == 0) {
            custo = 1;
        } else {
            custo = 5 * ( map[pos.x][pos.y].type);
        }

        map[bos.x][bos.y].path = true;
        custo_total += custo;
        pos.x = map[bos.x][bos.y].xx;
        pos.y = map[bos.x][bos.y].yy;
        //printf("%d %d  -- %d %d\n", pos.x, pos.y, start.x, start.y);
    }

    printf("Custo do caminho: %d\n", custo_total);

    return;
}
