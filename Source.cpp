#include <iostream>
#include <stdio.h>

using namespace std;
#include "nb\math\matrix.h"
#include "constants.h"
#include "nb\std\BaseException.h"
#include "nb\std\InvalidIndex.h"
#include "nb\std\std.h"
#include "nb\math\longNum.h"
#include "nb\math\vector.h"
#include "nb\stl\stl.h"
#include "nb\stl\vector.h"
#include "model.h"
#include "includes.h"
#include "linearModels.h"
int main()
{

//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int amountObservations = 5;
	int amountFeatures = 3;
	Matrix X_train(amountObservations, amountFeatures + 1);
	vector<double> y_train(amountObservations);
	for (int i = 0;i < amountObservations; i++)
	{
		X_train[i][0] = 1;
		for (int j = 1;j <= amountFeatures; j++)
		{
			int val = rand() % 100;
			X_train[i][j] = val;
		}
		y_train[i] = X_train[i][0] * 5 + X_train[i][1] * 3 + X_train[i][2] * 5 + X_train[i][3] * (-1);
	}
	X_train.print();
	RidgeRegression model;
	model.fit(X_train, y_train);
	vector<double> weights = model.getWeights();
	for (int i = 0;i < weights.size(); i++)
	{
		cout << weights[i] << " "; 
	}
/*	int *data = new int[5];
	data[0] = 1;
	data[1] = 2;
	data[2] = 3;
	data[3] = 5;
	data[4] = 6;

	nb::stl::nbVector<int> b(data, 5);
//	b.pop_back();

	b.push_back(6);
	b.push_back(7);
//	b.pop_back();
//	b.erase(6, 1);
	nb::stl::nbVector<int> c = b.find(6);
	b = c;
	b.show();
	nb::math::Matrix a(4, 3, 2);
	a.print();*/
	system("pause");
	return 0;
}