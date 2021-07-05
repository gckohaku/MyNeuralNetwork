#include "NeuralNetwork.h"

double NNet::NeuralNetwork::Sigmoid(double a)
{
	return 1.0 / (1.0 - exp(-5 * a));
}

Matrix NNet::NeuralNetwork::Sigmoid(Matrix m)
{
	Matrix ret(m.GetRowValue(), m.GetColValue());

	for (int i = 0; i < m.GetRowValue(); i++) {
		for (int j = 0; j < m.GetColValue(); j++) {
			ret[i][j] = Sigmoid(m[i][j]);
		}
	}

	return ret;
}

double NNet::NeuralNetwork::ReLU(double a)
{
	return max(0.0, a);
}

Matrix NNet::NeuralNetwork::ReLU(Matrix m)
{
	Matrix ret(m.GetRowValue(), m.GetColValue());

	for (int i = 0; i < m.GetRowValue(); i++) {
		for (int j = 0; j < m.GetColValue(); j++) {
			ret[i][j] = ReLU(m[i][j]);
		}
	}

	return ret;
}

double NNet::NeuralNetwork::dSigmoid(double a)
{
	return (1.0 - Sigmoid(a)) * Sigmoid(a);
}

Matrix NNet::NeuralNetwork::dSigmoid(Matrix m)
{
	Matrix ret(m.GetRowValue(), m.GetColValue());

	for (int i = 0; i < m.GetRowValue(); i++) {
		for (int j = 0; j < m.GetColValue(); j++) {
			ret[i][j] = dSigmoid(m[i][j]);
		}
	}

	return ret;
}

double NNet::NeuralNetwork::dReLU(double a)
{
	if (a > 0.0) {
		return 1.0;
	}
	if (a < 0.0) {
		return 0.0;
	}

	return 0.5;
}

Matrix NNet::NeuralNetwork::dReLU(Matrix m)
{
	Matrix ret(m.GetRowValue(), m.GetColValue());

	for (int i = 0; i < m.GetRowValue(); i++) {
		for (int j = 0; j < m.GetColValue(); j++) {
			ret[i][j] = dReLU(m[i][j]);
		}
	}

	return ret;
}

NNet::NeuralNetwork::NeuralNetwork()
{

}

Matrix NNet::NeuralNetwork::Activation(string funcName, Matrix m)
{
	if (funcName == "sigmoid") {
		return Sigmoid(m);
	}
	if (funcName == "relu") {
		return ReLU(m);
	}

	cerr << "���̂悤�Ȋ������֐��͂���܂���\n" << endl;
	return m;
}

Matrix NNet::NeuralNetwork::dActivation(string funcName, Matrix m)
{
	if (funcName == "sigmoid") {
		return dSigmoid(m);
	}
	if (funcName == "relu") {
		return dReLU(m);
	}

	cerr << "���̂悤�Ȋ������֐��͂���܂���\n" << endl;
	return m;
}

void NNet::NeuralNetwork::CheckError(vector<double> va, vector<Node> vn)
{
	
}

void NNet::NeuralNetwork::InputToNode(vector<double> iv)
{
	
}

void NNet::NeuralNetwork::Propagation(Matrix in)
{
	for (int i = 0; i < _nodes.size(); i++) {
		if (i == 0) {
			_z[i] = in * _weights[i].Transpose() + _biases[i];
		}
		else {
			_z[i] = _nodes[i - 1] * _weights[i].Transpose() + _biases[i];
		}

		_nodes[i] = Activation(_activationList[i], _z[i]);
	}
}

void NNet::NeuralNetwork::BackPropagation(Matrix ans)
{
	int tale_index = _nodes.size() - 1;
	string tale_func = _activationList[tale_index];
	_deltas[tale_index] = (Activation(tale_func, _z[tale_index]) - ans).Hadamard(dActivation(tale_func, _z[tale_index]));

	for (int i = tale_index - 1; i >= 0; i--) {
		_deltas[i] = dActivation(_activationList[i], _z[i]).Hadamard(_deltas[i + 1] * _weights[i + 1]);
	}
}

void NNet::NeuralNetwork::ReducingError(Matrix in)
{
	for (int i = _nodes.size() - 1; i > 0; i--) {
		_weights[i] -= _eta * (_deltas[i].Transpose() * _nodes[i - 1]);
		for (int j = 0; j < _biases[i].GetColValue(); j++) {
			_biases[i].ColFill(j, _biases[i][0][j] - _eta * _deltas[i].ColSum(j));
		}
	}

	_weights[0] -= _eta * (_deltas[0].Transpose() * in);
	for (int j = 0; j < _biases[0].GetColValue(); j++) {
		_biases[0].ColFill(j, _biases[0][0][j] - _eta * _deltas[0].ColSum(j));
	}
}

int NNet::NeuralNetwork::MostNode(int index)
{
	int ret = 0;
	vector<double> obj = _nodes.back()[index];

	for (int i = 1; i < obj.size(); i++) {
		if (obj[ret] < obj[i]) {
			ret = i;
		}
	}

	return ret;
}

void NNet::NeuralNetwork::SaveState(string fileName)
{
	ofstream ofs(fileName);

	ofs << _nodes.size() << "\n";
	ofs << _weights[0].GetRowValue() << "\n";

	for (int i = 0; i < _nodes.size(); i++) {
		ofs << _weights[0].GetColValue() << "\n";
		for (int j = 0; j < _weights[i].GetRowValue(); j++) {
			ofs << _biases[i][0][j] << endl;
			for (int k = 0; k < _weights[0].GetColValue(); k++) {
				ofs << _weights[i][j][k] << "\n";
			}
		}
	}
}

void NNet::NeuralNetwork::LoadState(string fileName)
{
	// TODO: �s��ł̎����ɑΉ��������̂ɂ���

	int layer, before_nodes, this_nodes;
	double bias, weight;

	cout << "�t�@�C�������Ԃ�ǂݎ���\n";

	ifstream ifs(fileName);

	ifs >> layer;

	ifs >> before_nodes;

	// �� 0 �w�̃T�C�Y��ݒ�
	cout << "�m�[�h����" << before_nodes << "�ɐݒ�\n";

	// �w�̐�������
	for (int i = 0; i < layer; i++) {
		cout << "��" << i + 1 << "�w" << '\n';

		ifs >> this_nodes;

		// �� i + 1 �w�̐������m�[�h�𐶐�
		cout << "�m�[�h����" << this_nodes << "�ɐݒ�\n";

		// �� i + 1 �w�֓`�������G�b�W�̐���
		cout << "�G�b�W����" << this_nodes << "�ɐݒ�\n";

		// ���ꂼ��̃m�[�h��� i �w�̃m�[�h�̐������₷
		for (int j = 0; j < this_nodes; j++) {
			ifs >> bias;

			cout << "�G�b�W" << j << "��" << before_nodes << "�ɑ��₷\n";

			for (int k = 0; k < before_nodes; k++) {
				ifs >> weight;
			}
		}
		cout << '\n';
		before_nodes = this_nodes;
	}

	cout << "�ǂݎ�肪�I�������\n";
}

double NNet::NeuralNetwork::GetOutPut(int i)
{
	return _nodes.back()[i][0];
}

void NNet::NeuralNetwork::SetEta(double eta)
{
	_eta = eta;
}

void NNet::NeuralNetwork::SetActivationList(vector<string> acv)
{
	_activationList = acv;
}

void NNet::NeuralNetwork::DebugDeltaPrint()
{
	int tale_index = _nodes.size() - 1;

	for (int i = 0; i < _deltas[tale_index].GetColValue(); i++) {
		cout << _deltas[tale_index].ColSum(i) << " ";
	}
	cout << endl;
}

void NNet::NeuralNetwork::DebugErrorPrint(Matrix ans)
{
	int tale_index = _nodes.size() - 1;
	double er;

	for (int i = 0; i < _nodes[tale_index].GetColValue(); i++) {
		er = 0.0;
		Matrix m = _nodes[tale_index];
		for (int j = 0; j < m.GetRowValue(); j++) {
			er += pow(m[j][i] - ans[j][i], 2) * 0.5;
		}
		cout << er * 0.5 << " ";
	}
	cout << endl;
}

void NNet::NeuralNetwork::DebugNodePrint()
{
	
}

void NNet::NeuralNetwork::DebugNodePrint(int layer)
{
	
}

void NNet::NeuralNetwork::DebugWeightPrint(int layer)
{
	
}
