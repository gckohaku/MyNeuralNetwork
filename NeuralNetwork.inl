template<typename ...Values>
inline NeuralNetwork::NeuralNetwork(int dataValue, int layer, Values ...values)
{
	cout << "layer : " << layer << "\n\n";

	vector<int> vs = { values ... };

	if (vs.size() != layer + 1) {
		cerr << "not match layer value\n";
		return;
	}

	auto r = XorShifts::XorShift128();
	r.SetSeed(time(nullptr));

	_z.resize(layer);
	_nodes.resize(layer);
	_biases.resize(layer);
	_weights.resize(layer);
	_deltas.resize(layer);

	_r.SetSeed();

	// ‘w‚Ì”‚¾‚¯‰ñ‚·
	for (int i = 0; i < layer; i++) {
		cout << "‘æ" << i + 1 << "‘w" << '\n';

		_z[i].DefSize(dataValue, vs[i + 1]);
		for (int j = 0; j < _z[i].GetRowValue(); j++) {
			for (int k = 0; k < _z[i].GetColValue(); k++) {
				_z[i][j][k] = r.RandFloat(0.0, 1.0);
			}
		}

		_nodes[i].DefSize(dataValue, vs[i + 1]);
		for (int j = 0; j < _nodes[i].GetRowValue(); j++) {
			for (int k = 0; k < _nodes[i].GetColValue(); k++) {
				_nodes[i][j][k] = r.RandFloat(0.0, 1.0);
			}
		}

		_weights[i].DefSize(vs[i + 1], vs[i]);
		for (int j = 0; j < _weights[i].GetRowValue(); j++) {
			for (int k = 0; k < _weights[i].GetColValue(); k++) {
				_weights[i][j][k] = r.RandFloat(0.0, 1.0);
			}
		}

		_biases[i].DefSize(dataValue, vs[i + 1]);
		for (int j = 0; j < _biases[i].GetRowValue(); j++) {
			for (int k = 0; k < _biases[i].GetColValue(); k++) {
				_biases[i][j][k] = r.RandFloat(0.0, 1.0);
			}
		}

		_deltas[i].DefSize(dataValue, vs[i + 1]);
	}
}