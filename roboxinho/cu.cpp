#include "main.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>

bool CompareCu ( _square a, _square b){
    return a.cu < b.cu;
}

void Cu ( _square** map, _pos start, _pos stop ){
    std::vector<_square> c;
    std::vector<_square> u;

    map[start.x][start.y].cu = 0;

    for (int i = 0; i < 42; ++i)
    {
        for (int j = 0; j < 42; ++j)
        {
            map[i][j].x = i;
            map[i][j].y = j;
        }
    }

     c.push_back( map[start.x][start.y] );

    _square lugar;
    int end = 0;

    while ( 1 ){
        while ( !c.empty() ) {
            lugar = c.front();
            c.erase( c.begin() );


        	if ( lugar.x == stop.x && lugar.y == stop.y ){
        		end = 1;
        		break;    	
        	}	

            if ( lugar.y > 0 && !map[lugar.x][lugar.y-1].visited ){
                int custo = 0;

                if (map[lugar.x][lugar.y-1].type == 0) {
                    custo = 1;
                } else {
                    custo = 5 * ( map[lugar.x][lugar.y-1].type);
                }

                map[lugar.x][lugar.y-1].cu = map[lugar.x][lugar.y].cu + custo;
                map[lugar.x][lugar.y-1].xx = lugar.x;
                map[lugar.x][lugar.y-1].yy = lugar.y;
                map[lugar.x][lugar.y-1].visited = true;

                u.push_back( map[lugar.x][lugar.y-1] );
            }

            if ( lugar.x > 0 && !map[lugar.x-1][lugar.y].visited){
                int custo = 0;

                if (map[lugar.x-1][lugar.y].type == 0) {
                    custo = 1;
                } else {
                    custo = 5 * ( map[lugar.x-1][lugar.y].type);
                }

                map[lugar.x-1][lugar.y].cu = map[lugar.x][lugar.y].cu + custo;
                map[lugar.x-1][lugar.y].xx = lugar.x;
                map[lugar.x-1][lugar.y].yy = lugar.y;
                map[lugar.x-1][lugar.y].visited = true;

                u.push_back( map[lugar.x-1][lugar.y] );
            }

            if ( lugar.x < 41 && !map[lugar.x+1][lugar.y].visited){
                int custo = 0;

                if (map[lugar.x+1][lugar.y].type == 0) {
                    custo = 1;
                } else {
                    custo = 5 * ( map[lugar.x+1][lugar.y].type);
                }
                
                map[lugar.x+1][lugar.y].cu = map[lugar.x][lugar.y].cu + custo;
                map[lugar.x+1][lugar.y].xx = lugar.x;
                map[lugar.x+1][lugar.y].yy = lugar.y;
                map[lugar.x+1][lugar.y].visited = true;

                u.push_back( map[lugar.x+1][lugar.y] );
            }

            if ( lugar.y < 41 && !map[lugar.x][lugar.y+1].visited){
                int custo = 0;

                if (map[lugar.x][lugar.y+1].type == 0) {
                    custo = 1;
                } else {
                    custo = 5 * ( map[lugar.x][lugar.y+1].type);
                }

                map[lugar.x][lugar.y+1].cu = map[lugar.x][lugar.y].cu + custo;
                map[lugar.x][lugar.y+1].xx = lugar.x;
                map[lugar.x][lugar.y+1].yy = lugar.y;
                map[lugar.x][lugar.y+1].visited = true;

                u.push_back( map[lugar.x][lugar.y+1] );
            }

        }

        if ( end )
        	break;

        std::sort (u.begin(), u.end(), CompareCu);

        c = u;
        u.clear();
    }

    printf("custo do caminho %d\n",map[lugar.x][lugar.y].cu );

    int k =0;
    while ( lugar.x != start.x || lugar.y != start.y ) {
        _square aux = lugar;
        map[aux.x][aux.y].path = true;
        lugar.x = map[aux.x][aux.y].xx;
        lugar.y = map[aux.x][aux.y].yy;
        //printf("%d %d %d %d %d\n", ++k, lugar.x, lugar.y, map[aux.x][aux.y].type, map[aux.x][aux.y].cu);
    }
}
