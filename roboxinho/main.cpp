#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "map.h"

int main(int argc, char const *argv[]) {
    FILE *file = fopen("Robo_ambiente.txt", "rt");
    int width = 42;
    int heigth = 42;

    int **map;

    map = (int**) malloc ( sizeof(int*) * width );
    for ( int i = 0 ; i < 42 ; i++ )
        map[i] = (int*) malloc ( sizeof(int) * heigth );

    int hue;

    for ( int i = 0 ; i < 42 ; i++ ){
        for ( int j = 0 ; j < 42 ; j++ ){
            fscanf(file, "%d", &hue);
            map[j][i] = hue;
        }
        puts("");
    }

    printfImage(map);

    return 0;
}
