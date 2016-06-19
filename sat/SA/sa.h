#ifndef SA
#define SA

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>



using namespace std;

typedef struct {
	int nVariables;
	int nClauses;
	int *clauses;
} Info;

double LinearCooling ( double t0 , double tn, int i, double n);

int *SimAnnealing ( Info info );

int Random ();

int *InitialSolution ( int nVariables );

int *Neighbour ( int nVariables );

int *CreateArray ( int n );

double Energy ( int *candidate, Info info );

#endif