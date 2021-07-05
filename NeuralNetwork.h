#ifndef NN_NEURAL_NETWORK_H

#define NN_NEURAL_NETWORK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Node.h"
#include "Edge.h"
#include "Matrix.h"
#include "XorShift128.h"
using namespace std;
using namespace NNet;
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

		// �������֐�
		double Sigmoid(double a);
		Matrix Sigmoid(Matrix m);
		double ReLU(double a);
		Matrix ReLU(Matrix m);

		// ���������������֐�
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

		void CheckError(vector<double> va, vector<Node> vn);
		void ReducingError(Matrix in);
		// �� 0 �w�ւ̓���
		void InputToNode(vector<double> iv);
		// ���`��
		void Propagation(Matrix in);
		// �t�`�� (�f���^�̎Z�o)
		void BackPropagation(Matrix ans);

		// �ǂ̃m�[�h����Ԓl���傫����
		int MostNode(int index);

		// �f�[�^�̕ۑ��A�ǂݍ���
		void SaveState(string fileName);
		void LoadState(string faleName);

		double GetOutPut(int i);

		void SetEta(double eta);
		void SetActivationList(vector<string> acv);

		// �f�o�b�O�p
		void DebugDeltaPrint();
		void DebugErrorPrint(Matrix ans);
		void DebugNodePrint();
		void DebugNodePrint(int layer);
		void DebugWeightPrint(int layer);
	};
	
#include "NeuralNetwork.inl"
}

#endif // !NN_NEURAL_NETWORK_H
