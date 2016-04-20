#include <cstdio>
#include <cstdlib>

#include "map.h"

void printfImage(_square **map, _pos start, _pos stop ){
    static int k = 0;
    
    FILE *out = fopen("out.svg", "wt");

    int sizeX = 42;
    int sizeY = 42;
    int scale = 20;

    int visitados = 0;
    int caminho   = 0;

    fprintf(out, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
    fprintf(out, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
    fprintf(out, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
    fprintf(out, "<svg width=\"");
    fprintf(out, "%d", ((sizeX-1) * scale));
    fprintf(out, "\" height=\"");
    fprintf(out, "%d", ((sizeY-1) * scale));
    fprintf(out, "\" version=\"1.0\"\n");
    fprintf(out, "xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(out, "<rect width=\"");
    fprintf(out, "%d", ((sizeX-1) * scale));
    fprintf(out, "\" height=\"");
    fprintf(out, "%d", ((sizeY-1) * scale));
    fprintf(out, "\" style=\"fill:rgb(255, 255, 255);stroke-width:2;stroke:rgb(0, 0, 0)\"/>\n");

    for ( int i = 0 ; i < 42 ; i++ ){
        for ( int j = 0 ; j < 42 ; j++ ){
            fprintf(out, "<circle cx=\"");
            fprintf(out, "%d", (i*scale));
            fprintf(out, "\" cy=\"");
            fprintf(out, "%d", (j*scale));
            if        (map[i][j].type == 0){
                    fprintf(out, "\" r=\"%d\" stroke=\"olivedrab\" stroke-width=\"1\" fill=\"olivedrab\"/>\n", scale/2);
            } else if (map[i][j].type == 1){
                    fprintf(out, "\" r=\"%d\" stroke=\"saddlebrown\" stroke-width=\"1\" fill=\"saddlebrown\"/>\n", scale/2);
            } else if (map[i][j].type == 2){
                    fprintf(out, "\" r=\"%d\" stroke=\"deepskyblue\" stroke-width=\"1\" fill=\"deepskyblue\"/>\n", scale/2);
            } else if (map[i][j].type == 3){
                    fprintf(out, "\" r=\"%d\" stroke=\"darkred\" stroke-width=\"1\" fill=\"darkred\"/>\n", scale/2);
            }

            if ( map[i][j].visited ) {
                visitados++;
                fprintf(out, "<circle cx=\"");
                fprintf(out, "%d", (i*scale));
                fprintf(out, "\" cy=\"");
                fprintf(out, "%d", (j*scale));
                fprintf(out, "\" r=\"%d\" stroke=\"lawngreen\" stroke-width=\"1\" fill=\"lawngreen\"/>\n", scale/8);
            }

            if ( map[i][j].path ) {
                caminho++;
                fprintf(out, "<circle cx=\"");
                fprintf(out, "%d", (i*scale));
                fprintf(out, "\" cy=\"");
                fprintf(out, "%d", (j*scale));
                fprintf(out, "\" r=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>\n", scale/5);
            }
        }
    }

    _pos pos = stop;

    do {
        _pos bos = pos;
        pos.x = map[bos.x][bos.y].xx;
        pos.y = map[bos.x][bos.y].yy;
        if ( pos.x != start.x || pos.y != start.y ) {
            fprintf(out, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(0, 0, 0);stroke-width:2\" />\n", pos.x * scale, pos.y * scale, bos.x * scale, bos.y * scale);
        }
    } while ( pos.x != start.x || pos.y != start.y );

    //fprintf(out, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(255, 0, 0);stroke-width:2\" />\n", (start.x * scale - 5), (start.y * scale - 5), (start.x * scale + 5), (start.y * scale + 5)) ;
    fprintf(out, "</svg>\n");

    printf("Nós explorados: %d\n", visitados);
    printf("Tamanho do caminho: %d\n", caminho);
}
