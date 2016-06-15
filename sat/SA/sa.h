#ifndef SA
#define SA

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

//#define MAXITERATION ;

using namespace std;

typedef struct {
	int nVariables;
	int nClauses;
} Info;

//pertubação

//rand

void SimAnnealing( Info info );

int *InitialSolution ( Info info );

int Random ();


#endif