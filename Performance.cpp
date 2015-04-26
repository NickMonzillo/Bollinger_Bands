#include "Performance.h"
#include <ostream>

Performance::Performance()
{
}

void Performance::write_file(vector<float> input_vec, string filename)
{
	ofstream outputFile (filename);
	for(int i = 0;i < input_vec.size();i++)
	{
		outputFile << input_vec[i];
		outputFile << '\n';
	}
}

float Performance::sharpe_ratio()
{
	vector<float> risk_free_data = read_csv("../CSV/RiskFree.csv");
	for(int i = 0;i<risk_free_data.size();i++)
	{
		if(risk_free_data.at(i) > 1)
		{
			cout<< risk_free_data.at(i) << endl;
		}
	}
	risk_free = avg(risk_free_data);
	return (avg(returns) - risk_free)/std_dev(returns);
}