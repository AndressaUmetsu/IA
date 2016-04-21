#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "main.h"

void InitializePosition ( _square **map ){
    for ( int i = 0; i < 42; ++i ){
        for ( int j = 0; j < 42; ++j ){
            map[i][j].x = i;
            map[i][j].y = j;
        }
    }
}

int CostByType ( int type ){
    if ( type == 0 ) 
        return 1;
    return  5 * type;
}

bool IsInFrontier ( std::vector<_square> & frontier, int x, int y ){
    int i = 0;

    while ( i < frontier.size() ){
       // printf("verificando fronteira\n");
        if ( frontier[i].x == x && frontier[i].y == y ){
            frontier.erase( frontier.begin()+i );
            break;  
        }
        i++;
    }
    return false;
}

void VisitNeighbor ( _square **map, _square n, std::vector<_square> & frontier, _square father ){
    int cost;
    cost = CostByType( n.type );

    if ( !n.visited ){

        if ( !IsInFrontier( frontier, n.x, n.y ) ){
            map[n.x][n.y].cu += cost;
            map[n.x][n.y].xx = father.x;
            map[n.x][n.y].yy = father.y;  
        } else if ( map[n.x][n.x].cu > map[n.x][n.y].cu + cost ) {
            map[n.x][n.y].cu += cost;
            map[n.x][n.y].xx = father.x;
            map[n.x][n.y].yy = father.y;
        } 
    }       

    frontier.push_back( map[n.x][n.y] );        
}

bool CompareCu ( _square a, _square b ){
    return a.cu < b.cu;
}

void Cu ( _square** map, _pos start, _pos stop ){
    std::vector <_square> frontier;

    InitializePosition ( map );

    map[start.x][start.y].cu = 0;
    frontier.push_back( map[start.x][start.y] );

    while( !map[stop.x][stop.y].visited ){
        _square expandedNode = frontier.front();
        frontier.erase( frontier.begin() );

        map[expandedNode.x][expandedNode.y].visited = true;  

        if ( expandedNode.y > 0 )
            VisitNeighbor ( map, map[expandedNode.x][expandedNode.y-1], frontier, map[expandedNode.x][expandedNode.y] );    

        if ( expandedNode.x > 0 )
            VisitNeighbor ( map, map[expandedNode.x-1][expandedNode.y], frontier, map[expandedNode.x][expandedNode.y] );    

        if ( expandedNode.y < 41 )
            VisitNeighbor ( map, map[expandedNode.x][expandedNode.y+1], frontier, map[expandedNode.x][expandedNode.y] );    

        if ( expandedNode.x < 41 )
            VisitNeighbor ( map, map[expandedNode.x+1][expandedNode.y], frontier, map[expandedNode.x][expandedNode.y] );   

        std::sort ( frontier.begin(), frontier.end(), CompareCu );
    } 
}

