#include <iostream>
#include <vector>
#include "Performance.h"
using namespace std;

int main()
{
	Performance P; //Initializes an instance of the Performance class.
	P.run(2,20); //first parameter is the number of standard deviations for bands. 
				 //Second parameter is the number of periods in the moving average.
	cout<< "Sharpe Ratio: " << P.sharpe_ratio() << endl;
	
	system("pause");
}