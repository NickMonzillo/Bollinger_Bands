#ifndef STRATEGY_H
#define STRATEGY_H
#include <iostream>
#include <vector>
#include "Data.h"
using namespace std;

class Strategy: public Data //Inherits the data class
{
public:
	void run(float std_devs, int num_prices); //Runs the trading strategy
protected:
	float avg(vector<float> prices); //Finds the average of a vector of prices
	float std_dev(vector<float> prices); //Finds the standard deviation of a vector of prices
	vector <float> returns;
	vector <float> sell_prices; //The vector of the prices the algorithm sold at.
	vector <float> buy_prices; //The vector of the prices the algorithm bought at.
private:
	vector <float> price_data; //The vector of price data
	
	//Vectors used to generate graphs
	vector <float> bottom_band_vec; 
	vector <float> top_band_vec;
	vector <float> signal_vec;

	int num_prices; //Number of prices to consider for moving average
	float std_devs;//float std_devs; //The number of standard deviations for the bollinger bands
	float top_band; //Top Bollinger band
	float bottom_band; //Bottom Bollinger band
	int signal; //1 if buy, 0 if neutral, -1 if sell
	
	float sum(vector<float> vec); //Sums the contents of a vector
	vector<float> subset(int first, int last, vector<float> vec); //Creates a subset of vector. The first and last parameters are the indices of vec that the function returns between.
	void sell(int num_shares, float price);
	void buy(int num_shares, float price);
	void bands(vector<float> prices, float standard_devs); //Defines the bands from a vector of prices
};

#endif