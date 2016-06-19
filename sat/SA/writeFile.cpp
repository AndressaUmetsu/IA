#include "writeFile.h"


void WriteTemperature (double temp){
	ofstream outTemp;
	outTemp.open ("outTemp.dat");
	outTemp << temp;
  	outTemp.close();

}