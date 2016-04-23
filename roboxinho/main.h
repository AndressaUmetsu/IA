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
} _square;

typedef struct {
    int x, y;
} _pos;

#endif // _MAIN
