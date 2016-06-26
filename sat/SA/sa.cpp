#include "sa.h"

double Cooling0 ( double t0 , double tn, int i, double n ){
	return t0 - i * ( t0 - tn )/n;
}

double ConstantCooling (double t){
	return t*ALFA;
}

int SimAnnealing ( Info info, string filename){

	ofstream out;
	out.open ( filename.c_str() );

	int nVariables = info.nVariables;
	double t = MAXTEMP, tmin = MINTEMP;
	int j = 0;
	
	int *candidate = InitialSolution ( nVariables );
	int *best = CopyArray ( candidate, nVariables );

	do {
		int *nextCandidate = Neighbour ( CopyArray( candidate, nVariables ), nVariables, t );

		int energyOld = Energy ( candidate, info );
		int energyNew = Energy ( nextCandidate, info );

		int delta =  energyNew - energyOld;

		out << j << " " << t << " " << energyOld << " " << exp ( (delta/t) ) << endl;

		if ( delta <= 0 )
			candidate = nextCandidate;

		else if( Accept ( -delta, t ) )
			candidate = nextCandidate;

		 if ( Energy ( candidate, info ) < Energy ( best, info ) )
			best = CopyArray( candidate, nVariables );

		t = Cooling0(t, tmin , j, N); 

		j++;

	} while( t > tmin && j < MAXAVAL);
  	out.close();

	return Energy ( best, info );
}

int *InitialSolution ( int n ){
	int *variables = ( int * ) malloc ( sizeof( int )*n );

	for ( int i = 0; i < n; ++i )
		variables[i] = Random(2);

	return variables;
}

int *CopyArray(int *a, int n){
	int *b = ( int * ) malloc ( sizeof( int )*n );

	for (int i = 0; i < n; ++i)
		b[i] = a[i];

	return b;
}

int *Neighbour ( int *variables, int n, double chance ){
	for ( int i = 0; i < n; ++i ){
		if (chance < 1){
			double probability = Random((chance+C)*100);
			if (chance > probability/100.0){
				variables[i] = Not(variables[i]);
			}
		}
		else {
			int probability = Random(chance+K);

			if (chance > probability){

				variables[i] = Not(variables[i]);
			}
		}
	}
	return variables;
}

int Random (int n){
	int random = rand() % n;
	return random;
}

int Energy ( int *candidate, Info info ){
	int energy = 0;

	for (int i = 0; i < info.nClauses * 3; i+=3){
		int clauseSatisfied = 0;

		for (int j = 0; j < 3; ++j){

			if (info.clauses[i+j] > 0){
				clauseSatisfied += candidate[info.clauses[i+j] - 1];
			}

			else{
				clauseSatisfied += Not ( candidate[abs( info.clauses[i+j] ) - 1] );
			}
		}

		if (clauseSatisfied == 0){
			energy++;
		}
	}

	return energy;
}

int Not ( int p ){
	return p == 0 ? 1 : 0;
}

bool Accept ( int delta, double temperature ){
	double chance = exp ( (delta/temperature) );
	double probability = Random(101)/100;
	if (chance > probability)
		return true;

	return false;
}
