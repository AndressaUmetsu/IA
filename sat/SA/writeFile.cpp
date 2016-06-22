#include "writeFile.h"


void WriteTemperature (double temp){
	ofstream outTemp;
	outTemp.open ("outTemp1.dat");
	outTemp << temp;
  	outTemp.close();

}