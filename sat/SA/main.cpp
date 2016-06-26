#include "sa.h"
#include "readFile.h"

void TestIn();

void Test(string filename, string name);

void Print();

int main(int argc, char const *argv[])
{
	
	long seed = time(NULL);
	srand(seed);
	TestIn();
	//Print();
	return 0;
}

void Print(){
	Info info;
	string filename = "input/uf20-01.cnf";

	ReadFile (filename, &info);

	int bestEnergy = SimAnnealing (info, "out.csv");

	cout << info.nVariables << " " << info.nClauses << endl << "Numero de clausulas não satisfeitas " << bestEnergy << endl;
}


void Test(string filename, string name){
	Info info;
	int bestEnergy;

	ReadFile (filename, &info);

	for (int i = 0; i < 10; ++i){
		stringstream out;
		out << "out/out" << i << name << ".csv";
		filename = out.str();
		bestEnergy = SimAnnealing (info, filename);
	}

}

void TestIn(){
	string filename = "input/uf20-01.cnf";
	string name = "uf20-01";
	Test(filename, name);
	filename = "input/uf50-01.cnf";
	name = "uf50-01";
	Test(filename, name);
	filename = "input/uf75-01.cnf";
	name = "uf75-01";
	Test(filename, name);
	filename = "input/uf100-01.cnf";
	name = "uf100-01";
	Test(filename, name);
	filename = "input/uf250-01.cnf";
	name = "uf250-01";
	Test(filename, name);
}

