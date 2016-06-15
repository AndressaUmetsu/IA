#include "sa.h"
#include "readFile.h"

int main(int argc, char const *argv[])
{
	Info info;
	int *clauses;

	string filename = "uf20-01.cnf";
	clauses = ReadFile ( filename, &info );
	
	/*cout << info.nVariables << " " << info.nClauses << endl;
	for (int i = 0; i < ( info.nClauses )*3; i = i+3 )
		cout << clauses[i] << " " << clauses[i+1] << " " << clauses[i+2] << " " << endl;
	*/

	SimAnnealing ( info);
	return 0;
}

