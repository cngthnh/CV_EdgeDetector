#pragma once
#include "Utils.h"

enum LAPLACIAN_FILTER {
	FILTER_3x3 = 0,
	FILTER_5x5 = 1
};

int detectByLaplace(Mat src, Mat& des, int filter, int padding = -1, int stride = 1);
