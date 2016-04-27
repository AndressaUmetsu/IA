#include "main.h"
#include <queue>
#include <cstdio>
#include <cstdlib>

int Bfs ( _square** map, _pos start, _pos stop ){
	std::queue <_pos> myqueue;

    map[start.x][start.y].path = true;

    myqueue.push(start);
    _pos pos;

    while ( myqueue.size() > 0 ) {
        pos = myqueue.front();
        myqueue.pop();

        if ( !map[pos.x][pos.y].visited ) {
            map[pos.x][pos.y].visited = true;

            if ( pos.x == stop.x && pos.y == stop.y ) {
                break;
            }

            _pos next;

            if ( pos.y > 0 ) {
                next.x = pos.x;
                next.y = pos.y - 1;
                myqueue.push(next);

                if ( !map[pos.x][pos.y-1].visited ) {
                    map[pos.x][pos.y-1].xx = pos.x;
                    map[pos.x][pos.y-1].yy = pos.y;
                }
            }

            if ( pos.x < 41 ) {
                next.x = pos.x + 1;
                next.y = pos.y;
                myqueue.push(next);

                if ( !map[pos.x+1][pos.y].visited ) {
                    map[pos.x+1][pos.y].xx = pos.x;
                    map[pos.x+1][pos.y].yy = pos.y;
                }
            }

            if ( pos.y < 41 ) {
                next.x = pos.x;
                next.y = pos.y + 1;
                myqueue.push(next);

                if ( !map[pos.x][pos.y+1].visited ) {
                    map[pos.x][pos.y+1].xx = pos.x;
                    map[pos.x][pos.y+1].yy = pos.y;
                }
            }

            if ( pos.x > 0 ) {
                next.x = pos.x - 1;
                next.y = pos.y;
                myqueue.push(next);

                if ( !map[pos.x-1][pos.y].visited ) {
                    map[pos.x-1][pos.y].xx = pos.x;
                    map[pos.x-1][pos.y].yy = pos.y;
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

    //printf("%d ", custo_total);

    return custo_total;
}
