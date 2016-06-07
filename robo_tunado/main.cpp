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

    long hue = time(NULL);
    //hue = 1465296063;

    srand(hue);
    srand48(hue);
    //printf("%d\n", hue);

    map     = (_square**  ) malloc ( sizeof(_square*) * width );
    fabrica = ( _fabrica* ) malloc ( sizeof(_fabrica) * 5     );
    for ( int i = 0 ; i < 42 ; i++ )
        map[i] = (_square*) malloc ( sizeof(_square) * heigth );

    init(fabrica, map, file);
    init_robo(&robo);

    // Main loop
    int iters = 0;
    do {
        if ( robo.tomove.size() == 0 && ( robo.action == PICKUP ) ) {
            robo_pickup_item(&robo, map);

            for (int i = 0; i < (int)robo.bag.size(); ++i) {
                for (int j = i+1; j < (int)robo.bag.size(); ++j) {
                    if ( robo.bag[i] == robo.bag[j] ) {
                        robo.action  = DELIVER;
                        for (int k = 0; k < 5; ++k) {
                            if ( fabrica[k].item == robo.bag[i] ) {
                                robo.goingTo = fabrica[k].pos;
                                robo.tomove = a_star(map, robo.pos, robo.goingTo, 2);
                                robo.canMove = false;
                                printf("Robot @ (%2d, %2d) delivering %d to factory %d @ (%2d, %2d)\n", robo.pos.x, robo.pos.y, robo.bag[i],     map[robo.goingTo.x][robo.goingTo.y].item, robo.goingTo.x, robo.goingTo.y);
                            }
                        }
                        break;
                    }
                }
            }

            robo.action = robo.action == DELIVER ? DELIVER : SEARCH;
        }

        if ( robo.tomove.size() == 0 ) {
            if ( robo.action == DELIVER ) {
                if ( !map[robo.pos.x][robo.pos.y].isFabrica      ) { fprintf(stderr, "Tried to deliver in something that is not a factory!\n"); abort(); }
                if (  map[robo.pos.x][robo.pos.y].item == NENHUM ) { fprintf(stderr, "Tried to deliver in something that is not a factory!\n"); abort(); }

                int c = 0;
                bool doit;

                do {
                    doit = false;
                    for ( int i = 0; i < (int)robo.bag.size(); i++){
                        if ( robo.bag[i] == map[robo.pos.x][robo.pos.y].item ) {
                            robo.delivered.push_back(robo.bag[i]);
                            robo.bag.erase(robo.bag.begin() + i);
                            c++;
                            doit = true;
                            break;
                        }
                    }
                } while ( doit );

                printf("Robot @ (%2d, %2d) delivered %2d itens of type %2d\n", robo.pos.x, robo.pos.y, c, map[robo.pos.x][robo.pos.y].item);

                if ( c != 2 ) { fprintf(stderr, "ERROR, delivered only %d itens, expected 2\n", c); abort(); }

                robo.action = SEARCH;
            } if ( robo.action == SEARCH ) {
                robo.goingTo = get_random_pos(robo);

                robo.tomove = a_star(map, robo.pos, robo.goingTo, 2);
                robo.canMove = false;

                printf("Robot @ (%2d, %2d) going to (%2d, %2d)\n", robo.pos.x, robo.pos.y, robo.goingTo.x, robo.goingTo.y);
            }
        }

        // Changes SEARCH action to PICKUP if the file is needed
        std::vector<_item_pos> saw = vision(&robo, map);
        for (int i = 0; i < (int)saw.size(); ++i) {
            _item item = saw[i].item;
            int count = 0;
            for (int j = 0; j < (int)robo.bag.size(); ++j) {
                if ( item == robo.bag[j] ) {
                    count++;
                }
            }
            for (int j = 0; j < (int)robo.delivered.size(); ++j) {
                if ( item == robo.delivered[j] ) {
                    count++;
                }
            }

            if ( count < 2 ) {
                if ( robo.action == SEARCH ) {
                    robo.action = PICKUP;
                    robo.tomove.clear();
                    robo.goingTo = saw[i].pos;
                    robo.tomove = a_star(map, robo.pos, robo.goingTo, 2);
                    robo.canMove = false;
                    break;
                } else if ( robo.action == PICKUP ) {
                    // TODO
                } else if ( robo.action == DELIVER ) {
                    // TODO
                }
            }
        }

        // Moves the robot
        update_pos(&robo, map);

        printfImage(map, &robo, fabrica, iters);
        iters++;
    } while ( (int)robo.delivered.size() != 5*2 );

    printf("-------------\n");

    printf("\n");
    printf("Total squares walked: %3d\n", robo.nMoves);
    printf("Total cost: %3d\n", robo.totalCost);

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
            map[j][i].type      = hue ;
            map[j][i].visited   = false;
            map[j][i].path      = false;
            map[j][i].x         = -1;
            map[j][i].y         = -1;
            map[j][i].xx        = -1;
            map[j][i].yy        = -1;
            map[j][i].item      = NENHUM;
            map[i][j].isItem    = false;
            map[i][j].isFabrica = false;
        }
    }

    for ( int i = 0 ; i < 5 ; i++ ) {
        int x               = rand() % 42;
        int y               = rand() % 42;
        fabrica[i].pos.x    = x;
        fabrica[i].pos.y    = y;
        map[x][y].item      = fabrica[i].item;
        map[x][y].isFabrica = true;
    }

    printf("--- Fabricas ---\n");
    printf("Fabrica Bateria          -> (%2d, %2d) (%d, %d)\n", fabrica[0].pos.x, fabrica[0].pos.y, fabrica[0].item, map[fabrica[0].pos.x][fabrica[0].pos.y].item);
    printf("Fabrica Braco_Solda      -> (%2d, %2d) (%d, %d)\n", fabrica[1].pos.x, fabrica[1].pos.y, fabrica[1].item, map[fabrica[1].pos.x][fabrica[1].pos.y].item);
    printf("Fabrica Bomba            -> (%2d, %2d) (%d, %d)\n", fabrica[2].pos.x, fabrica[2].pos.y, fabrica[2].item, map[fabrica[2].pos.x][fabrica[2].pos.y].item);
    printf("Fabrica Refrigeracao     -> (%2d, %2d) (%d, %d)\n", fabrica[3].pos.x, fabrica[3].pos.y, fabrica[3].item, map[fabrica[3].pos.x][fabrica[3].pos.y].item);
    printf("Fabrica Braco_Penumatico -> (%2d, %2d) (%d, %d)\n", fabrica[4].pos.x, fabrica[4].pos.y, fabrica[4].item, map[fabrica[4].pos.x][fabrica[4].pos.y].item);
    printf("---------------\n");

    printf("\n--- Itens ---\n");

    for ( int i = 0 ; i < 10 ; i++ ) {
        int x, y;
        do {
            x = rand() % 42;
            y = rand() % 42;
        } while ( map[x][y].type != 0 || map[x][y].isFabrica || map[x][y].isItem ) ;
        map[x][y].item   = BATERIA;
        map[x][y].isItem = true;
        printf("BATERIA %d                 -> (%2d, %2d)\n", i, x, y);
    }
    printf("\n");

    for ( int i = 0 ; i < 8 ; i++ ) {
        int x, y;
        do {
            x = rand() % 42;
            y = rand() % 42;
        } while ( map[x][y].type != 0 || map[x][y].isFabrica || map[x][y].isItem ) ;
        map[x][y].item   = BRACO_SOLDA;
        map[x][y].isItem = true;
        printf("BRACO_SOLDA %d             -> (%2d, %2d)\n", i, x, y);
    }
    printf("\n");

    for ( int i = 0 ; i < 6 ; i++ ) {
        int x, y;
        do {
            x = rand() % 42;
            y = rand() % 42;
        } while ( map[x][y].type != 0 || map[x][y].isFabrica || map[x][y].isItem ) ;
        map[x][y].item   = BOMBA;
        map[x][y].isItem = true;
        printf("BOMBA %d                   -> (%2d, %2d)\n", i, x, y);
    }
    printf("\n");

    for ( int i = 0 ; i < 4 ; i++ ) {
        int x, y;
        do {
            x = rand() % 42;
            y = rand() % 42;
        } while ( map[x][y].type != 0 || map[x][y].isFabrica || map[x][y].isItem ) ;
        map[x][y].item   = REFRIGERACAO;
        map[x][y].isItem = true;
        printf("REFRIGERACAO %d            -> (%2d, %2d)\n", i, x, y);
    }
    printf("\n");

    for ( int i = 0 ; i < 2 ; i++ ) {
        int x, y;
        do {
            x = rand() % 42;
            y = rand() % 42;
        } while ( map[x][y].type != 0 || map[x][y].isFabrica || map[x][y].isItem ) ;
        map[x][y].item   = BRACO_PNEUMATICO;
        map[x][y].isItem = true;
        printf("BRACO_PNEUMATICO %d        -> (%2d, %2d)\n", i, x, y);
    }
    printf("-------------\n");

    return;
}
