#include "Laplacian.h"

vector<vector<char>> filter3x3 = { {-1,-1,-1},{-1,8,-1},{-1,-1,-1} };
vector<vector<char>> filter5x5 = { {0,0,-1,0,0}, {0,-1,-2,-1,0},{-1,-2,17,-2,-1},{0,-1,-2,-1,0},{0,0,-1,0,0} };

int detectByLaplace(Mat src, Mat& des, int filter, int padding, int stride)
{
	switch (filter)
	{
	case LAPLACIAN_FILTER::FILTER_3x3:
		des = conv(src, filter3x3, padding, stride);
		break;
	case LAPLACIAN_FILTER::FILTER_5x5:
		des = conv(src, filter5x5, padding, stride);
		break;
	}
	return 1;
}