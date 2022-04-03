#pragma once
#include "Utils.h"
#include "Sobel.h"
#include "Prewitt.h"

enum CANNY_OPERATOR {
	SOBEL_OPERATOR = 0,
	PREWITT_OPERATOR = 1
};

int detectByCanny(Mat src, Mat& des, int opr, int padding, int stride, int lowerThreshold = 20, int upperThreshold = 100,
	float gaussianBlurSigma = 1.4, int gaussianKernelSize = 5);
void nonMaxSuppression(Mat& grad, vector<vector<uchar>> directions);
void hysteresis(Mat& grad, int lowerThreshold, int upperThreshold);
void enhance(Mat& grad);