#include "sa.h"

double LinearCooling ( double t0 , double tn, int i, double n ){
	return t0 - i * ( t0 - tn )/n;
}

int *SimAnnealing ( Info info ){
	srand(time(NULL));
	
	int nVariables = info.nVariables;

	int *candidate = InitialSolution ( nVariables );
	double t0 = 100, tf = 0;	
	
	do {
		int *nextCandidate = Neighbour ( nVariables );



	} while( t > tf );


return candidate;





   	/*
	int i = 0;
	
	do{
		i++;
		ti = LinearCooling (100, 1e-30,i, 500);  
	} while(i<500);

	*/
}



int *InitialSolution ( int nVariables ){
	return CreateArray (nVariables);
}

int *Neighbour ( int nVariables ){
	return CreateArray (nVariables);
}

int *CreateArray (int n){
	int *variables = ( int * ) malloc ( sizeof( int )*n );

	for ( int i = 0; i < n; ++i )
		variables[i] = Random();

	return variables;
}

int Random (){
	int random = rand() % 2;
	return random;
}

double Energy ( int *candidate, Info info ){
	int energy;

	for (int i = 0; i < info.nClauses; i+=3){
		
	}



	return energy;
}

bool ClauseSatisfied (  ){


}
