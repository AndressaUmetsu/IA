#include "main.h"
#include <queue>
#include <cstdio>
#include <cstdlib>

void Bfs ( _square** map, _pos start, _pos stop ){
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
                    map[pos.x][pos.y-1].x = pos.x;
                    map[pos.x][pos.y-1].y = pos.y;
                }
            }
            
            if ( pos.x < 41 ) {
                next.x = pos.x + 1;
                next.y = pos.y;
                myqueue.push(next);

                if ( !map[pos.x+1][pos.y].visited ) {
                    map[pos.x+1][pos.y].x = pos.x;
                    map[pos.x+1][pos.y].y = pos.y;
                }
            }
            
            if ( pos.y < 41 ) {
                next.x = pos.x;
                next.y = pos.y + 1;
                myqueue.push(next);

                if ( !map[pos.x][pos.y+1].visited ) {
                    map[pos.x][pos.y+1].x = pos.x;
                    map[pos.x][pos.y+1].y = pos.y;
                }
            }

            if ( pos.x > 0 ) {
                next.x = pos.x - 1;
                next.y = pos.y;
                myqueue.push(next);

                if ( !map[pos.x-1][pos.y].visited ) {
                    map[pos.x-1][pos.y].x = pos.x;
                    map[pos.x-1][pos.y].y = pos.y;
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

}