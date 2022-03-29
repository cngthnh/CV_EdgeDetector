#include "Prewitt.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

vector<vector<char>> prewitt_filter3x3_x = { {-1,0,1},{-1,0,1},{-1,0,1} };
vector<vector<char>> prewitt_filter3x3_y = { {-1,-1,-1},{0,0,0},{1,1,1} };
vector<vector<char>> prewitt_filter5x5_x = { {9,9,9,9,9}, {9,5,5,5,9},{-7,-3,0,-3,-7},{-7,-3,-3,-3,-7},{-7,-7,-7,-7,-7} };
vector<vector<char>> prewitt_filter5x5_y = { {9,9,-7,-7,-7}, {9,5,-3,-3,-7},{9,5,0,-3,-7},{9,5,-3,-3,-7},{9,9,-7,-7,-7} };

int detectByPrewitt(Mat src, Mat& des, int filter, int padding, int stride)
{
	switch (filter) // check xem nguoi dung muon  tich ma tran nao
	{
	case PREWITT_FILTER::PREWITT_FILTER_3x3:
		des = convPrewitt(src, prewitt_filter3x3_x, prewitt_filter3x3_y, padding, stride);
		break;
	case PREWITT_FILTER::PREWITT_FILTER_5x5:
		des = convPrewitt(src, prewitt_filter5x5_x, prewitt_filter5x5_y, padding, stride);
		break;
	}
	return 1;
}

Mat convPrewitt(Mat& image, vector<vector<char>>& x_mask, vector<vector<char>>& y_mask, int padding, int stride)
{
	Mat result;
	Mat result_x_gradient; // dao ham theo x
	Mat result_y_gradient; // dao ham theo y

	result_x_gradient = conv(image, x_mask, padding, stride);
	result_y_gradient = conv(image, y_mask, padding, stride);
	result = result_x_gradient + result_y_gradient;  // tong 2 dao ham lai
	imshow("x_gradient", result_x_gradient);
	imshow("y_gradient", result_y_gradient);
	return result;
}
