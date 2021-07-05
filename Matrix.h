#ifndef MM_MATRIX_H

#define MM_MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

namespace MyMath {
	class Matrix {
	private:
		vector<vector<double>> _data;
		int _row;
		int _col;
	public:
		Matrix();
		Matrix(int row, int col);
		Matrix(int row, int col, double a);

		void DefSize(int row, int col);

		// �]�u
		Matrix Transpose();
		
		// �A�_�}�[���� (�v�f���Ƃ̐�)
		Matrix Hadamard(const Matrix& om);

		// �w�肵��������ׂđ���
		double ColSum(int col);

		// �v�f�S�����w�肵�����Ŗ��߂�
		void Fill(double a);
		// col ��̒l��S�� a �ɂ���
		void ColFill(int col, double a);

		int GetRowValue();
		int GetColValue();

		// ���Z�q�I�[�o�[���[�h
		Matrix operator-() const;
		Matrix& operator+=(const Matrix& om);
		Matrix& operator-=(const Matrix& om);
		Matrix& operator*=(const Matrix& om);
		Matrix& operator*=(const double a);

		const vector<double>& operator[](size_t i) const&;
		vector<double>& operator[](size_t i)&;
		vector<double> operator[](size_t i) const&&;
	};

	Matrix operator+(const Matrix& am, const Matrix& bm);
	Matrix operator-(const Matrix& am, const Matrix& bm);
	Matrix operator*(const Matrix& am, const Matrix& bm);
	Matrix operator*(const Matrix& m, const double a);
	Matrix operator*(const double a, const Matrix& m);
}

#endif // !MM_MATRIX_H