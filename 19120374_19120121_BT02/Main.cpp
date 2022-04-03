#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Laplacian.h"
#include "Sobel.h"
#include "Prewitt.h"
#include "Canny.h"

#define CMD_LAPLACIAN "--l"
#define CMD_SOBEL "--s"
#define CMD_PREWITT "--p"
#define CMD_OUTPUT "-o"
#define CMD_CANNY "--c"
#define CMD_SIGMA "-sigma"
#define CMD_LTHRESHOLD "-low_threshold"
#define CMD_HTHRESHOLD "-high_threshold"


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

	// Hiển thị ảnh gốc
	namedWindow("Original Image: " + fileName, WINDOW_AUTOSIZE);
	imshow("Original Image: " + fileName, image);

	Mat output;
	if (image.type() == CV_8UC3)
		cvtColor(image, image, COLOR_BGR2GRAY);

	// Driver
	if (cmdOptionExists(argv, argc, CMD_LAPLACIAN))
	{
		detectByLaplace(image, output, LAPLACIAN_FILTER::FILTER_3x3);
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
		// Đọc các tham số, nếu không được truyền vào thì khởi tạo mặc định
		int lowerThreshold, upperThreshold;
		float sigma;

		if (cmdOptionExists(argv, argc, CMD_SIGMA))
			sigma = atof(getCmdOption(argv, argc, CMD_SIGMA));
		else
			sigma = 1.4;

		if (cmdOptionExists(argv, argc, CMD_LTHRESHOLD))
			lowerThreshold = atoi(getCmdOption(argv, argc, CMD_LTHRESHOLD));
		else
			lowerThreshold = 20;
		
		if (cmdOptionExists(argv, argc, CMD_HTHRESHOLD))
			upperThreshold = atoi(getCmdOption(argv, argc, CMD_HTHRESHOLD));
		else
			upperThreshold = 100;

		detectByCanny(image, output, CANNY_OPERATOR::SOBEL_OPERATOR, -1, 1, lowerThreshold, upperThreshold, sigma, 5);
	}

	// Ghi file kết quả nếu có tham số output path
	if (cmdOptionExists(argv, argc, CMD_OUTPUT) && (!output.empty()))
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
	if (!output.empty())
	{
		namedWindow("Processed Image: " + fileName, WINDOW_AUTOSIZE);
		imshow("Processed Image: " + fileName, output);
		waitKey(0);
	}
}