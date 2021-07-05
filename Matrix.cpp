#include "Matrix.h"

namespace MyMath {
	Matrix::Matrix() {

	}

	Matrix::Matrix(int row, int col)
	{
		DefSize(row, col);
	}

	Matrix::Matrix(int row, int col, double a)
	{
		DefSize(row, col);
		Fill(a);
	}

	void Matrix::DefSize(int row, int col)
	{
		_row = row;
		_col = col;

		_data.resize(row);

		for (int i = 0; i < row; i++) {
			_data[i].resize(col);
		}
	}

	Matrix Matrix::Transpose()
	{
		Matrix ret(_col, _row);

		for (int i = 0; i < _col; i++) {
			for (int j = 0; j < _row; j++) {
				ret[i][j] = (*this)[j][i];
			}
		}

		return ret;
	}

	Matrix Matrix::Hadamard(const Matrix& om)
	{
		if (this->_row != om._row || this->_col != om._col) {
			cerr << "この行列の組み合わせは計算できません" << endl;
			cout << "this: " << this->_row << ", " << this->_col << endl;
			cout << "om  : " << om._row << ", " << om._col << endl;
			return *this;
		}

		Matrix ret(_row, _col);

		for (int i = 0; i < this->_row; i++) {
			for (int j = 0; j < this->_col; j++) {
				ret[i][j] = (*this)[i][j] * om[i][j];
			}
		}

		return ret;
	}

	double Matrix::ColSum(int col)
	{
		double ret = 0.0;

		for (int i = 0; i < this->_row; i++) {
			ret += (*this)[i][col];
		}

		return ret;
	}

	void Matrix::Fill(double a)
	{
		for (int i = 0; i < this->_row; i++) {
			for (int j = 0; j < this->_col; j++) {
				(*this)[i][j] = a;
			}
		}
	}

	void Matrix::ColFill(int col, double a)
	{
		for (int i = 0; i < this->_row; i++) {
			(*this)[i][col] = a;
		}
	}

	int Matrix::GetRowValue()
	{
		return _row;
	}

	int Matrix::GetColValue()
	{
		return _col;
	}

	Matrix Matrix::operator-() const
	{
		Matrix ret(this->_row, this->_col);

		for (int i = 0; i < this->_row; i++) {
			for (int j = 0; j < this->_col; j++) {
				ret[i][j] = -(*this)[i][j];
			}
		}

		return ret;
	}

	Matrix& Matrix::operator+=(const Matrix& om)
	{
		if (this->_row != om._row || this->_col != om._col) {
			cerr << "この行列の組み合わせは足せません" << endl;
			cout << "this: " << this->_row << ", " << this->_col << endl;
			cout << "om  : " << om._row << ", " << om._col << endl;
			return *this;
		}

		for (int i = 0; i < this->_row; i++) {
			for (int j = 0; j < this->_col; j++) {
				(*this)[i][j] += om[i][j];
			}
		}

		return *this;
	}

	Matrix& Matrix::operator-=(const Matrix& om)
	{
		if (this->_row != om._row || this->_col != om._col) {
			cerr << "この行列の組み合わせは引けません" << endl;
			cout << "this: " << this->_row << ", " << this->_col << endl;
			cout << "om  : " << om._row << ", " << om._col << endl;
			return *this;
		}

		for (int i = 0; i < this->_row; i++) {
			for (int j = 0; j < this->_col; j++) {
				(*this)[i][j] -= om[i][j];
			}
		}

		return *this;
	}

	Matrix& MyMath::Matrix::operator*=(const Matrix& om)
	{
		if (this->_col != om._row) {
			cerr << "この行列の組み合わせはかけられません" << endl;
			cout << "this: " << this->_row << ", " << this->_col << endl;
			cout << "om  : " << om._row << ", " << om._col << endl;
			return *this;
		}

		Matrix ret(this->_row, om._col);

		for (int i = 0; i < this->_row; i++) {
			for (int j = 0; j < om._col; j++) {
				for (int k = 0; k < this->_col; k++) {
					ret[i][j] = (*this)[i][k] * om[k][j];
				}
			}
		}

		this->DefSize(this->_row, om._col);

		this->_data = ret._data;

		return *this;
	}

	Matrix& Matrix::operator*=(const double a)
	{
		for (int i = 0; i < this->_row; i++) {
			for (int j = 0; j < this->_col; j++) {
				(*this)[i][j] *= a;
			}
		}

		return *this;
	}

	const vector<double>& Matrix::operator[](size_t i) const& {
		return this->_data[i];
	}

	vector<double>& Matrix::operator[](size_t i)&
	{
		return this->_data[i];
	}

	Matrix operator+(const Matrix& am, const Matrix& bm)
	{
		return Matrix(am) += bm;
	}

	Matrix operator-(const Matrix& am, const Matrix& bm)
	{
		return Matrix(am) -= bm;
	}

	Matrix operator*(const Matrix& am, const Matrix& bm)
	{
		return Matrix(am) *= bm;
	}

	Matrix operator*(const Matrix& m, const double a)
	{
		return Matrix(m) *= a;
	}

	Matrix operator*(const double a, const Matrix& m)
	{
		return Matrix(m) *= a;
	}

}