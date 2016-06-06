#ifndef _MAIN
#define _MAIN

#include <vector>
#include "stdio.h"

typedef enum {BATERIA, BRACO_SOLDA, BOMBA, REFRIGERACAO, BRACO_PNEUMATICO, NENHUM} _item;

typedef struct {
    int  type;
    bool visited;
    bool path;
    int  x, y;
    int xx, yy;
    int cu;
    float heur;
    float oracle;
    _item item;
} _square;

typedef struct {
    int x, y;
} _pos;

typedef struct {
    _pos pos;
    _item item;
} _fabrica;

typedef struct {
    int cost;
    int nodes;
    int size;

    double c_mean;
    double c_variance;
    double c_std_dev;

    double n_mean;
    double n_variance;
    double n_std_dev;

    double s_mean;
    double s_variance;
    double s_std_dev;
} _data;

typedef struct {
    _pos pos;
    _item item;
}_item_pos;

_data magic( _pos start_pos, _pos end_pos, int method, int distance) ;
void init(_fabrica *fabrica, _square** map, FILE* file);

#endif // _MAIN
