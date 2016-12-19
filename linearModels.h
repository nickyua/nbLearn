#pragma once
#include "includes.h"
#include "nb\math\matrix.h"
#include "model.h"

using namespace nb::math;
class LinearModel : Model
{
public:
	// virtual void fit(Matrix &_X_train, vector<double> &_yTrain, double _tolerance, double _step_size) = 0;
	 virtual vector<double> predict(Matrix &_X_test) const = 0;
	 virtual double evaluate(Matrix &_X_test, vector<double> &_yTest, double(*_evaluation_metric)(const vector<double>&y, const vector<double>&prediction)) const = 0;
	 virtual vector<double> getWeights() = 0; 
	 double getIntercept() { return m_fIntercept; }
	 LinearModel(double _fLearningRate = 1.0, bool _bFitIntercept = true, bool _bNormalize = false) 
		 : Model(_bNormalize), m_bFitIntercept(_bFitIntercept), m_fLearningRate(_fLearningRate) {};
private:

protected:
	double m_fIntercept;
	bool m_bFitIntercept;
	double m_fLearningRate;
	vector<double> m_aWeights;
	//virtual vector<double> featureDerivative(vector<double>&_errors, Matrix &_features) const = 0;

};


class LinearRegression : LinearModel{
public:
	void fit(Matrix &_X_train, vector<double> &_yTrain, double _tolerance = 0.00001, double _step_size = 1e-6);
	vector<double> predict(Matrix &_X_test) const ;
	double evaluate(Matrix &_X_test, vector<double> &_y_test, double(*_evaluation_metric)(const vector<double>&y, const vector<double>&prediction)) const;
	LinearRegression(double _fLearningRate = 1.0, bool _bFitIntercept = true, bool _bNormalize = false)
		: LinearModel(_bNormalize, _fLearningRate, _bFitIntercept) {};
	vector<double> getWeights() {return this->m_aWeights;};
private:
	//vector<double> gradientDescentStep();
//	void gradientDescent(Matrix _X_train, vector<double> _y_train);
	vector<double> featureDerivative(vector<double>&_errors, Matrix &_features) const;
	void gradientDescent(Matrix &_X_train, vector<double> &_yTrain, double _tolerance = 0.001, double _step_size = 0.001);

protected:

};


class RidgeRegression : LinearModel {
public:
	void fit(Matrix &_X_train, vector<double> &_y_train, double _l2 = 10, double _tolerance = 1e-1, double _step_size = 1e-6);
	vector<double> predict(Matrix &_X_test) const;
	double evaluate(Matrix &_X_test, vector<double> &_y_test, double(*_evaluation_metric)(const vector<double>&y, const vector<double>&prediction)) const;
	RidgeRegression(double _fLearningRate = 1.0, bool _bFitIntercept = true, bool _bNormalize = false, double _fAlpha = 0.0)
		: LinearModel(_bNormalize, _fLearningRate, _bFitIntercept), m_fAlpha(_fAlpha) {};
	vector<double> getWeights() { return this->m_aWeights; };
private:
	double m_fAlpha;
protected:
	void gradientDescent(Matrix &_X_train, vector<double> &_yTrain, double _l2 = 10, double _tolerance = 0.001, double _step_size = 0.001);
	vector<double> featureDerivative(vector<double>& _errors, Matrix &_features) const;
};


class Lasso : LinearModel {
public:
	void fit(Matrix &_X_train, vector<double> &_y_train, double _l1 = 10, double _tolerance = 1e-1, double _step_size = 1e-6);
	vector<double> predict(Matrix &_X_test) const ;
	double evaluate(Matrix &_X_test, vector<double> &_y_test, double(*_evaluation_metric)(const vector<double>&y, const vector<double>&prediction)) const;
	Lasso(double _fLearningRate = 1.0, bool _bFitIntercept = true, bool _bNormalize = false, double _fAlpha = 0.0)
		: LinearModel(_bNormalize, _fLearningRate, _bFitIntercept), m_fAlpha(_fAlpha) {};
private:
	double m_fAlpha;
	void gradientDescent(Matrix &_X_train, vector<double> &_yTrain, double _l1, double _tolerance, double _step_size);
protected:
	vector<double> featureDerivative(vector<double>& _errors, Matrix &_features) const;
};

//vector operations
double operator*(const vector<double>&_a, const vector<double> &_b) ;
vector<double> operator-(const vector<double>&_a, const vector<double> &_b) ;
vector<double> operator+(const vector<double>&_a, const vector<double> &_b);
vector<double> operator*(const double &_a, const vector<double> &_b);
vector<double> operator/(const vector<double> &_a, const double &_b);

double norm2(const vector<double>&_a);

//metrics
