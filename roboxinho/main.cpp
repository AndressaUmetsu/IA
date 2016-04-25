#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "map.h"
#include "main.h"
#include "dfs.h"
#include "bfs.h"
#include "cu.h"
#include "a_star.h"

int main(int argc, char const *argv[]) {
    FILE *file = fopen("Robo_ambiente.txt", "rt");
    int width = 42;
    int heigth = 42;
    _pos start_pos;
    _pos end_pos;
    int method;
    int distance;

    _square **map;

    if ( argc != 7 ) {
        fprintf(stderr, "Faltam parametros\n");
    } else {
        start_pos.x = atoi(argv[1]);
        start_pos.y = atoi(argv[2]);
        end_pos.x   = atoi(argv[3]);
        end_pos.y   = atoi(argv[4]);
        method      = atoi(argv[5]);
        distance    = atoi(argv[6]);
    }

    map = (_square**) malloc ( sizeof(_square*) * width );
    for ( int i = 0 ; i < 42 ; i++ )
        map[i] = (_square*) malloc ( sizeof(_square) * heigth );

    int hue;

    for ( int i = 0 ; i < 42 ; i++ ) {
        for ( int j = 0 ; j < 42 ; j++ ) {
            fscanf(file, "%d", &hue);
            map[j][i].type    = hue ;
            map[j][i].visited = false;
            map[j][i].path    = false;
            map[j][i].x       = -1;
            map[j][i].y       = -1;
            map[j][i].xx      = -1;
            map[j][i].yy      = -1;
            //printf("%d ", hue);
        }
        //puts("");
    }

    switch ( method ) {
    case 1:
        dfs(map, start_pos, end_pos);
    case 2:
        Bfs(map, start_pos, end_pos);
    case 3:
        Cu(map, start_pos, end_pos);
    case 4:
        a_star(map, start_pos, end_pos, distance);
    }

    printfImage(map, start_pos, end_pos);

    return 0;
}
