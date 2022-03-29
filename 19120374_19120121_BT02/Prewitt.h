#pragma once
#include "Utils.h"

enum PREWITT_FILTER {
	PREWITT_FILTER_3x3 = 0,
	PREWITT_FILTER_5x5 = 1
};

extern vector<vector<char>> prewitt_filter3x3_x;
extern vector<vector<char>> prewitt_filter3x3_y;
extern vector<vector<char>> prewitt_filter5x5_x;
extern vector<vector<char>> prewitt_filter5x5_y;

int detectByPrewitt(Mat src, Mat& des, int filter, int padding = -1, int stride = 1);
Mat convPrewitt(Mat& image, vector<vector<char>>& x_mask, vector<vector<char>>& y_mask, int padding, int stride);
