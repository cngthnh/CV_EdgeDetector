#pragma once
#include "Utils.h"


enum SOBEL_FILTER {
	SOBEL_FILTER_3x3 = 0,
	SOBEL_FILTER_5x5 = 1
};

int detectBySobel(Mat src, Mat& des, int filter, int padding = -1, int stride = 1);
Mat convSobel(Mat& image, vector<vector<char>>& x_mask, vector<vector<char>>& y_mask, int padding, int stride);
