#include "sa.h"
#include "readFile.h"
#include "media.h"
#include <sys/time.h>

void TestIn();

double Test(string filename, string name);

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

	int bestEnergy = SimAnnealing (info, "out.csv", "uf20-01");

	cout << info.nVariables << " " << info.nClauses << endl << "Numero de clausulas não satisfeitas " << bestEnergy << endl;
}

double Test(string filename, string name){
	Info info;
	int bestEnergy;

  	struct timeval start, end;
    double tmili = 0;

	ReadFile (filename, &info);

	for (int i = 0; i < 10; ++i){
		stringstream out, out1;
		out << "out/out" << i << name << ".csv";
		filename = out.str();

		out1 << i << name;
		name = out1.str();

		gettimeofday(&start, NULL);
		bestEnergy = SimAnnealing (info, filename, name);
	    gettimeofday(&end, NULL);
	    tmili += (int) (1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000);
	}
	return tmili/10.0;
}

void TestIn(){

	ofstream out;
	out.open ( "out/mediaTempo.csv" );

	double t;

	string filename = "input/uf20-01.cnf";
	string name = "uf20-01";
	t = Test(filename, name);
	Read(name);
	out << t << endl;

	filename = "input/uf50-01.cnf";
	name = "uf50-01";
	t = Test(filename, name);
	Read(name);
	out << t << endl;

	filename = "input/uf75-01.cnf";
	name = "uf75-01";
	t = Test(filename, name);
	Read(name);
	out << t << endl;

	filename = "input/uf100-01.cnf";
	name = "uf100-01";
	t = Test(filename, name);
	Read(name);
	out << t << endl;

	filename = "input/uf250-01.cnf";
	name = "uf250-01";
	t = Test(filename, name);
	Read(name);
	out << t << endl;
	out.close();
}

