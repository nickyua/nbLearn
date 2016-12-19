#pragma once
#include "includes.h"
#include "nb\math\matrix.h"
#include "metrics.h"

using namespace nb::math;

class Model 
{
private:

protected:
//	vector<double> m_aWeights;
	bool m_bNormalize;

public:
	Model(bool _bNormalize = false) : m_bNormalize(_bNormalize) {};
	//virtual void fit(Matrix &_X_train, vector<double> &_yTrain, double _tolerance, double _step_size) = 0;
	virtual vector<double> predict(Matrix &_X_test) const = 0;
	virtual double evaluate(Matrix &_X_test, vector<double> &_yTest, double(*_evaluation_metric)(const vector<double>&y, const vector<double>&prediction) = metrics::rmse) const = 0;
};

