#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Data
{
protected:
	vector <float> read_csv(string filename); //Reads in a .csv file and returns the contents as a vector
};
#endif