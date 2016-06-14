#include "sa.h"

ReadFile (){
	string line;
	ifstream arq;
	istringstream iss;
	arq.open ( "uf20-01.cnf" );

	if ( arq.is_open() ){
		
		while ( getline (arq, line) ){
			
			if ( line.at(0) != 'c' ){
				//Virar função
				if ( line.at(0) == 'p' ){
					iss.str ( line );
					int cont = 0;
					while (iss) {
						string subs;
						iss >> subs;
						cout << "subs " << subs << endl; 
						cont++;
					}
					cout << cont << endl;
				} else {
					//Virar função
					istringstream iss;
					iss.str (line);
					int cont = 0;
					while (iss) {
						string subs;
						iss >> subs;
						cout << "subs " << subs << endl; 
						cont++;
					}
					cout << cont << endl;

					//cout << line << '\n';
				}

			}
		}
		arq.close();
	}
}

