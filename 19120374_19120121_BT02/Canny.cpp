#include "Canny.h"
#include "opencv2/highgui/highgui.hpp"

int detectByCanny(Mat src, Mat& des, int opr, int padding, int stride, int lowerThreshold, int upperThreshold,
	float gaussianBlurSigma, int gaussianKernelSize)
{
	// Apply gaussian blur
	vector<vector<float>> gFilter = generateGaussianFilter(gaussianKernelSize, gaussianBlurSigma);
	src = conv(src, gFilter, -1, 1);

	Mat xGrad, yGrad, grad;
	vector<vector<uchar>> directions;
	switch (opr) {
	case (CANNY_OPERATOR::SOBEL_OPERATOR):
		xGrad = conv(src, sobel_filter3x3_x, padding, stride);
		yGrad = conv(src, sobel_filter3x3_y, padding, stride);
		break;
	case (CANNY_OPERATOR::PREWITT_OPERATOR):
		xGrad = conv(src, prewitt_filter3x3_x, padding, stride);
		yGrad = conv(src, prewitt_filter3x3_y, padding, stride);
		break;
	}

	grad = xGrad + yGrad;
	directions = calcDirection(xGrad, yGrad);
	nonMaxSuppression(grad, directions);
	hysteresis(grad, lowerThreshold, upperThreshold);
	enhance(grad);
	des = grad;
	return 1;
}

void enhance(Mat& grad)
{
	for (int y = 0; y < grad.size().height; ++y)
		for (int x = 0; x < grad.size().width; ++x)
			if (grad.at<uchar>(y, x) != 0)
				grad.at<uchar>(y, x) = 255;
}

void scanNeighbors(Mat& grad, int x, int y, int lowerThreshold, vector<vector<bool>>& scanCheck)
{
	if (grad.at<uchar>(y, x) < lowerThreshold || scanCheck[y][x])
		return;

	scanCheck[y][x] = true;

	bool lowerX = x - 1 >= 0;
	bool upperX = x + 1 < grad.size().width;
	bool lowerY = y - 1 >= 0;
	bool upperY = y + 1 < grad.size().height;

	if (lowerX && lowerY)
		if (grad.at<uchar>(y - 1, x - 1) < lowerThreshold)
			grad.at<uchar>(y - 1, x - 1) = 0;
		else 
			scanNeighbors(grad, x - 1, y - 1, lowerThreshold, scanCheck);

	if (lowerX && upperY)
		if (grad.at<uchar>(y + 1, x - 1) < lowerThreshold)
			grad.at<uchar>(y + 1, x - 1) = 0;
		else
			scanNeighbors(grad, x - 1, y + 1, lowerThreshold, scanCheck);

	if (upperX && lowerY)
		if (grad.at<uchar>(y - 1, x + 1) < lowerThreshold)
			grad.at<uchar>(y - 1, x + 1) = 0;
		else
			scanNeighbors(grad, x + 1, y - 1, lowerThreshold, scanCheck);

	if (upperX && upperY)
		if (grad.at<uchar>(y + 1, x + 1) < lowerThreshold)
			grad.at<uchar>(y + 1, x + 1) = 0;
		else
			scanNeighbors(grad, x + 1, y + 1, lowerThreshold, scanCheck);

	if (lowerX)
		if (grad.at<uchar>(y, x - 1) < lowerThreshold)
			grad.at<uchar>(y, x - 1) = 0;
		else
			scanNeighbors(grad, x - 1, y, lowerThreshold, scanCheck);

	if (upperX)
		if (grad.at<uchar>(y, x + 1) < lowerThreshold)
			grad.at<uchar>(y, x + 1) = 0;
		else
			scanNeighbors(grad, x + 1, y, lowerThreshold, scanCheck);

	if (upperY)
		if (grad.at<uchar>(y + 1, x) < lowerThreshold)
			grad.at<uchar>(y + 1, x) = 0;
		else
			scanNeighbors(grad, x, y + 1, lowerThreshold, scanCheck);

	if (lowerY)
		if (grad.at<uchar>(y - 1, x) < lowerThreshold)
			grad.at<uchar>(y - 1, x) = 0;
		else
			scanNeighbors(grad, x, y - 1, lowerThreshold, scanCheck);
}

void hysteresis(Mat& grad, int lowerThreshold, int upperThreshold)
{
	vector<vector<bool>> scanCheck(grad.size().height, vector<bool>(grad.size().width, false));
	for (int y = 0; y < grad.size().height; ++y)
		for (int x = 0; x < grad.size().width; ++x)
			if (grad.at<uchar>(y, x) < upperThreshold)
				grad.at<uchar>(y, x) = 0;
			else
			{
				scanNeighbors(grad, x, y, lowerThreshold, scanCheck);
			}
}

void nonMaxSuppression(Mat& grad, vector<vector<uchar>> directions)
{
	for (int y = 0; y < grad.size().height; ++y)
		for (int x = 0; x < grad.size().width; ++x)
		{
			if (grad.at<uchar>(y, x) != 0) 
			{
				uchar comp1 = 0, comp2 = 0;
				switch (directions[y][x])
				{
				case 0:
					if (x - 1 < 0)
						comp1 = 0;
					else
						comp1 = grad.at<uchar>(y, x - 1);
					if (x + 1 >= grad.size().width)
						comp2 = 0;
					else 
						comp2 = grad.at<uchar>(y, x + 1);
					break;
				case 45:
					if ((y - 1 < 0) || (x - 1 < 0))
						comp1 = 0;
					else 
						comp1 = grad.at<uchar>(y - 1, x - 1);
					if ((y + 1 >= grad.size().height) || (x + 1 >= grad.size().width))
						comp2 = 0;
					else 
						comp2 = grad.at<uchar>(y + 1, x + 1);
					break;
				case 90:
					if (y - 1 < 0)
						comp1 = 0;
					else
						comp1 = grad.at<uchar>(y - 1, x);
					if (y + 1 >= grad.size().height)
						comp2 = 0;
					else 
						comp2 = grad.at<uchar>(y + 1, x);
					break;
				case 135:
					if ((y - 1 < 0) || (x + 1 >= grad.size().width))
						comp1 = 0;
					else 
						comp1 = grad.at<uchar>(y - 1, x + 1);
					if ((y + 1 >= grad.size().height) || (x - 1 < 0))
						comp2 = 0;
					else 
						comp2 = grad.at<uchar>(y + 1, x - 1);
					break;
				}
				if (grad.at<uchar>(y, x) <= comp1 || grad.at<uchar>(y, x) <= comp2)
					grad.at<uchar>(y, x) = 0;
			}
		}
}