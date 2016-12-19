#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <exception>
#include "D:\Projects\VS\cplusplus\nbLearn\nbLearn\nb\std\BaseException.h"
#include "D:\Projects\VS\\cplusplus\nbLearn\nbLearn\constants.h"

using namespace std;

namespace nb
{
	namespace math
	{
//		template <class double>
		class Matrix
		{
		private:
			vector<vector<double>> m_aData;
			vector<vector<double>> m_aTData;
			vector<double> m_aEigen;
			vector<vector<double>> m_aIData;
			bool m_bIsChanged;
			static double Matrix::SumTwoObjects(double &_a, double &_b)
			{
				return _a + _b;
			}

			static double Matrix::DiffTwoObjects(double &_a, double &_b)
			{
				return _a - _b;
			}

			//!!!!!!!!!!!!! only for + and - !!!!!!!!!!!!
			static Matrix Matrix::makeBinaryAction(Matrix &_a, Matrix &_b, double(*action)(double &x, double &y))
			{
				pair<int, int> asize = _a.getSize();
				pair<int, int> tsize = _b.getSize();
				//				MessageBox(nullptr, TEXT("The driver is sleeping!!"), TEXT("Message"), MB_ICONERROR);
				//assert(_a.getSize() == this->getSize() && "nbMatrix::operator (+ or -) : Dimensions doesn't matches!");
				try
				{
					if (_a.getSize() != _b.getSize()) throw nb::std::BaseException("Matrix::makeBinaryAction: ", "Dimensions doesn't matches");

					Matrix res(_a.getSize(), 0);
					for (int i = 0; i < res.getSize().first; i++)
					{
						for (int j = 0; j < res.getSize().second; j++)
						{
							res[i][j] = action(_a[i][j], _b[i][j]);
						}
					}
					return res;
				}
				catch (nb::std::BaseException &be)
				{
					cout << "BaseException: " << be.what() << endl;
					throw nb::std::BaseException("Matrix::makeBinaryAction: ", "Dimensions doesn't matches");
				}
				catch (exception &e)
				{
					cout << "Exception: " << e.what();
					throw nb::std::BaseException("Matrix::makeBinaryAction: ", e.what());
				}
				catch (...)
				{
					cout << "Unexpected exception!";
					throw nb::std::BaseException("Matrix::makeBinaryAction: ", "Unexpected exception");
				}
				return Matrix();
			}

			double CountCell(vector<double> &_a, vector<double> &_b)
			{
				double res = 0;
				for (int i = 0; i < _a.size(); i++)
				{
					res += _a[i] * _b[i];
				}
				return res;
			}
			Matrix Matrix::MakeMultyplication(Matrix &_a, Matrix &_b)
			{
				assert(_b.getSize().first == _a.getSize().second && "Matrix::MakeMultyplycation: dimensions don't match");
				Matrix res(_a.getSize().first, _b.getSize().second);
				Matrix aBTransposeMatrix = _b.getTransposeMatrix();
				for (int i = 0; i < res.getSize().first; i++)
				{
					for (int j = 0; j < res.getSize().second; j++)
					{
						res[i][j] = CountCell(_a[i], aBTransposeMatrix[j]);
					}
				}
				return res;
			}

			static bool Matrix::isEqual(const Matrix &_a, const Matrix &_b)
			{
				try
				{
					if (_a.getSize() != _b.getSize())
					{
						return false;
					}
					for (int i = 0; i < _a.getSize().first; i++)
					{
						for (int j = 0; j < _a.getSize().second; j++)
						{
							if (_a[i][j] != _b[i][j])
							{
								return false;
							}
						}
					}
				}
				catch (...)
				{
					cout << "Unexpected exception!\n";
					throw nb::std::BaseException("Matrix::isEqual: ", "Unexpected exception!");
				}
				return true;
			}

			static void Matrix::ClearMatrix(vector<vector<double>> _matrix)
			{
				for (int i = 0; i < _matrix.size(); i++)
				{
					_matrix[i].clear();
				}
				_matrix.clear();
			}

			static vector<vector<double>> Matrix::TransposeMatrix(vector<vector<double>> &_a)
			{
				vector<vector<double>> aTransposeMatrix(_a[0].size());
				for (int i = 0; i < _a[0].size(); i++)
				{
					aTransposeMatrix[i].resize(_a.size());
				}
				//				ClearMatrix(_a);
				for (int i = 0; i < _a.size(); i++)
				{
					for (int j = 0; j < _a[0].size(); j++)
					{
						aTransposeMatrix[j][i] = _a[i][j];
					}
				}
				return aTransposeMatrix;
			}

			static double Matrix::DeterminantMatrix(Matrix &_a)
			{

			}

			static Matrix Matrix::InverseMatrix(Matrix &_a)
			{

			}

			//	static vector<double> 
		public:
			//constructors
			Matrix()
			{

			}

			Matrix(int nrow, int ncol, int value = 0)
			{
				//assert(nrow * ncol < c_nMaxElementsInMatrix && "nbMatrix::constructor: too many items in matrix");
				try
				{
					m_aData.resize(nrow);
					for (int i = 0; i < nrow; i++)
					{
						m_aData[i].resize(ncol, value);
					}
					m_bIsChanged = false;
				}
				catch (bad_alloc &ba)
				{
					cout << "bad_alloc: " << ba.what() << endl;
					throw nb::std::BaseException("Matrix: ", "bad_alloc. Try to allocate too much memory");
				}
				catch (length_error &le)
				{
					throw nb::std::BaseException("Matrix: ", "Try to allocate negative size of array.");
				}
				catch (exception &e)
				{
					throw nb::std::BaseException("Matrix: ", e.what());
				}
			}

			Matrix(pair<int, int>dim, int value = 0) : Matrix(dim.first, dim.second, value) {}

			Matrix(Matrix&a)
			{
				this->m_aData = a.getData();
				m_bIsChanged = false;
			}

			Matrix(const Matrix&a)
			{
				this->m_aData = a.getData();
				m_bIsChanged = false;
			}
			Matrix(vector<vector<double>> _data)
			{
				int nrow = _data.size();
				int ncol = _data[0].size();
				assert(nrow * ncol < c_nMaxElementsInMatrix && "nbMatrix::constructor: too many items in matrix");
				//				assert(nrow * ncol < 1e7 && "nbMatrix::constructor: too many items in matrix");
				m_aData.resize(nrow);
				for (int i = 0; i < nrow; i++)
				{
					m_aData[i].resize(ncol);
					for (int j = 0; j < ncol; j++)
					{
						m_aData[i][j] = _data[i][j];
					}
				}
				m_bIsChanged = false;
			}
			//destructors
			~Matrix()
			{
				m_aData.clear();
			}

			int Matrix::size(){return m_aData.size();}
			//getters
			vector<double>& Matrix::operator[](int i) const 
			{

				//assert(i >= 0 && i < m_aData.size() && "Index is out of bounds");
				try
				{
//					m_bIsChanged = true;
					vector <double> aResult = m_aData.at(i);
					return aResult;
				}
				catch (out_of_range &oor)
				{
					const char *sWhat = oor.what();
					char *sMsg = new char[strlen(oor.what()) + 20];
					char *sExc = new char[strlen(oor.what()) + 20];
//					sMsg = strcat(sExc, sWhat);
//					strcpy(sExc, "out_of_range: ");

					cout << "out_of_range: " << oor.what();
					throw nb::std::BaseException("Matrix::operator[]: ", "out_of_range: First index out of range");
				}
				catch (...)
				{

				}
			}

			vector <double>& Matrix::operator[](int i){
				try
				{
					m_bIsChanged = true;
					//vector <double> aResult = m_aData.at(i);
					return m_aData[i];//aResult;
				}
				catch (out_of_range &oor)
				{
					const char *sWhat = oor.what();
					char *sMsg = new char[strlen(oor.what()) + 20];
					char *sExc = new char[strlen(oor.what()) + 20];
//					sMsg = strcat(sExc, sWhat);
//					strcpy(sExc, "out_of_range: ");

					cout << "out_of_range: " << oor.what();
					throw nb::std::BaseException("Matrix::operator[]: ", "out_of_range: First index out of range");
				}
				catch (...)
				{

				}

			}
			
			vector<vector<double>> getData() const { return m_aData; }

			pair<int, int> getSize() const { return make_pair(m_aData.size(), m_aData[0].size()); }

			double getItem(int i, int j) const { return m_aData[i][j]; }

			//setters


			//overload operators
			Matrix Matrix::operator+(Matrix &a)
			{
				return Matrix::makeBinaryAction(*this, a, SumTwoObjects);
			}

			Matrix Matrix::operator-(Matrix &a)
			{
				return makeBinaryAction(*this, a, Matrix::DiffTwoObjects);
			}

			Matrix Matrix::operator*(Matrix &a)
			{
				return MakeMultyplication(*this, a);
			}

			bool Matrix::operator ==(const Matrix &_a) const
			{
				Matrix t = Matrix(*this);
				Matrix a = Matrix(_a);

				return Matrix::isEqual(t, a);
			}

			bool Matrix::operator != (const Matrix &_a) const
			{
				return !Matrix::isEqual(_a, *this);
			}

			//complex operations

			Matrix getInverseMatrix()
			{

			}

			Matrix getTransposeMatrix()
			{
				if (!m_bIsChanged && m_aTData.size() > 0)
				{
					return Matrix(m_aTData);
				}
				else
				{
					ClearMatrix(m_aTData);
					m_aTData = TransposeMatrix(m_aData);
					return Matrix(m_aTData);
				}
			}

			double determinant()
			{

			}

			void print()
			{
				for (int i = 0; i < m_aData.size(); i++)
				{
					for (int j = 0; j < m_aData[i].size(); j++)
					{
						cout << m_aData[i][j] << " ";
					}
					cout << endl;
				}
			}
		};

	}
};