#include "sa.h"
#include "readFile.h"
#include "writeFile.h"

int main(int argc, char const *argv[])
{
	Info info;
	int *solution;
	string filename = "uf20-01.cnf";

	ReadFile (filename, &info);

	solution = SimAnnealing (info);

	for (int i = 0; i < info.nVariables; ++i)
		cout << solution[i] << " " ;
	cout << endl;
	
	cout << Energy (solution, info) << endl;

	return 0;
}
