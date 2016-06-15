#ifndef SA
#define SA

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define MAXITERATION 500000;

using namespace std;

typedef struct {
	int nVariables;
	int nClauses;
} Info;

typedef struct {
	int *var;
} Individual;

//pertubação

//rand

void SimAnnealing();

InitialSolution();

#endif