#ifndef AG
#define AG

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <queue>

#define MAXITERATION 500000;

using namespace std;

typedef struct {
	int nVariables;
	int nClauses;
	int *clauses;
} Info;

typedef struct {
	int *solution;
	int fitness;
	int id;
} Individual;

typedef struct {
	Individual *individual;
	int sizePop;
} Population;


void GeneticAlgorithm( Info info, int sizePopulation );

void PrintGeneticAlgorithm( Info info, int sizePopulation );

void InitialPopulation ( Population *p, Info info );

int *InitialSolution ( int n );

int Random (int n);

int CalculateFitness ( int *individual, Info info );

int Not ( int p );

void EvaluatePopulation ( Population *p, Info info );

Individual BestIndividual ( Population p );

bool Satisfy ( Individual best, Info info );

int WorstFitness ( Population p );

Population BestPopulation( Population p );

Population Copy ( Population p );

void NewPopulation ( Population best);

int Roulette ( vector<double> percent , int sum );


#endif
