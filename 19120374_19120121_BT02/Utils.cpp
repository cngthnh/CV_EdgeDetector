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

Mat calcGrad(Mat xGrad, Mat yGrad)
{
	Mat result = Mat::zeros(xGrad.size().height, xGrad.size().width, CV_8UC1);
	if (xGrad.size() != yGrad.size())
	{
		return result;
	}
	for (int y = 0; y < xGrad.rows; ++y)
	{
		for (int x = 0; x < xGrad.cols; ++x)
			result.at<uchar>(y, x) = sqrt(pow(xGrad.at<uchar>(y, x), 2) + pow(yGrad.at<uchar>(y, x), 2));
	}
	return result;
}

vector<vector<uchar>> calcDirection(Mat xGrad, Mat yGrad)
{
	vector<vector<uchar>> result;
	if (xGrad.size() != yGrad.size())
	{
		return result;
	}
	for (int y = 0; y < xGrad.rows; ++y)
	{
		vector<uchar> row;
		for (int x = 0; x < xGrad.cols; ++x)
		{
			uchar group;
			float degree = atan(((double)yGrad.at<uchar>(y, x)) / xGrad.at<uchar>(y, x)) * (180.0 / M_PI);
			if ((degree >= -22.5 && degree <= 22.5) || (degree >= 157.5) || (degree <= -157.5))
			{
				group = 0;
			}
			else if ((degree >= -112.5 && degree <= -67.5) || (degree >= 67.5 && degree <= 112.5)) {
				group = 90;
			}
			else if ((degree > 22.5 && degree < 67.5) || (degree > -157.5 && degree < -112.5)) {
				group = 45;
			}
			else if ((degree > 112.5 && degree < 157.5) || (degree > -67.5 && degree < -22.5)) {
				group = 135;
			}
			row.push_back(group);
		}
		result.push_back(row);
	}
	return result;
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
		}
	}

	return filter;
}