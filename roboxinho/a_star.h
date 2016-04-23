void as_InitializePosition ( _square **map, _pos );

bool as_CompareCu ( _square a, _square b );

void a_star ( _square** map, _pos start, _pos stop );

int    manhattan_distance(_pos a, _pos b);
double renan_distance(_pos a, _pos b);
double euclidian_distance(_pos a, _pos b);

void get_best_neighbor ( _square **map, _square n, std::vector<_square> & frontier, _square father );
void as_VisitNeighbor ( _square **map, _square n, std::vector<_square> & frontier, _square father );

int   get_best_neighbor ( _square **map, _square expandedNode, std::vector<_square> & frontier);
float get_best_neighbor_aux ( _square **map, _square n, std::vector<_square> & frontier, _square father );
