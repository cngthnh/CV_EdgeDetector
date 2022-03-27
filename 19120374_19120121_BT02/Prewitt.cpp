#include "Prewitt.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

vector<vector<char>> filter3x3_y = { {-1,0,1},{-1,0,1},{-1,0,1} };
vector<vector<char>> filter3x3_x = { {-1,-1,-1},{0,0,0},{1,1,1} };
vector<vector<char>> filter5x5_x = { {9,9,9,9,9}, {9,5,5,5,9},{-7,-3,0,-3,-7},{-7,-3,-3,-3,-7},{-7,-7,-7,-7,-7} };
vector<vector<char>> filter5x5_y = { {9,9,-7,-7,-7}, {9,5,-3,-3,-7},{9,5,0,-3,-7},{9,5,-3,-3,-7},{9,9,-7,-7,-7} };

int detectByPrewitt(Mat src, Mat& des, int filter, int padding, int stride)
{
	switch (filter)
	{
	case PREWITT_FILTER::PREWITT_FILTER_3x3:
		des = convPrewitt(src, filter3x3_x, filter3x3_y, padding, stride);
		break;
	case PREWITT_FILTER::PREWITT_FILTER_5x5:
		des = convPrewitt(src, filter5x5_x, filter5x5_y, padding, stride);
		break;
	}
	return 1;
}

Mat convPrewitt(Mat& image, vector<vector<char>>& x_mask, vector<vector<char>>& y_mask, int padding, int stride)
{
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
