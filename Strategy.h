#include <iostream>
#include <vector>
#include "Data.h"
using namespace std;

class Strategy: public Data //Inherits the data class
{
public:
	int num_prices; //Number of prices to consider for moving average
	float std_devs; //The number of standard deviations for the bollinger bands
	float top_band; //Top Bollinger band
	float bottom_band; //Bottom Bollinger band
	int signal; //1 if buy, 0 if neutral, -1 if sell
	vector <float> price_data; //The vector of price data
	vector <float> sell_prices; //The vector of the prices the algorithm sold at.
	vector <float> buy_prices; //The vector of the prices the algorithm bought at.
	float avg(vector<float> &prices); //Finds the average of a vector of prices
	float std_dev(vector<float> &prices); //Finds the standard deviation of a vector of prices
	void bands(vector<float> &prices); //Defines the bands from a vector of prices
	void prompt();
	void run();
	void clip_shares();
	float sum(vector<float> &vec);
	vector<float> subset(int first, int last, vector<float> vec);
};

