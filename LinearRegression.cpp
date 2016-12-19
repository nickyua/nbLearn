#include "includes.h"
#include "linearModels.h"
#include "nb\math\matrix.h"
#include "model.h"

void LinearRegression::fit(Matrix &_X_train, vector<double> &_yTrain, double _tolerance, double _step_size){
	assert(_X_train.size() == _yTrain.size() && "LinearRegression::fit: different dimension sizes");

	this->gradientDescent(_X_train, _yTrain, _tolerance, _step_size);
}

vector<double> LinearRegression::featureDerivative(vector<double>& _errors, Matrix &_features) const{
	 vector<double> result(_features[0].size(), 0);
	 for (int i = 0;i < result.size(); i++)
	 {
		 for (int j = 0; j < _errors.size(); j++)
		 {
			 double error = _errors[j];
			 double feature = _features[j][i];
			 //double tfeature = _features[i][j];
			 result[i] += 2 * _errors[j] * (-_features[j][i]);
		 }
	 }
	 return result;
}

vector<double> LinearRegression::predict(Matrix &_X_test) const
{
	vector<double> result ;
	for (int i = 0;i < _X_test.size(); i++)
	{
		double current_result = _X_test[i] * this->m_aWeights;
		result.push_back(current_result);
	}
	return result;
}

void LinearRegression::gradientDescent(Matrix &_X_train, vector<double> &_yTrain, double _tolerance, double _step_size)
{
//	_tolerance = 0.01;
	bool converged = false;
	m_aWeights.resize(_X_train[0].size());
	for (int i = 0;i < m_aWeights.size(); i++)
	{
		m_aWeights[i] = (rand() % 2000 - 1000) / 100.0;
	}

	vector<double> predicts;
	vector<double> errors;
	vector<double> derivative;
	int amountSteps = 0;
	_step_size = 1e-6;
	while (!converged /*&& amountSteps < 1e6*/)
	{
		predicts = predict(_X_train);
		errors = _yTrain - predicts;
		derivative = featureDerivative(errors, _X_train);
		double norm = norm2(derivative);
	//	derivative = derivative / norm;
		m_aWeights = m_aWeights - _step_size*derivative;
		if (norm < _tolerance) 
		{
			converged = true;
		}
		amountSteps++;
		if (amountSteps % 100000 == 0)
		{
			printf("%d %f\n", amountSteps, norm);
		}
	}
}


double LinearRegression::evaluate(Matrix &_X_test, vector<double> &_y_test, double (*_evaluation_metric)(const vector<double>&y, const vector<double>&prediction)) const{
	vector<double> prediction = predict(_X_test);
	double score = _evaluation_metric(_y_test, prediction);
	return score;
}

double operator*(const vector<double>&_a, const vector<double> &_b) 
{
	assert(_a.size() == _b.size() && "different sizes");
	double result = 0;
	for (int i = 0;i < _a.size(); i++)
	{
		result += _a[i] * _b[i];
	}
	return result;
}

vector<double> operator*(const double &_a, const vector<double> &_b)
{
	vector<double> result(_b.size());
	for (int i = 0; i < _b.size(); i++)
	{
		result[i] = _a * _b[i];
	}
	return result;
}

vector<double> operator/(const vector<double> &_a, const double &_b)
{
	assert(_b != 0 && "division by zero");
	vector<double> result(_a.size());
	for (int i = 0; i < _a.size(); i++)
	{
		result[i] = _a[i] / _b;
	}
	return result;
}

vector<double> operator-(const vector<double>&_a, const vector<double> &_b) 
{
	assert(_a.size() == _b.size() && "different sizes");
	vector<double> result(_a.size(), 0);
	for (int i = 0; i < _a.size(); i++)
	{
		result[i] = _a[i] - _b[i];
	}
	return result;
}

vector<double> operator+(const vector<double>&_a, const vector<double> &_b)
{
	assert(_a.size() == _b.size() && "different sizes");
	vector<double> result(_a.size(), 0);
	for (int i = 0; i < _a.size(); i++)
	{
		result[i] = _a[i] + _b[i];
	}
	return result;
}


double norm2(const vector<double>&_a)
{
	double result = 0;
	for (int i = 0; i < _a.size(); i++)
	{
		result += _a[i] * _a[i];
	}
	return sqrt(result);
}