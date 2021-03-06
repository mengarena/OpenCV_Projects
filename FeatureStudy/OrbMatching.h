#pragma once

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <opencv2\legacy\legacy.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv; 

class OrbMatching
{

private:
	float ratio;	//Max ratio between 1st and 2nd NN
	double distance;	//Min distance to epipolar
	double confidence;	//Confidence level (probability)
	bool refineF;	//If true will refine the Fundamental matrix

public:
	OrbMatching(void);
	~OrbMatching(void);

	void setRatio(float rt);
	void setDistance(double dst);
	void setConfidence(double confd);

	int ratioTest(vector<vector<DMatch>> &matches);
	void symmetryTest(const vector<vector<DMatch>>& matches1,const vector<vector<DMatch>>& matches2, vector<DMatch>& symMatches);
	void ransacTest(const vector<DMatch>& matches, const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2, vector<DMatch>& outMatches);
	void ransacTest_Special(const vector<DMatch>& matches, const vector<Point2f>& points1, const vector<Point2f>& points2, vector<DMatch>& outMatches);
	vector<KeyPoint> GetRequiredKeypoint(Mat& image1, int nRequiredKeypointNum);
	vector<DMatch> DoMatching(Mat& image1, Mat& image2, int nRequiredKeypointNum, int &nNumKeypoint1, int &nNumKeypoint2);
	vector<DMatch> DoMatching_Fixed(Mat& image1, Mat& image2, int &nNumKeypoint1, int &nNumKeypoint2);

	void filterWithSlopeDistance(Mat& image1, 
						Mat& image2, 
						const vector<KeyPoint>& keypoints1, 
						const vector<KeyPoint>& keypoints2, 
						const vector<DMatch>& inMatches,
						vector<DMatch>& finalMatches);

	void filterWithSlopeDistance_Special(int widthBase, 
											const vector<Point2f>& points1, 
											const vector<Point2f>& points2, 
											const vector<DMatch>& inMatches,
											vector<DMatch>& finalMatches );

};

