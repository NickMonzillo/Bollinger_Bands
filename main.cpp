#include <iostream>
#include <vector>
#include "Performance.h"
using namespace std;

int main()
{

	Performance P;
	P.run(2,20);
	cout<< "Sharpe Ratio: " << P.sharpe_ratio() << endl;
	system("pause");
}