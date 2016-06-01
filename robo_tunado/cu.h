#ifndef CU
#define CU

#include "main.h"
#include <vector> 

void InitializePosition ( _square **map );

int CostByType ( int type );

bool IsInFrontier ( std::vector<_square> & frontier, int x, int y );

void VisitNeighbor ( _square **map, _square n, std::vector<_square> & frontier, _square father );

bool CompareCu ( _square a, _square b );

int Cu ( _square** map, _pos start, _pos stop );

#endif
