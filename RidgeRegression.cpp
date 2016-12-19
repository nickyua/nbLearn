#include "includes.h"
#include "linearModels.h"
#include "nb\math\matrix.h"
#include "model.h"

void RidgeRegression::fit(Matrix &_X_train, vector<double> &_yTrain,double _l2, double _tolerance, double _step_size)
{
	assert(_X_train.size() == _yTrain.size() && "LinearRegression::fit: different dimension sizes");

	this->gradientDescent(_X_train, _yTrain, _l2, _tolerance, _step_size);
}

vector<double> RidgeRegression::featureDerivative(vector<double>& _errors, Matrix &_features) const {
	vector<double> result(_features[0].size(), 0);
	for (int i = 0; i < result.size(); i++)
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
vector<double> RidgeRegression::predict(Matrix &_X_test) const
{
	vector<double> result;
	for (int i = 0; i < _X_test.size(); i++)
	{
		double current_result = _X_test[i] * this->m_aWeights;
		result.push_back(current_result);
	}
	return result;
}

void RidgeRegression::gradientDescent(Matrix &_X_train, vector<double> &_yTrain, double _l2, double _tolerance, double _step_size)
{
	//	_tolerance = 0.01;
	bool converged = false;
	m_aWeights.resize(_X_train[0].size());
	for (int i = 0; i < m_aWeights.size(); i++)
	{
		m_aWeights[i] = (rand() % 2000 - 1000) / 100.0;
	}

	vector<double> predicts;
	vector<double> errors;
	vector<double> derivative;
	int amountSteps = 0;

	while (!converged /*&& amountSteps < 1e6*/)
	{
		predicts = predict(_X_train);
		errors = _yTrain - predicts;
		derivative = featureDerivative(errors, _X_train);
		double norm = norm2(derivative);
		//	derivative = derivative / norm;
		m_aWeights = (1.0 - 2* _l2 * _step_size) * m_aWeights - _step_size*derivative;
		m_aWeights[0] += _step_size*derivative[0];
		m_aWeights[0] /= (1.0 - 2 * _l2 * _step_size);
		m_aWeights[0] -= _step_size * derivative[0];
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


double RidgeRegression::evaluate(Matrix &_X_test, vector<double> &_y_test, double(*_evaluation_metric)(const vector<double>&y, const vector<double>&prediction)) const {
	vector<double> prediction = predict(_X_test);
	double score = _evaluation_metric(_y_test, prediction);
	return score;
}
