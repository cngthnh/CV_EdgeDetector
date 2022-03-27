#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
using namespace std;
using namespace cv;




char* getCmdOption(char** argv, int argc, const char* option);
bool cmdOptionExists(char** argv, int argc, const char* option);
Mat conv(Mat& image, vector<vector<char>>& kernel, int padding, int stride);