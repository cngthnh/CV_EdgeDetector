#include "Sobel.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

// ma tran tich chap 3x3 hoac 5x5
vector<vector<char>> y_filter3x3 = { {-1,0,1},{-2,0,2},{-1,0,1} };
vector<vector<char>> x_filter3x3 = { {1,2,1},{0,0,0},{-1,-2,-1} };
vector<vector<char>> y_filter5x5 = { {2,2,4,2,2}, {1,1,2,1,1},{0,0,0,0,0},{-1,-1,-2,-1,-1},{-2,-2,-4,-2,-2} };
vector<vector<char>> x_filter5x5 = { {2,1,0,-1,-2}, {2,1,0,-1,-2},{4,2,0,-2,-4},{2,1,0,-1,-2},{2,1,0,-1,-2} };

int detectBySobel(Mat src, Mat& des, int filter, int padding, int stride)
{
	switch (filter)  // cho nguoi dung chon tich chap
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
	
	result_x_gradient = conv(image, x_mask, padding, stride);
	result_y_gradient = conv(image, y_mask, padding, stride);
	result = result_x_gradient + result_y_gradient;
	imshow("x_gradient", result_x_gradient);
	imshow("y_gradient", result_y_gradient);	
	return result;
}