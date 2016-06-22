#include "sa.h"

double LinearCooling ( double t0 , double tn, int i, double n ){
	return t0 - i * ( t0 - tn )/n;
}

double ConstantCooling (double t){
	return t*ALFA;
}

double Coolling6 (double t0 , double tn, int i, double n){
	double a = 1 + exp( 3 * ( ( n / 2.0 ) - i ) );
	cout << 1 + exp( 3 * ( ( n / 2.0 ) - i ))  << " " << ( n / 2.0 ) - 1 << endl;
	return tn + ( ( t0 - tn ) / a );
}

double Coolling3 (double t0 , double tn, int i, double n){
	double a = log(t0 - tn)/log(n);
	cout << log(t0 - tn) << " " << t0-tn << endl;
	return t0 - pow (i, a);
}

double SigmoidCooling ( double t0 , double tn, int i, double n ){
	double a = ( ( t0 - tn ) * ( n + 1 ) ) / n;
	double b = t0 - a;
	return b + a/(i+1);
}

int *SimAnnealing ( Info info ){
	long seed = time(NULL);
	srand(seed);

	ofstream outTemp, outEnergy;
	outTemp.open ("outTemp.csv");
	outEnergy.open ("outEnergy.csv");

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

		if ( delta <= 0 )
			candidate = nextCandidate;

		else if( Accept ( -delta, t ) )
			candidate = nextCandidate;

		if ( Energy ( candidate, info ) < Energy ( best, info ) )
			best = CopyArray( candidate, nVariables );

		outTemp   << j << " " << t << endl;
		outEnergy << j << " " << t << endl;
		j++;

		//t = LinearCooling(t, tmin , j, N);
		//t = Coolling3(t, tmin, j, N);
		t = Coolling6 (t, tmin, j, N);
		// t =  ConstantCooling (t);
		//t = SigmoidCooling(t, tmin , j, N);
	} while( t > tmin );

  	outTemp   << j << " " << t << endl;

  	outTemp.close();
  	outEnergy.close();


return best;
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
				// cout << "chance change " << chance << " probability " << probability/100 << endl;
			}
		}
		else {
			int probability = Random(chance+K);

			if (chance > probability){

				variables[i] = Not(variables[i]);

				// cout << "chance change " << chance << " probability " << probability << endl;
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
