#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "map.h"
#include "main.h"
#include "dfs.h"
#include "bfs.h"
#include "cu.h"
#include "a_star.h"

int main( ) {
    _pos start_pos;
    _pos end_pos;
    _data d;
    int max = 10;

    srand(time(NULL));

    _data data[10];

    for (int i = 0; i <= 10; ++i) {
        data[i].size  = 0;
        data[i].cost  = 0;
        data[i].nodes = 0;
    }

    for (int j = 0; j < max; ++j) {
        do {
            start_pos.x = rand() % 42;
            start_pos.y = rand() % 42;

            end_pos.x   = rand() % 42;
            end_pos.y   = rand() % 42;
        } while ( ( start_pos.x + end_pos.x == 0 ) || ( start_pos.y + end_pos.y == 0 ) );

        //printf("(%d,  %d) -> (%d, %d)\n", start_pos.x, start_pos.y, end_pos.x, end_pos.y);

        for (int i = 0; i <= 2; ++i) {
            d = magic( start_pos, end_pos, i+1, 666 );
            data[i].nodes += d.nodes;
            data[i].size  += d.size;
            data[i].cost  += d.cost;
        }

        for (int i = 1; i <= 7; ++i) {
            d = magic( start_pos, end_pos, 4, i );
            data[i+2].nodes += d.nodes;
            data[i+2].size  += d.size;
            data[i+2].cost  += d.cost;
        }
    }

    printf("Cost \t\t Size \t\t Nodes\n");
    for (int i = 0; i < 10; ++i) {
        printf("%f \t %f \t %f\n", data[i].cost/(double)max, data[i].size/(double)max, data[i].nodes/(double)max);
    }

    return EXIT_SUCCESS;
}

_data magic( _pos start_pos, _pos end_pos, int method, int distance) {
    FILE *file = fopen("Robo_ambiente.txt", "rt");
    int width = 42;
    int heigth = 42;

    _square **map;
    _data data;

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
        data.cost = dfs(map, start_pos, end_pos);
        break;
    case 2:
        data.cost = Bfs(map, start_pos, end_pos);
        break;
    case 3:
        data.cost = Cu(map, start_pos, end_pos);
        break;
    case 4:
        data.cost = a_star(map, start_pos, end_pos, distance);
        break;
    }

    //printfImage(map, start_pos, end_pos);

    _pos pos = end_pos;

    do {
        _pos bos = pos;
        pos.x = map[bos.x][bos.y].xx;
        pos.y = map[bos.x][bos.y].yy;
    } while ( pos.x != start_pos.x || pos.y != start_pos.y );

    data.nodes = 0;
    data.size  = 0;
    for ( int i = 0 ; i < 42 ; i++ ){
        for ( int j = 0 ; j < 42 ; j++ ){
            if ( map[i][j].visited )
                data.nodes++;

            if ( map[i][j].path )
                data.size++;
        }
    }

    for ( int i = 0 ; i < 42 ; i++ )
        free(map[i]);
    free(map);

    return data;
}
