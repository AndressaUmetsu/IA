#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "main.h"
#include "a_star.h"
#include "cu.h"

void reset_map(_square **map) {
    for ( int i = 0; i < 42; ++i ){
        for ( int j = 0; j < 42; ++j ){
            map[j][i].visited = false;
            map[j][i].path    = false;
            map[j][i].xx      = -1;
            map[j][i].yy      = -1;
            map[j][i].cu      = -1;
        }
    }
}

void load_oracle ( _square **map ){
    int hue;
    FILE *file = fopen("cu.dat", "rt");
    for ( int i = 0 ; i < 42 ; i++ ) {
        for ( int j = 0 ; j < 42 ; j++ ) {
            fscanf(file, "%d", &hue);
            map[j][i].visited = false;
            map[j][i].path    = false;
            map[j][i].x       = i;
            map[j][i].y       = j;
            map[j][i].heur    = 0;
            map[j][i].oracle  = hue;
        }
    }
    fclose(file);
}

void as_InitializePosition ( _square **map, _pos q, int distance ){
    //load_oracle(map);

    for ( int i = 0; i < 42; ++i ){
        for ( int j = 0; j < 42; ++j ){
            _pos p;
            p.x = i;
            p.y = j;
            map[i][j].x    = i;
            map[i][j].y    = j;

            switch ( distance ) {
                case 1:
                    map[i][j].heur = euclidian_distance(p, q) * 1.0;
                    break;
                case 2:
                    map[i][j].heur = manhattan_distance(p, q);
                    break;
                case 3:
                    map[i][j].heur = minkowski_distance(p, q, 0.6);
                    break;
                case 4:
                    map[i][j].heur = renan_distance(p, q);
                    break;
                case 5:
                    map[i][j].heur = chebyshev_distance(p, q) * 1;
                    break;
                case 6:
                    map[i][j].heur = canberra_distance(p, q) * 25.0;
                    break;
            }
            //map[i][j].heur /= 5.0;
            //map[i][j].heur = map[i][j].oracle;
            //map[i][j].heur = 0;
            //printf("%d \t %d \t %f \t %f \t %f\n", i, j, map[i][j].heur, map[i][j].oracle, map[i][j].oracle - map[i][j].heur);
        }
    }
}

bool as_CompareCu ( _square a, _square b ){
    return a.cu + a.heur < b.cu + b.heur;
}

void a_star ( _square** map, _pos start, _pos stop, int distance ){
    std::vector <_square> frontier;
    _square expandedNode;

    as_InitializePosition ( map, stop, distance );

    map[start.x][start.y].cu = CostByType(map[start.x][start.y].type);
    frontier.push_back( map[start.x][start.y] );

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

    printf( "%d ", map[expandedNode.x][expandedNode.y].cu );

    while ( expandedNode.x != start.x || expandedNode.y != start.y ) {
        _square aux = expandedNode;
        //printf("%d\n", CostByType( map[aux.x][aux.y].type ));
        map[aux.x][aux.y].path = true;
        expandedNode.x = map[aux.x][aux.y].xx;
        expandedNode.y = map[aux.x][aux.y].yy;
    }
    //printf("%d\n", CostByType( map[expandedNode.x][expandedNode.y].type ));

}

int manhattan_distance(_pos a, _pos b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int chebyshev_distance(_pos a, _pos b){
    int x = abs(a.x - b.x);
    int y = abs(a.y - b.y);
    return x > y ? x : y;
}

double renan_distance(_pos a, _pos b){
    double i = 6.0;
    double j = 1.0;
    double k = 6.0;
    double l = 1.0;

    double r = 1.9;
    double s = 0.7;

    double x = euclidian_distance(a, b) * 1.0;
    double y = manhattan_distance(a, b) * 1.0;
    double z = minkowski_distance(a, b, 0.5);
    double w = chebyshev_distance(a, b) * 1.0;

    double m = (i*x + j*y + k*z + l*w) / (i + j + k + l);
    double n = ( r * ((y * w)/(y + w)) + s * ((x))) ;

    return (0.3*m + 0.5*n) * canberra_distance(a, b);
}

double euclidian_distance(_pos a, _pos b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double minkowski_distance(_pos a, _pos b, double p){
    return pow(pow(abs(a.x - b.x), p) + pow(abs(a.y - b.y), p), 1.0/p);
}

double canberra_distance(_pos a, _pos b){
    return abs(a.x - b.x)/(a.x + b.x) + abs(a.y - b.y)/(a.y + b.y);
}
