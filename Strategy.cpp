#include <iostream>
#include <vector>
#include "Strategy.h"
#include <cmath>
using namespace std;

float Strategy::avg(vector<float> &prices)
//Takes in a vector of floats and returns the average of them.
{
	float sum = 0;
	for(int i = 0; i < prices.size(); i++)
	{
		sum += prices[i];
	}
	float avg = sum/prices.size();
	return avg;
}

float Strategy::std_dev(vector<float> &prices)
	//Returns the standard deviation of a vector of prices
{
	float mean = avg(prices);
	float diff_mean = 0;
	for(int i = 0; i < prices.size(); i++)
	{
		diff_mean += pow(mean-prices.at(i),2);
	}
	float variance = diff_mean/prices.size();
	return sqrt(variance);
}

void Strategy::bands(vector<float> &prices)
	//Defines the Bollinger bands
{
	top_band = avg(prices) + std_dev(prices)*std_devs;
	bottom_band = avg(prices) - std_dev(prices)*std_devs;
}

void Strategy::prompt()
	//Prompts the user for input
{
	cout<< "Number of std deviations for the Bollinger bands: ";
	cin>> std_devs;
	cout<<"Number of periods in the moving average: ";
	cin>> num_prices;
	//cout<< ".csv path: ";
	string file_path = "C:/Users/Class2016/Downloads/ALLdata.csv";
	price_data = read_csv(file_path);
}

vector<float> Strategy::subset(int first, int last, vector<float> vec)
	//Subsets a vector into a smaller vector
{
	vector<float>::const_iterator beg = vec.begin() + first;
	vector<float>::const_iterator end = vec.begin() + last;
	vector<float> subset_vec(beg,end);
	return subset_vec;
}

float Strategy::sum(vector<float> &vec)
	//Sums the components of a vector.
{
	float sum = 0;
	for(int i = 0; i<vec.size();i++)
	{
		sum += vec.at(i);
	}
	return sum;
}

void Strategy::clip_shares()
	//Removes the excess shares to make the buys and sells equal in number.
{
	int(difference) = buy_prices.size() - sell_prices.size();
	if(difference > 0)
	{
		buy_prices = subset(0,buy_prices.size() - difference,buy_prices);
	}

	if(difference < 0)
	{
		sell_prices = subset(0,sell_prices.size() - abs(difference),sell_prices);
	}
}

void Strategy::run()
	//Runs the trading strategy.
{

	for(int index = num_prices + 1; index < price_data.size(); index++)
	{
		vector<float> prices_subset = subset(index - num_prices - 1,index,price_data);
		bands(prices_subset);
		float current_price = price_data[index];
		if(current_price > top_band)
		{
			for(int i = 0; i < ceil(current_price - top_band);i++)
			{
				sell_prices.push_back(current_price);
			}
		}
		if(current_price < bottom_band)
		{
			for(int i = 0; i < ceil(bottom_band - current_price);i++)
			{
				buy_prices.push_back(current_price);
			}
		}
	}
	clip_shares();
	cout<< "Buys: " << buy_prices.size() << endl;
	cout<< "Sells: " << sell_prices.size() << endl;
	cout<<"Profit: " << sum(sell_prices) - sum(buy_prices) << endl;
}