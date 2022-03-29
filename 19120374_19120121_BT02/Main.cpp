#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Laplacian.h"
#include "Sobel.h"
#include "Prewitt.h"
#include "Canny.h"

#define CMD_LAPLACIAN "-l"
#define CMD_SOBEL "-s"
#define CMD_PREWITT "-p"
#define CMD_OUTPUT "-o"
#define CMD_CANNY "-c"


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
	if (image.type() == CV_8UC3)
		cvtColor(image, image, COLOR_BGR2GRAY);
	if (cmdOptionExists(argv, argc, CMD_LAPLACIAN))
	{
		detectByLaplace(image, output, LAPLACIAN_FILTER::FILTER_3x3, 0);
	}
	else if (cmdOptionExists(argv, argc, CMD_SOBEL))
	{
		detectBySobel(image, output, SOBEL_FILTER::SOBEL_FILTER_3x3);
	}
	else if (cmdOptionExists(argv, argc, CMD_PREWITT))
	{
		detectByPrewitt(image, output, PREWITT_FILTER::PREWITT_FILTER_3x3);
	}
	else if (cmdOptionExists(argv, argc, CMD_CANNY))
	{
		detectByCanny(image, output, 10, 65, CANNY_OPERATOR::PREWITT_OPERATOR, -1, 1, 5.4, 5);
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