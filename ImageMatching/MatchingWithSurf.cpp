//Do image matching

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv; 

String selfTakeImage = "E:\\TestVideo\\Set1\\SelfTook.jpg";

int main()
{
	Mat image = imread(selfTakeImage);
	namedWindow("SIFT");
	imshow("SIFT",image);

	waitKey(30000);

	return 0;
}