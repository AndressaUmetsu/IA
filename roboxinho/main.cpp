#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "map.h"
#include "main.h"
#include "dfs.h"
#include "bfs.h"
#include "cu.h"

int main(int argc, char const *argv[]) {
    FILE *file = fopen("Robo_ambiente.txt", "rt");
    int width = 42;
    int heigth = 42;
    _pos start_pos;
    _pos end_pos;

    _square **map;

    if ( argc != 5 ) {
        fprintf(stderr, "nononon bizonho\n");
    } else {
        start_pos.x = atoi(argv[1]);
        start_pos.y = atoi(argv[2]);
        end_pos.x   = atoi(argv[3]);
        end_pos.y   = atoi(argv[4]);
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
            printf("%d ", hue);
        }
        puts("");
    }

    //dfs(map, start_pos, end_pos);
 
   // Bfs(map, start_pos, end_pos);

    Cu(map, start_pos, end_pos);

    printfImage(map);

    return 0;
}
