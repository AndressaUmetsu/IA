#include "sa.h"
#include "readFile.h"

int main(int argc, char const *argv[])
{
	Info info;
	int *solution;
	string filename = "uf20-01.cnf";
	ReadFile (filename, &info);

	solution = SimAnnealing (info);

	return 0;
}
