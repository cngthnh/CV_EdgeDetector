#pragma once
#include<iostream>
#include<cmath>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "Utils.h"

using namespace std;
using namespace cv;

enum SOBEL_FILTER {
	FILTER_3x3 = 0,
	FILTER_5x5 = 1
};

int xGradient(Mat image, int x, int y);
int yGradient(Mat image, int x, int y);