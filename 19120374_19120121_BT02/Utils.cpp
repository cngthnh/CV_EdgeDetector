#include "Utils.h"

// Hàm lấy các option từ câu lệnh
char* getCmdOption(char** argv, int argc, const char* option)
{
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], option) == 0) {
			if (++i < argc) {
				return argv[i];
			}
			else return NULL;
		}
	}
	return NULL;
}

// Hàm kiểm tra option có tồn tại trong lời gọi chương trình hay không
bool cmdOptionExists(char** argv, int argc, const char* option)
{
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], option) == 0) return true;
	}
	return false;
}

vector<vector<float>> generateGaussianFilter(int size, float sigma)
{
	vector<vector<float>> filter;

	double r, s = 2.0 * sigma * sigma;
	double sum = 0.0;
	int absSize = floor(size / 2);

	for (int y = -absSize; y <= absSize; y++) {
		vector<float> row;
		for (int x = -absSize; x <= absSize; x++) {
			r = sqrt(x * x + y * y);
			double entry = (exp(-(r * r) / s)) / (M_PI * s);
			row.push_back(entry);
			sum += entry;
		}
		filter.push_back(row);
	}

	// normalize
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			filter[i][j] /= sum;
			cout << filter[i][j] << ' ';
		}
		cout << '\n';
	}

	return filter;
}