#pragma once
namespace metrics {
	static double rmse(const vector<double> &_y, const vector<double> &_prediction)
	{
		double result = 0;
		for (int i = 0; i < _y.size(); i++)
		{
			result += (_y[i] - _prediction[i]) * (_y[i] - _prediction[i]);
		}
		return result;
	}
}
