#include "main.h"
#include <vector>
#include <cstdio>
#include <cstdlib>

void Cu ( _square** map, _pos start, _pos stop ){
	std::vector<_square> c;
	std::vector<_square> u;

	map[start.x][start.y].cu = 0;

	c.push_back( map[start.x][start.y] );

	for (int i = 0; i < 42; ++i)
	{
		for (int j = 0; j < 42; ++j)
		{
			map[i][j].x = i;
			map[i][j].y = j;
		}
	}

	_square lugar;
	_square lugar2;

	while ( 1 ){
		lugar = c.front();
		c.pop();	



		if ( lugar.y > 0 ){


			map[lugar.x][lugar.y-1].cu = map[lugar.x][lugar.y].cu + map[lugar.x][lugar.y-1].type * (map[lugar.x][lugar.y-1].type > 1 ? map[lugar.x][lugar.y-1].type * 5 : 1);
			map[lugar.x][lugar.y-1].xx = lugar.x;
			map[lugar.x][lugar.y-1].yy = lugar.y;
			


			u.push_back(  );
		}

		if ( lugar.x > 0 ){

		}

		if ( lugar.y < 41 ){



		}

		if ( lugar.x < 41 ){

		}



	}


}