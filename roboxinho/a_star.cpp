#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "main.h"
#include "a_star.h"
#include "cu.h"

void as_InitializePosition ( _square **map, _pos q ){
    for ( int i = 0; i < 42; ++i ){
        for ( int j = 0; j < 42; ++j ){
            _pos p;
            p.x = i;
            p.y = j;
            map[i][j].x    = i;
            map[i][j].y    = j;
            //map[i][j].heur = euclidian_distance(p, q) * 4.5;
            //map[i][j].heur = euclidian_distance(p, q) * 3.5;
            //map[i][j].heur = euclidian_distance(p, q) * 2.5;
            //map[i][j].heur = euclidian_distance(p, q) * 2.0;
            //map[i][j].heur = euclidian_distance(p, q) * 1.5;
            //map[i][j].heur = euclidian_distance(p, q) * 1.0;
            //map[i][j].heur = manhattan_distance(p, q);
            map[i][j].heur = renan_distance(p, q);
            //map[i][j].heur = 0;
            //printf("%d %d %f\n", i, j, map[i][j].heur);
        }
    }
}

bool as_CompareCu ( _square a, _square b ){
    return a.cu + a.heur < b.cu + b.heur;
}

void a_star ( _square** map, _pos start, _pos stop ){
    std::vector <_square> frontier;
    _square expandedNode;

    as_InitializePosition ( map, stop );

    map[start.x][start.y].cu = 0;
    frontier.push_back( map[start.x][start.y] );
    int i = 0;
    while( 1 ){
        expandedNode = frontier.front();
        frontier.erase( frontier.begin() );

        if ( expandedNode.x == stop.x && expandedNode.y == stop.y )
            break;

        if( !expandedNode.visited ){
            map[expandedNode.x][expandedNode.y].visited = true;

            if ( expandedNode.y > 0 )
                VisitNeighbor ( map, map[expandedNode.x][expandedNode.y-1], frontier, map[expandedNode.x][expandedNode.y] );

            if ( expandedNode.x > 0 )
                VisitNeighbor ( map, map[expandedNode.x-1][expandedNode.y], frontier, map[expandedNode.x][expandedNode.y] );

            if ( expandedNode.y < 41 )
                VisitNeighbor ( map, map[expandedNode.x][expandedNode.y+1], frontier, map[expandedNode.x][expandedNode.y] );

            if ( expandedNode.x < 41 )
                VisitNeighbor ( map, map[expandedNode.x+1][expandedNode.y], frontier, map[expandedNode.x][expandedNode.y] );

            std::sort ( frontier.begin(), frontier.end(), as_CompareCu );
        }
    }

    frontier.clear();

    printf( "Custo do caminho: %d\n", map[expandedNode.x][expandedNode.y].cu );

    int k = 0;
    while ( expandedNode.x != start.x || expandedNode.y != start.y ) {
        _square aux = expandedNode;
        map[aux.x][aux.y].path = true;
        expandedNode.x = map[aux.x][aux.y].xx;
        expandedNode.y = map[aux.x][aux.y].yy;
    }

}

int manhattan_distance(_pos a, _pos b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

double renan_distance(_pos a, _pos b){
    double x = euclidian_distance(a, b) * 2.0;
    double y = manhattan_distance(a, b) * 1.0;
    double m = (x + y) / 2.0;
    printf("%f %f %f\n", x, y, m );
    //return x < y ? x : y;
    return m;
}

double euclidian_distance(_pos a, _pos b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

