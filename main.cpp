#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <algorithm>
#include <string>
#include <regex>
#include <experimental/filesystem>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include "NeuralNetwork.h"
#include "XorShift128.h"
#include "Matrix.h"
using namespace std;
using namespace NNet;
namespace fs = std::experimental::filesystem;

#define NN_SIMPLE

#if defined NN_NUM_TEST

int main() {
	string path = "C:\\VSproject\\NeuralNetwork\\numTestData\\";
	string state_file_name = "C:\\VSproject\\NeuralNetwork\\stateData\\numStateData.osd";

	int layer_value = 2, input_value = 4096;
	int mini_batch_test_case = 5;
	int epoch = 5;

	regex re(R"(_\d_)");
	smatch match;

	auto r = XorShifts::XorShift128();
	r.SetSeed(time(nullptr));

	NeuralNetwork nn(3, input_value, 64, 32, 10);
	/*NeuralNetwork nn;

	nn.LoadState(state_file_name);
	nn.SetEta(0.1);*/

	vector<string> test_file_name;

	for (const auto entry : fs::directory_iterator(path)) {
		test_file_name.push_back(entry.path().filename().string());
	}

	for (int etimes = 0; etimes < epoch; etimes++) {
		for (int times = 0; times < mini_batch_test_case; times++) {

			string filename = test_file_name[r.RandInt(0, 19)];

			cv::Mat img = cv::imread(path + filename, 0);

			int real, res;

			// 正解の読み取り
			if (regex_search(filename.cbegin(), filename.cend(), match, re)) {
				real = match.str()[1] - '0';
			}

			vector<double> ans(10);

			for (int i = 0; i < 10; i++) {
				ans[i] = (i == real ? 1 : 0);
			}

			vector<double> in(input_value);

			for (int i = 0; i < input_value; i++) {
				in[i] = abs(img.at<byte>(i) / 255.0 - 1.0);
			}

			nn.InputToNode(in);

			nn.Propagation();

			res = nn.MostNode();

			// コンソール画面への結果の出力
			cout << res << " (" << real << ") -> " << ((res == real ? 'o' : 'x')) << '\n';

			// 誤差を計算
			nn.CheckError(ans);
		}
		cout << "誤差を減らしているよ\n";
		nn.ReducingError();
	}

	nn.SaveState(state_file_name);

	return 0;
}

#endif

#if defined NN_SIMPLE

int main() {
	int layer_value = 3, input_value = 2;
	int mini_batch_test_case = 100;
	int epoch = 1000;

	string state_file_name = "C:\\VSproject\\NeuralNetwork\\stateData\\simple.osd";

	auto r = XorShifts::XorShift128();
	r.SetSeed(time(nullptr));

	NeuralNetwork nn(mini_batch_test_case, layer_value, input_value, 2, 2, 1);
	//NeuralNetwork nn;
	//nn.LoadState(state_file_name);

	nn.SetEta(0.01);
	nn.SetActivationList({ "sigmoid", "sigmoid", "sigmoid" });

	int correct;

	for (int etimes = 0; etimes <= epoch; etimes++) {
		int correct = 0;

		int real, res;

		MyMath::Matrix in(mini_batch_test_case, 2);
		MyMath::Matrix ans(mini_batch_test_case, 1);

		for (int i = 0; i < mini_batch_test_case; i++) {
			in[i] = { (double)r.RandInt(0, 1), (double)r.RandInt(0, 1) };
			ans[i][0] = ((int)in[i][0] ^ (int)in[i][1]) ? 1.0 : 0.0;
		}

		nn.Propagation(in);
		nn.BackPropagation(ans);
		nn.ReducingError(in);

		// コンソール画面への結果の出力
		// cout << res << " (" << real << ") -> " << ((res == real ? 'o' : 'x')) << '\n';

		// 結果
		/*for (int i = 0; i < ans.GetRowValue(); i++) {
			if (ans[i][0] == round(nn.GetOutPut(i))) {
				correct++;
			}
		}*/

		if (etimes % 100 == 0) {
			cout << "エポック " << etimes << " の誤差 = ";
			nn.DebugErrorPrint(ans);
		}

		// エポックごとの結果の表示
		/*cout << "エポック " << etimes << " の結果 : " << (100 * correct / mini_batch_test_case) << "% (" << correct << "/" << mini_batch_test_case << ")\n";*/
	}

	nn.SaveState(state_file_name);

	return 0;
}

#endif

#if defined MATRIX_TEST

int main() {
	Matrix a(2, 2), b(2, 2);

	a[0] = { 2, 4 };
	a[1] = { 6, 4 };

	b[0] = { 3, 4 };
	b[1] = { 8, 7 };

	Matrix res(2, 2);

	res = a * 5;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%4.0lf ", res[i][j]);
		}
		cout << endl;
	}

	cout << endl;

	return 0;
}

#endif