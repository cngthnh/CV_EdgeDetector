#pragma once
#include "Utils.h"
#include "Sobel.h"
#include "Prewitt.h"

enum CANNY_OPERATOR {
	SOBEL_OPERATOR = 0,
	PREWITT_OPERATOR = 1
};

int detectByCanny(Mat src, Mat& des, int lowerThreshold, int upperThreshold, int opr, int padding, int stride,
	float gaussianBlurSigma = 1.4, int gaussianKernelSize = 5);
void nonMaxSuppression(Mat& grad, vector<vector<uchar>> directions);
void hysteresis(Mat& grad, int lowerThreshold, int upperThreshold);
void enhance(Mat& grad);