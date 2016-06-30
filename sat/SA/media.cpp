#include "media.h"
#include <cmath>


void Read ( string name){
	string line;
	ifstream input0, input1, input2, input3, input4, input5, input6, input7, input8, input9 ;

	stringstream out;
	out << "out/out0" << name << ".csv";
	string f0 = out.str();
	input0.open ( f0.c_str() );

	stringstream out1;
	out1 << "out/out1" << name << ".csv";
	string f1 = out1.str();
	input1.open ( f1.c_str() );

	stringstream out2;
	out2 << "out/out2" << name << ".csv";
	string f2 = out2.str();
	input2.open ( f2.c_str() );

	stringstream out3;
	out3 << "out/out3" << name << ".csv";
	string f3 = out3.str();
	input3.open ( f3.c_str() );

	stringstream out4;
	out4 << "out/out4" << name << ".csv";
	string f4 = out4.str();
	input4.open ( f4.c_str() );

	stringstream out5;
	out5 << "out/out5" << name << ".csv";
	string f5 = out5.str();
	input5.open ( f5.c_str() );

	stringstream out6;
	out6 << "out/out6" << name << ".csv";
	string f6 = out6.str();
	input6.open ( f6.c_str() );

	stringstream out7;
	out7 << "out/out7" << name << ".csv";
	string f7 = out7.str();
	input7.open ( f7.c_str() );

	stringstream out8;
	out8 << "out/out0" << name << ".csv";
	string f8 = out8.str();
	input8.open ( f8.c_str() );

	stringstream out9;
	out9 << "out/out0" << name << ".csv";
	string f9 = out9.str();
	input9.open ( f9.c_str() );

	ofstream outmedia;

	stringstream outm;
	outm << "out/media" << name << ".csv";
	string fmedia = outm.str();
	outmedia.open ( fmedia.c_str() );

	if ( !input0.is_open() && !input1.is_open() && 
		 !input2.is_open() && !input3.is_open() && 
		 !input4.is_open() && !input5.is_open() &&
		 !input6.is_open() && !input7.is_open() && 
		 !input8.is_open() && !input9.is_open() && 
		 !outmedia.is_open () )
	{
		cout << "Error opening file" << endl;
		abort();
	}

	istringstream iss;

	while ( getline (input0, line) ){
		
		long double sumEnergy = 0, sumA = 0;
		int i, energy[10];
		double t, a[10];
		string subs;

		iss.str (line);
		iss >> subs;
		istringstream ( subs ) >> i;
		iss >> subs;
		istringstream ( subs ) >> t;
		iss >> subs;
		istringstream ( subs ) >> energy[0];
		iss >> subs;
		istringstream ( subs ) >> a[0];
		iss.clear();

	    getline (input1, line);
	    iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[1];
		iss >> subs;
		istringstream ( subs ) >> a[1];
		iss.clear();

		getline (input2, line);
		iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[2];
		iss >> subs;
		istringstream ( subs ) >> a[2];
		iss.clear();

		getline (input3, line);
		iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[3];
		iss >> subs;
		istringstream ( subs ) >> a[3];
		iss.clear();

		getline (input4, line);
		iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[4];
		iss >> subs;
		istringstream ( subs ) >> a[4];
		iss.clear();

		getline (input5, line);
		iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[5];
		iss >> subs;
		istringstream ( subs ) >> a[5];
		iss.clear();

		getline (input6, line);
		iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[6];
		iss >> subs;
		istringstream ( subs ) >> a[6];
		iss.clear();

		getline (input7, line);
		iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[7];
		iss >> subs;
		istringstream ( subs ) >> a[7];
		iss.clear();

		getline (input8, line);
		iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[8];
		iss >> subs;
		istringstream ( subs ) >> a[8];
		iss.clear();

		getline (input9, line);
		iss.str (line);
		iss >> subs;
		iss >> subs;
		iss >> subs;
		istringstream ( subs ) >> energy[9];
		iss >> subs;
		istringstream ( subs ) >> a[9];
		iss.clear();
	
		for (int j = 0; j < 10; ++j)
		{
			sumEnergy += energy[j];
			sumA += a[j];  
		}

		double mEnergy = sumEnergy/10.0, mA = sumA/10.0, varE = 0, varA = 0;

		for (int j = 0; j < 10; ++j)
		{
			varE += pow((energy[j] - mEnergy), 2);
			varA += pow((a[j] - mA), 2);
		}

		double desE = sqrt(varE/10.0), desA = sqrt(varA/10.0);


		outmedia << i << " " << t << " " << mEnergy << " " << desE << " " << mA << " " << desA <<endl;
	}

	input0.close();
	input1.close();
	input2.close();
	input3.close();
	input4.close();
	input5.close();
	input6.close();
	input7.close();
	input8.close();
	input9.close();

}
