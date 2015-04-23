#include <iostream>
#include <string>
#include "Data.h"
#include <fstream>
using namespace std;

vector<float> Data::read_csv(string filename)
{
	ifstream in(filename);
	if(in)
	{
		string line;
		while(getline(in,line))
		{
			prices.push_back(stod(line));
		}
	}
	in.close();
	return prices;
}