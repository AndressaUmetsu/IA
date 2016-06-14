#ifndef SA
#define SA

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

typedef struct {
	int nVariables;
	int nClauses;
} Info;

typedef struct {
	int *var;
} Individual;

#endif