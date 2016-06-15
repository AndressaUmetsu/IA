#include "sa.h"


void SimAnnealing ( Info info){
	srand(time(NULL));
	
	int *candidate = InitialSolution ( info );
	
   	
}

int *InitialSolution ( Info info ){
	int *variables = ( int * ) malloc ( sizeof( int )*info.nVariables );

	for (int i = 0; i < info.nVariables; ++i)
		variables[i] = Random();

	return variables;
}

int Random (){
	int random = rand() % 2;
    // cout << random << endl;
	return random;
} 

int *Neighbour(Info info){
	
}