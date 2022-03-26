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

int applyKernel(Mat& image, vector<vector<char>>& kernel, int startX, int startY) {
	int sum = 0;

	for (int y = 0; y < kernel.size(); ++y) 
	{
		for (int x = 0; x < kernel[0].size(); ++x)
		{
			sum += image.at<uchar>(y + startY, x + startX) * kernel[y][x];
		}
	}
	return sum;
}

Mat conv(Mat& image, vector<vector<char>>& kernel, int padding, int stride) {
	Mat result;
	Mat pad_image;
	// "valid" padding
	if (padding == 0)
	{
		pad_image = image;
	}
	// "same" padding
	else if (padding == -1)
	{
		int padding_horiz = ceil((stride * (image.cols - 1) - image.cols + kernel[0].size()) / 2);
		int padding_vert = ceil((stride * (image.rows - 1) - image.rows + kernel.size()) / 2);
		copyMakeBorder(image, pad_image, padding_vert, padding_vert, padding_horiz, padding_horiz, BORDER_CONSTANT, (0, 0, 0));
	}
	else 
	{
		copyMakeBorder(image, pad_image, padding, padding, padding, padding, BORDER_CONSTANT, (0, 0, 0));
	}

	result = Mat::zeros((pad_image.rows - kernel.size()) / stride + 1, (pad_image.rows - kernel[0].size()) / stride + 1, CV_8UC1);
	for (int y = 0; y < ceil((pad_image.rows - kernel.size()) / stride); ++y)
	{
		for (int x = 0; x < ceil(pad_image.cols - kernel[0].size() / stride); ++x)
		{
			result.at<uchar>(y, x) = saturate_cast<uchar>(applyKernel(pad_image, kernel, x * stride, y * stride));
		}
	}

	return result;
}