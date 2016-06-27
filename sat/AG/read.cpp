#include "ag.h"
#include "read.h"

void ReadFile (string filename, Info *info){
	string line;
	int *clauses;
	ifstream input;
	istringstream iss;

	input.open ( filename.c_str() );

	if ( !input.is_open() ){
		cout << "Error opening file" << endl;
		abort();
	}
	int i =0;
	while ( getline (input, line) ){

		if ( line.at(0) == 'c' )
			continue;

		if ( line.at(0) == '%' )
			break;

		string subs;
		iss.str (line);

		if ( line.at(0) == 'p' ){
			int count = 0;

			while ( iss ) {

				count++;
				iss >> subs;

				if ( count == 3 )
					istringstream ( subs ) >> info->nVariables;

				if ( count == 4 )
					istringstream ( subs ) >> info->nClauses;
			}

			clauses =  ( int* ) malloc ( sizeof( int )*( info->nClauses )*3 );

		} else {
			while ( iss ) {

				int tmp;
				iss >> subs;
				istringstream ( subs ) >> tmp;

				if ( tmp != 0 ){
					clauses[i] = tmp;
					i++;
				}
			}
		}

		iss.clear();
	}

	input.close();

	info->clauses = clauses;

}
