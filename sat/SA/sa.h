#ifndef SA
#define SA

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#define MAXTEMP 5000
#define MINTEMP 1e-10  //1e-30
#define NULLTEMP -1
#define ALFA 0.98
#define N 1000
#define MAXAVAL 500000
#define C 8
#define K 20

using namespace std;

typedef struct {
	int nVariables;
	int nClauses;
	int *clauses;
} Info;

double Cooling0 ( double t0 , double tn, int i, double n);

double Cooling3 (double t0 , double tn, int i, double n);

double Cooling6 (double t0 , double tn, int i, double n);

double ConstantCooling (double t);

int SimAnnealing ( Info info, string filename, string name);

int Random (int n);

int *InitialSolution ( int nVariables );

int *CopyArray(int *a, int n);

int *Neighbour ( int *variables, int n, double chance );

int Energy ( int *candidate, Info info );

int Not (int p );

bool Accept (int delta, double temperature);

#endif