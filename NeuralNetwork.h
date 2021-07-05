#ifndef NN_NEURAL_NETWORK_H

#define NN_NEURAL_NETWORK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Matrix.h"
#include "XorShift128.h"
using namespace std;
using namespace MyMath;

namespace NNet {
	class NeuralNetwork {
	private:
		vector<Matrix> _z;
		vector<Matrix> _biases;
		vector<Matrix> _weights;
		vector<Matrix> _nodes;

		vector<Matrix> _deltas;

		vector<string> _activationList;

		XorShifts::XorShift128 _r;

		double _eta = 0.001;

		// 活性化関数
		double Sigmoid(double a);
		Matrix Sigmoid(Matrix m);
		double ReLU(double a);
		Matrix ReLU(Matrix m);

		// 微分した活性化関数
		double dSigmoid(double a);
		Matrix dSigmoid(Matrix m);
		double dReLU(double a);
		Matrix dReLU(Matrix m);

	public:
		NeuralNetwork();
		template<typename ...Values>
		NeuralNetwork(int dataValue, int layer, Values ... args);

		Matrix Activation(string funcName, Matrix m);
		Matrix dActivation(string funcName, Matrix m);

		void ReducingError(Matrix in);
		// 第 0 層への入力
		void InputToNode(vector<double> iv);
		// 順伝搬
		void Propagation(Matrix in);
		// 逆伝搬 (デルタの算出)
		void BackPropagation(Matrix ans);

		// どのノードが一番値が大きいか
		int MostNode(int index);

		// データの保存、読み込み
		void SaveState(string fileName);
		void LoadState(string faleName);

		double GetOutPut(int i);

		void SetEta(double eta);
		void SetActivationList(vector<string> acv);

		// デバッグ用
		void DebugDeltaPrint();
		void DebugErrorPrint(Matrix ans);
		void DebugNodePrint();
		void DebugNodePrint(int layer);
		void DebugWeightPrint(int layer);
	};
	
#include "NeuralNetwork.inl"
}

#endif // !NN_NEURAL_NETWORK_H
