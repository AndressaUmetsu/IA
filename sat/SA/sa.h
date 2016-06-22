#ifndef SA
#define SA

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "writeFile.h"

#define MAXTEMP 20000
#define MINTEMP 1e-30
#define NULLTEMP -1

using namespace std;

typedef struct {
	int nVariables;
	int nClauses;
	int *clauses;
} Info;

double LinearCooling ( double t0 , double tn, int i, double n);

int *SimAnnealing ( Info info );

int Random (int n);

int *InitialSolution ( int nVariables );

int *CopyArray(int *a, int n);

int *Neighbour ( int *variables, int n, double chance );

int Energy ( int *candidate, Info info );

int Not (int p );

bool Accept (int delta, double temperature);

#endif