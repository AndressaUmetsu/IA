#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "map.h"
#include "main.h"
#include "cu.h"
#include "a_star.h"

int main(int argc, char *argv[]) {
    FILE *file = fopen("Robo_ambiente.txt", "rt");
    int width = 42;
    int heigth = 42;
    int hue;

    _fabrica fabrica[5];
    fabrica[0].item = BATERIA;
    fabrica[1].item = BRACO_SOLDA;
    fabrica[2].item = BOMBA;
    fabrica[3].item = REFRIGERACAO;
    fabrica[4].item = BRACO_PNEUMATICO;

    _pos end_pos, start_pos;

    end_pos.x = 5;
    end_pos.y = 5;

    start_pos.x = 25;
    start_pos.y = 25;

    _square **map;
    _data data;

    map = (_square**) malloc ( sizeof(_square*) * width );
    for ( int i = 0 ; i < 42 ; i++ )
        map[i] = (_square*) malloc ( sizeof(_square) * heigth );


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
            map[j][i].item    = NENHUM;
            //printf("%d ", hue);
        }
        //puts("");
    }

    for ( int i = 0 ; i < 5 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        fabrica[i].pos.x = x;
        fabrica[i].pos.y = y;
    }

    for ( int i = 0 ; i < 10 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = BATERIA;
    }

    for ( int i = 0 ; i < 8 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = BRACO_SOLDA;
    }

    for ( int i = 0 ; i < 6 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = BOMBA;
    }

    for ( int i = 0 ; i < 4 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = REFRIGERACAO;
    }

    for ( int i = 0 ; i < 2 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = BRACO_PNEUMATICO;
    }

    data.cost = a_star(map, start_pos, end_pos, 0);

    printfImage(map, start_pos, end_pos, fabrica);

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

    return EXIT_SUCCESS;
}
