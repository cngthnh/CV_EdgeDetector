#include "Sobel.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

vector<vector<char>> y_filter3x3 = { {-1,0,1},{-2,0,2},{-1,0,1} };
vector<vector<char>> x_filter3x3 = { {1,2,1},{0,0,0},{-1,-2,-1} };
vector<vector<char>> y_filter5x5 = { {2,2,4,2,2}, {1,1,2,1,1},{0,0,0,0,0},{-1,-1,-2,-1,-1},{-2,-2,-4,-2,-2} };
vector<vector<char>> x_filter5x5 = { {2,1,0,-1,-2}, {2,1,0,-1,-2},{4,2,0,-2,-4},{2,1,0,-1,-2},{2,1,0,-1,-2} };

int detectBySobel(Mat src, Mat& des, int filter, int padding, int stride)
{
	switch (filter)
	{
	case SOBEL_FILTER::SOBEL_FILTER_3x3:
		des = convSobel(src, x_filter3x3, y_filter3x3, padding, stride);
		break;
	case SOBEL_FILTER::SOBEL_FILTER_5x5:
		des = convSobel(src, x_filter5x5, y_filter5x5, padding, stride);
		break;
	}
	return 1;
}


Mat convSobel(Mat& image, vector<vector<char>>&x_mask, vector<vector<char>>& y_mask, int padding, int stride) {
	Mat result;
	Mat result_x_gradient;
	Mat result_y_gradient;
	Mat pad_image;

	if (image.type() != CV_8UC1)
	{
		cout << "Invalid input image\n";
		return result;
	}

	// "valid" padding
	if (padding == 0)
	{
		pad_image = image;
	}
	// "same" padding
	else if (padding == -1)
	{
		int padding_horiz = ceil((stride * (image.cols - 1) - image.cols + x_mask[0].size()) / 2);
		int padding_vert = ceil((stride * (image.rows - 1) - image.rows + x_mask.size()) / 2);
		copyMakeBorder(image, pad_image, padding_vert, padding_vert, padding_horiz, padding_horiz, BORDER_CONSTANT, (0, 0, 0));
	}
	else
	{
		copyMakeBorder(image, pad_image, padding, padding, padding, padding, BORDER_CONSTANT, (0, 0, 0));
	}

	result = Mat::zeros((pad_image.rows - x_mask.size()) / stride + 1, (pad_image.rows - x_mask[0].size()) / stride + 1, CV_8UC1);
	result_x_gradient = Mat::zeros((pad_image.rows - x_mask.size()) / stride + 1, (pad_image.rows - x_mask[0].size()) / stride + 1, CV_8UC1);
	result_y_gradient = Mat::zeros((pad_image.rows - x_mask.size()) / stride + 1, (pad_image.rows - x_mask[0].size()) / stride + 1, CV_8UC1);

	for (int y = 0; y < ceil((pad_image.rows - x_mask.size()) / stride); ++y)
	{
		for (int x = 0; x < ceil(pad_image.cols - x_mask[0].size() / stride); ++x)
		{
			result_x_gradient.at<uchar>(y, x) = saturate_cast<uchar>(applyKernel(pad_image, x_mask, x * stride, y * stride));
			result_y_gradient.at<uchar>(y, x) = saturate_cast<uchar>(applyKernel(pad_image, y_mask, x * stride, y * stride));
			result.at<uchar>(y, x) = saturate_cast<uchar>(abs(result_x_gradient.at<uchar>(y, x)) + abs(result_y_gradient.at<uchar>(y, x)));

		}
	}
	imshow("x_gradient", result_x_gradient);
	imshow("y_gradient", result_y_gradient);
	return result;
}