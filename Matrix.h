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

		// 転置
		Matrix Transpose();
		
		// アダマール積 (要素ごとの積)
		Matrix Hadamard(const Matrix& om);

		// 指定した列をすべて足す
		double ColSum(int col);

		// 要素全部を指定した数で埋める
		void Fill(double a);
		// col 列の値を全て a にする
		void ColFill(int col, double a);

		int GetRowValue();
		int GetColValue();

		// 演算子オーバーロード
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