#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <stdlib.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "map.h"
#include "main.h"
#include "robo.h"
#include "a_star.h"

int main() {
    FILE *file = fopen("Robo_ambiente.txt", "rt");
    int width  = 42;
    int heigth = 42;

    _fabrica *fabrica;
    _square **map;
    _robo robo;

    srand(time(NULL));

    map     = (_square**  ) malloc ( sizeof(_square*) * width );
    fabrica = ( _fabrica* ) malloc ( sizeof(_fabrica) * 5     );
    for ( int i = 0 ; i < 42 ; i++ )
        map[i] = (_square*) malloc ( sizeof(_square) * heigth );

    init(fabrica, map, file);
    init_robo(&robo);

    // Main loop
    int iters = 0;
    do {
        if ( robo.tomove.size() == 0 ) {
            robo.goingTo.x = rand() % 42;
            robo.goingTo.y = rand() % 42;

            robo.tomove = a_star(map, robo.pos, robo.goingTo, 2);
        }

        update_pos(&robo, map);

        printf("Robot @ (%d, %d) going to (%d, %d)\n", robo.pos.x, robo.pos.y, robo.goingTo.x, robo.goingTo.y);

        printfImage(map, robo.pos, robo.goingTo, fabrica, iters);
        iters++;
    } while ( true && (int)robo.tomove.size() > 0 );

    for ( int i = 0 ; i < 42 ; i++ )
        free(map[i]);
    free(map);
    free(fabrica);

    return EXIT_SUCCESS;
}

void init(_fabrica *fabrica, _square** map, FILE* file){
    int hue;

    fabrica[0].item = BATERIA;
    fabrica[1].item = BRACO_SOLDA;
    fabrica[2].item = BOMBA;
    fabrica[3].item = REFRIGERACAO;
    fabrica[4].item = BRACO_PNEUMATICO;

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

    printf("--- Fabricas ---\n");
    printf("Fabrica Bateria          -> (%d, %d)\n", fabrica[0].pos.x, fabrica[0].pos.y);
    printf("Fabrica Braco_Solda      -> (%d, %d)\n", fabrica[1].pos.x, fabrica[1].pos.y);
    printf("Fabrica Bomba            -> (%d, %d)\n", fabrica[2].pos.x, fabrica[2].pos.y);
    printf("Fabrica Refrigeracao     -> (%d, %d)\n", fabrica[3].pos.x, fabrica[3].pos.y);
    printf("Fabrica Braco_Penumatico -> (%d, %d)\n", fabrica[4].pos.x, fabrica[4].pos.y);
    printf("---------------\n");

    printf("\n--- Itens ---\n");

    for ( int i = 0 ; i < 10 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = BATERIA;
        printf("BATERIA %d                 -> (%d, %d)\n", i, x, y);
    }
    printf("\n");

    for ( int i = 0 ; i < 8 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = BRACO_SOLDA;
        printf("BRACO_SOLDA %d             -> (%d, %d)\n", i, x, y);
    }
    printf("\n");

    for ( int i = 0 ; i < 6 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = BOMBA;
        printf("BOMBA %d                   -> (%d, %d)\n", i, x, y);
    }
    printf("\n");

    for ( int i = 0 ; i < 4 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = REFRIGERACAO;
        printf("REFRIGERACAO %d            -> (%d, %d)\n", i, x, y);
    }
    printf("\n");

    for ( int i = 0 ; i < 2 ; i++ ) {
        int x = rand() % 42;
        int y = rand() % 42;
        map[x][y].item = BRACO_PNEUMATICO;
        printf("BRACO_PNEUMATICO %d        -> (%d, %d)\n", i, x, y);
    }
    printf("-------------\n");

    return;
}
