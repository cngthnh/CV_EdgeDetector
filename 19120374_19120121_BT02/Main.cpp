#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Laplacian.h"
#include "Sobel.h"
#include "Prewitt.h"

#define CMD_LAPLACIAN "-l"
#define CMD_SOBEL "-s"
#define CMD_PREWITT "-p"
#define CMD_OUTPUT "-o"


int main(int argc, char** argv) {

	if (argc < 2) {
		cout << "Edge detector" << '\n';
		return -1;
	}

	string fileName(argv[1]);

	// Tạo ma trận chứa các giá trị điểm ảnh
	Mat image;
	// Đọc file ảnh và giữ nguyên số lượng channels
	image = imread(fileName, IMREAD_UNCHANGED);

	if (!image.data)
	{
		cout << "Image file is inaccessible\n";
		return -1;
	}

	namedWindow("Original Image: " + fileName, WINDOW_AUTOSIZE);
	imshow("Original Image: " + fileName, image);

	Mat output;
	if (cmdOptionExists(argv, argc, CMD_LAPLACIAN))
	{
		cvtColor(image, image, COLOR_BGR2GRAY);
		// Apply 3x3 gaussian filter with sigma=0.7
		/*vector<vector<float>> gFilter = generateGaussianFilter(3, 0.7);
		image = conv(image, gFilter, -1, 1);*/
		detectByLaplace(image, output, LAPLACIAN_FILTER::FILTER_3x3, 0);
	}
	else if (cmdOptionExists(argv, argc, CMD_SOBEL))
	{
		cvtColor(image, image, COLOR_BGR2GRAY);
		detectBySobel(image, output, SOBEL_FILTER::SOBEL_FILTER_3x3);
	}
	else if (cmdOptionExists(argv, argc, CMD_PREWITT))
	{
		cvtColor(image, image, COLOR_BGR2GRAY);
		detectByPrewitt(image, output, PREWITT_FILTER::PREWITT_FILTER_3x3);
	}

	if (cmdOptionExists(argv, argc, CMD_OUTPUT))
	{
		char* outputPath = getCmdOption(argv, argc, CMD_OUTPUT);
		if (outputPath != NULL)
		{
			imwrite(outputPath, output);
		}
		else
		{
			cout << "Output path does not exist\n";
		}
	}
	namedWindow("Processed Image: " + fileName, WINDOW_AUTOSIZE);
	imshow("Processed Image: " + fileName, output);
	waitKey(0);
}