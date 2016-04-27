#ifndef _MAIN
#define _MAIN

typedef struct {
    int  type;
    bool visited;
    bool path;
    int  x, y;
    int xx, yy;
    int cu;
    float heur;
    float oracle;
} _square;

typedef struct {
    int x, y;
} _pos;

typedef struct {
    int cost;
    int nodes;
    int size;
} _data;

_data magic( _pos start_pos, _pos end_pos, int method, int distance) ;

#endif // _MAIN
