#pragma once
#include "Utils.h"


enum SOBEL_FILTER {
	SOBEL_FILTER_3x3 = 0,
	SOBEL_FILTER_5x5 = 1
};

extern vector<vector<char>> sobel_filter3x3_y;
extern vector<vector<char>> sobel_filter3x3_x;
extern vector<vector<char>> sobel_filter5x5_y;
extern vector<vector<char>> sobel_filter5x5_x;

int detectBySobel(Mat src, Mat& des, int filter, int padding = -1, int stride = 1);
Mat convSobel(Mat& image, vector<vector<char>>& x_mask, vector<vector<char>>& y_mask, int padding, int stride);
