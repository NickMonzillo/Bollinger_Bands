#include "Strategy.h"
class Performance: public Strategy
{
public:
	Performance();
	float sharpe_ratio();
private:
	float risk_free;
	void write_file(vector<float> input_vec, string filename);
};