#include <iostream>
#include <vector>
#include "Strategy.h"
#include <string>
#include <cmath>
using namespace std;

float Strategy::avg(vector<float> prices)
//Takes in a vector of floats and returns the average of them.
{
	float sum = 0;
	for(int i = 0; i < prices.size(); i++)
	{
		sum += prices.at(i);
	}
	float avg = sum/prices.size();
	return avg;
}

float Strategy::std_dev(vector<float> prices)
	//Returns the standard deviation of a vector of prices
{
	float mean = avg(prices);
	float diff_mean = 0;
	for(unsigned int i = 0; i < prices.size(); i++)
	{
		diff_mean += pow(mean-prices.at(i),2);
	}
	float variance = diff_mean/prices.size();
	return sqrt(variance);
}

void Strategy::bands(vector<float> prices,float standard_devs)
	//Defines the Bollinger bands
{
	top_band = avg(prices) + std_dev(prices)*standard_devs;
	bottom_band = avg(prices) - std_dev(prices)*standard_devs;

	//Fills in the vectors used for graphing.
	top_band_vec.push_back(top_band);
	bottom_band_vec.push_back(bottom_band);
}

vector<float> Strategy::subset(int first, int last, vector<float> vec)
	//Subsets a vector into a smaller vector
{
	vector<float>::const_iterator beg = vec.begin() + first;
	vector<float>::const_iterator end = vec.begin() + last;
	vector<float> subset_vec(beg,end);
	return subset_vec;
}

float Strategy::sum(vector<float> vec)
	//Sums the components of a vector.
{
	float sum = 0;
	for(unsigned int i = 0; i < vec.size();i++)
	{
		sum += vec.at(i);
	}
	return sum;
}

void Strategy::sell(int num_shares,float price)
{
	//Sells a number of shares at a certain price
	for(int i = 0; i < num_shares;i++)
			{
				sell_prices.push_back(price);
			}
}

void Strategy::buy(int num_shares,float price)
	//Buys a number of shares at a certain price
{
	for(int i = 0; i < num_shares;i++)
			{
				buy_prices.push_back(price);
			}
}
void Strategy::run(float std_devs,int num_prices)
	//Runs the trading strategy.
{
	string file_path = "C:/Users/Class2016/Downloads/ADS.csv"; //Change this to the appropriate path
	price_data = read_csv(file_path);
	signal = 0;
	int prev_signal = 0;
	int share_count = 0;
	int total_share_count = 0;
	float band_diff = 0.0;
	float temp_buy = 0.0;
	float temp_sell = 0.0;
	for(int index = num_prices + 1; index < price_data.size(); index++)
		//Iterates through all of the data. This is the main loop in our strategy.
	{
		vector<float> prices_subset = subset(index - num_prices - 1,index,price_data); //Subsets the data vector into a smaller one to calculate the rolling moving average.
		bands(prices_subset,std_devs);
		float current_price = price_data[index];
		if(current_price > top_band)
			//If the share price is above the threshold -> sell
		{
			signal = -1;
			if(prev_signal == 1)
				//If the previous period was below the bottom band, liquidate shares.
				{
					sell(total_share_count,current_price);
					temp_sell += total_share_count*current_price;
					if(temp_buy != 0){
					//Calculates the return of the transaction.
					returns.push_back((temp_sell-temp_buy)/temp_buy);
					}
					temp_sell = 0;
					temp_buy = 0;
					total_share_count = 0;
				}
			share_count = ceil((current_price - top_band)/std_dev(prices_subset)); //Calculates the amount of shares to buy.
			//Buys and sells based on the number of standard deviations the price is outside the band.
			total_share_count += share_count;
			sell(share_count,current_price);
			temp_sell += share_count*current_price;
			
		}
		else{
			//If the share price is below the threshold -> buy
			if(current_price < bottom_band)
			{
				signal = 1;
				if(prev_signal == -1)
				{
					buy(total_share_count,current_price);
					temp_buy += total_share_count*current_price;
					if(temp_buy != 0){
					returns.push_back((temp_sell-temp_buy)/temp_buy);
					}
					temp_sell = 0;
					temp_buy = 0;
					total_share_count = 0;
				}
				share_count = ceil((bottom_band - current_price)/std_dev(prices_subset));
				total_share_count += share_count;
				buy(share_count,current_price);
				temp_buy += share_count*current_price;
				
			}
			else
				//If it's in between, check if you just sold or bought. If so, liquidate position. If not, do nothing.
			{
				signal = 0;
				if(prev_signal == 1)
					//If you were below the band in the previous period, liquidate position.
				{
					sell(total_share_count,current_price);
					temp_sell += total_share_count*current_price;
					if(temp_buy != 0){
					returns.push_back((temp_sell-temp_buy)/temp_buy);
					}
					temp_sell = 0;
					temp_buy = 0;
				}
				if(prev_signal == -1)
					//If you were above the band in the previous period, liquidate position.
				{
					buy(total_share_count,current_price);
					temp_buy += total_share_count*current_price;
					if(temp_buy != 0){
					returns.push_back((temp_sell-temp_buy)/temp_buy);
					}
					temp_sell = 0;
					temp_buy = 0;
				}
				total_share_count = 0;

			}
		}
		prev_signal = signal;
		signal_vec.push_back(signal);
	}

	cout<< "Buys: " << buy_prices.size() << endl;
	cout<< "Sells: " << sell_prices.size() << endl;
	cout<< "Average Return: " << avg(returns) << endl;
	cout<< "Profit: " << sum(sell_prices) - sum(buy_prices) << endl;
}