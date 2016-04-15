#include <cstdio>
#include <cstdlib>

#include "map.h"

void printfImage(_square **map){
    static int k = 0;
    
    FILE *out = fopen("out.svg", "wt");

    int sizeX = 42;
    int sizeY = 42;
    int scale = 20;

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
                fprintf(out, "<circle cx=\"");
                fprintf(out, "%d", (i*scale));
                fprintf(out, "\" cy=\"");
                fprintf(out, "%d", (j*scale));
                fprintf(out, "\" r=\"%d\" stroke=\"lawngreen\" stroke-width=\"1\" fill=\"lawngreen\"/>\n", scale/8);
            }

            if ( map[i][j].path ) {
                fprintf(out, "<circle cx=\"");
                fprintf(out, "%d", (i*scale));
                fprintf(out, "\" cy=\"");
                fprintf(out, "%d", (j*scale));
                fprintf(out, "\" r=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>\n", scale/5);
            }
        }
    }

    fprintf(out, "</svg>\n");
}
