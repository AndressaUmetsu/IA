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
                map[lugar.x][lugar.y-1].cu = map[lugar.x][lugar.y].cu + map[lugar.x][lugar.y-1].type * (map[lugar.x][lugar.y-1].type > 1 ? map[lugar.x][lugar.y-1].type * 5 : 1);
                map[lugar.x][lugar.y-1].xx = lugar.x;
                map[lugar.x][lugar.y-1].yy = lugar.y;
                map[lugar.x][lugar.y-1].visited = true;

                u.push_back( map[lugar.x][lugar.y-1] );
            }

            if ( lugar.x > 0 && !map[lugar.x-1][lugar.y].visited){  
                map[lugar.x-1][lugar.y].cu = map[lugar.x][lugar.y].cu + map[lugar.x-1][lugar.y].type * (map[lugar.x-1][lugar.y].type > 1 ? map[lugar.x-1][lugar.y].type * 5 : 1);
                map[lugar.x-1][lugar.y].xx = lugar.x;
                map[lugar.x-1][lugar.y].yy = lugar.y;
                map[lugar.x-1][lugar.y].visited = true;

                u.push_back( map[lugar.x-1][lugar.y] );
            }

            if ( lugar.x < 41 && !map[lugar.x+1][lugar.y].visited){
                map[lugar.x+1][lugar.y].cu = map[lugar.x][lugar.y].cu + map[lugar.x+1][lugar.y].type * (map[lugar.x+1][lugar.y].type > 1 ? map[lugar.x+1][lugar.y].type * 5 : 1);
                map[lugar.x+1][lugar.y].xx = lugar.x;
                map[lugar.x+1][lugar.y].yy = lugar.y;
                map[lugar.x+1][lugar.y].visited = true;
                u.push_back( map[lugar.x+1][lugar.y] );
            }

            if ( lugar.y < 41 && !map[lugar.x][lugar.y+1].visited){
                map[lugar.x][lugar.y+1].cu = map[lugar.x][lugar.y].cu + map[lugar.x][lugar.y+1].type * (map[lugar.x][lugar.y+1].type > 1 ? map[lugar.x][lugar.y+1].type * 5 : 1);
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
    
    printf("%d %d\n",lugar.x, lugar.y );

    int cost = 0;

    while ( lugar.x != start.x || lugar.y != start.y ) {
        _square aux = lugar;
        printf("%d\n",map[aux.x][aux.y].cu );
        map[aux.x][aux.y].path = true;
        cost += map[aux.x][aux.y].cu; 
        lugar.x = map[aux.x][aux.y].xx;
        lugar.y = map[aux.x][aux.y].yy;
    }
    printf("Custo do caminho %d\n", cost);
}
