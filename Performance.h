#include "Strategy.h"
class Performance: public Strategy
{
public:
	Performance();
	float sharpe_ratio(); //Calculates the Sharpe ratio based on the returns vector.
	
private:
	float risk_free;
	void matrix(); //Creates the matrix used to find the optimal arguments for the strategy.
	vector <vector <float>> sharpe_matrix;
	void write_file(vector<vector<float>> input_vec, string filename); //Writes a vector of vectors to a .txt file
};