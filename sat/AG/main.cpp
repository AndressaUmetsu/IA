#include "ag.h"
#include "read.h"

int main(int argc, char const *argv[])
{
	long seed = time(NULL);
	srand(seed);

	Info info;
	int *clauses;
	int *variables;
	
	string filename = "uf20-01.cnf";
	
	ReadFile ( filename, &info );

	PrintGeneticAlgorithm ( info, 8);	

	return 0;
}

