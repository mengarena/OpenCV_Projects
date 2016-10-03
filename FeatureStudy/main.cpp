//Do image matching

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
#include <cmath>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>


#include "OrbMatching.h"

using namespace std;
using namespace cv; 


String strImagePath = "F:\\ForDiversityFrame\\";
String strResultPath = "F:\\DriverTalk_DiversityResult\\";



void study_Diversity_tmp()
{
	int i, j, s, t;
	ofstream flImageCount;
	ofstream flMatchResult;
	ofstream flTmp;
	struct stat filestatus;
	char strFilePathName[100];
	int nImageCount = 0;

	char strImageFile1[100];
	char strImageFile2[100];
	Mat matImage1;
	Mat matImage2;
	OrbMatching myMatcher;

//	int nArrRequiredKeypointNum[] = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 250, 300, 500, 1000};
	int nArrRequiredKeypointNum[] = {1000};

	int nRequiredArrayLen = sizeof(nArrRequiredKeypointNum)/sizeof(nArrRequiredKeypointNum[0]);

	int nNumKeypoint1;
	int nNumKeypoint2;
	char strResultFile[100];
	int nMaxImageIdx1 = 0;
	int nMaxImageIdx2 = 0;
	int nMaxMatchedPoint = 0;

	flTmp.open ("F:\\DriverTalk_DiversityResult\\KeypointNumTmp.csv", ofstream::out);

	for (int mm = 0; mm<nRequiredArrayLen; mm++) {

		for (i=1; i<=1000; i++) {
			nImageCount = 0;
			for (j=1; j<=12; j++) {
				memset(strFilePathName, 0x00, 100);
				sprintf(strFilePathName, "%s%s%d%s%d%s", strImagePath.c_str(), "scene", i, "\\", j, ".jpg");
				if (stat(strFilePathName, &filestatus) == 0) {  //File exists
					nImageCount = nImageCount + 1;
				} else {
					break;
				}
			}

			nMaxImageIdx1 = 0;
			nMaxImageIdx2 = 0;
			nMaxMatchedPoint = 0;

			for (s=1; s<nImageCount; s++) {
				memset(strImageFile1, 0x00, 100);
				sprintf(strImageFile1, "%s%s%d%s%d%s", strImagePath.c_str(), "scene", i, "\\", s, ".jpg");
				matImage1 = imread(strImageFile1, CV_LOAD_IMAGE_GRAYSCALE);

				vector<KeyPoint> keypoints;
				
				keypoints = myMatcher.GetRequiredKeypoint(matImage1, nArrRequiredKeypointNum[mm]);
				cout<<"Keypoints===="<<keypoints.size()<<endl;
				flTmp<<keypoints.size()<<"\n";

			}

		}

	}

	flTmp.close();

}




void study_Diversity()
{
	int i, j, s, t;
	ofstream flImageCount;
	ofstream flMatchResult;

	struct stat filestatus;
	char strFilePathName[100];
	int nImageCount = 0;

	char strImageFile1[100];
	char strImageFile2[100];
	Mat matImage1;
	Mat matImage2;
	OrbMatching myMatcher;

	int nArrRequiredKeypointNum[] = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 250, 300, 500, 1000};
//	int nArrRequiredKeypointNum[] = {500};

	int nRequiredArrayLen = sizeof(nArrRequiredKeypointNum)/sizeof(nArrRequiredKeypointNum[0]);

	int nNumKeypoint1;
	int nNumKeypoint2;
	char strResultFile[100];
	int nMaxImageIdx1 = 0;
	int nMaxImageIdx2 = 0;
	int nMaxMatchedPoint = 0;

	for (int mm = 0; mm<nRequiredArrayLen; mm++) {

		memset(strResultFile, 0x00, 100);
		sprintf(strResultFile, "%s%s%d%s", strResultPath.c_str(), "MatchResult_RequiredKeypoint_", nArrRequiredKeypointNum[mm], ".csv");

		//flImageCount.open ("F:\\DriverTalk_DiversityResult\\imageCount.csv", ofstream::out);
		flMatchResult.open(strResultFile, ofstream::out);

		for (i=1; i<=1000; i++) {
			cout<<mm<<"-----------"<<i<<endl;
			nImageCount = 0;
			for (j=1; j<=12; j++) {
				memset(strFilePathName, 0x00, 100);
				sprintf(strFilePathName, "%s%s%d%s%d%s", strImagePath.c_str(), "scene", i, "\\", j, ".jpg");
				if (stat(strFilePathName, &filestatus) == 0) {  //File exists
					nImageCount = nImageCount + 1;
				} else {
					break;
				}
			}

			nMaxImageIdx1 = 0;
			nMaxImageIdx2 = 0;
			nMaxMatchedPoint = 0;

			for (s=1; s<nImageCount; s++) {
				memset(strImageFile1, 0x00, 100);
				sprintf(strImageFile1, "%s%s%d%s%d%s", strImagePath.c_str(), "scene", i, "\\", s, ".jpg");
				matImage1 = imread(strImageFile1, CV_LOAD_IMAGE_GRAYSCALE);

				for (t = s+1; t<=nImageCount; t++) {
					memset(strImageFile2, 0x00, 100);
					sprintf(strImageFile2, "%s%s%d%s%d%s", strImagePath.c_str(), "scene", i, "\\", t, ".jpg");
					matImage2 = imread(strImageFile2, CV_LOAD_IMAGE_GRAYSCALE);
					vector<DMatch> myMatches;
					myMatches = myMatcher.DoMatching(matImage1, matImage2, nArrRequiredKeypointNum[mm], nNumKeypoint1, nNumKeypoint2);

					if (myMatches.size() > nMaxMatchedPoint) {
						nMaxMatchedPoint = myMatches.size();
						nMaxImageIdx1 = s;
						nMaxImageIdx2 = t;
					}
				}
			}

			flMatchResult<<i<<","<<nMaxMatchedPoint<<","<<nMaxImageIdx1<<","<<nMaxImageIdx2<<","<<nNumKeypoint1<<","<<nNumKeypoint2<<"\n";

			//flImageCount<<i<<","<<nImageCount<<"\n";
		}

		flMatchResult.close();

		//flImageCount.close();
	}

}


void Study_KeyPointNum()
{
	int i, j, s, t;
	ofstream flMatchedResult;

	struct stat filestatus;
	char strFilePathName[100];
	int nImageCount = 0;

	char strImageFile1[100];
	char strImageFile2[100];
	Mat matImage1;
	Mat matImage2;
	OrbMatching myMatcher;
	
	float fRefSize;  //KB
	float fQuerySize;  //KB
	float fSmaller;

	int nNumKeypoint1;
	int nNumKeypoint2;
	char strResultFile[100];
	int nMaxMatchedPoint = 0;

	int nArrRequiredKeypointNum[] = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 250, 300, 500, 1000};
//	int nArrRequiredKeypointNum[] = {500};

	int nRequiredArrayLen = sizeof(nArrRequiredKeypointNum)/sizeof(nArrRequiredKeypointNum[0]);


	for (int mm = 0; mm<nRequiredArrayLen; mm++) {

		memset(strResultFile, 0x00, 100);
		sprintf(strResultFile, "%s%s%d%s", strResultPath.c_str(), "SameCar_MatchResult_RequiredKeypoint_", nArrRequiredKeypointNum[mm], ".csv");

		//flImageCount.open ("F:\\DriverTalk_DiversityResult\\imageCount.csv", ofstream::out);
		flMatchedResult.open(strResultFile, ofstream::out);

		//flMatchedResult.open ("F:\\DriverTalk_DiversityResult\\matcheResult_betweenSameCar.csv", ofstream::out);

		for (i=1; i<=50; i++) {
			cout<<"Required Keypoint------"<< nArrRequiredKeypointNum[mm]<<"      ,Group-----------"<<i<<endl;
			nImageCount = 0;
			for (j=1; j<=35; j++) {
				memset(strFilePathName, 0x00, 100);
				sprintf(strFilePathName, "%s%d%s%d%s", "E:\\TestVideo\\ForDecideSize_50group\\Group", i, "\\image_", j, ".jpg");
				if (stat(strFilePathName, &filestatus) == 0) {  //File exists
					nImageCount = nImageCount + 1;
				} else {
					break;
				}
			}

			nMaxMatchedPoint = 0;

			for (s=1; s<nImageCount; s++) {
				memset(strImageFile1, 0x00, 100);
				sprintf(strImageFile1, "%s%d%s%d%s", "E:\\TestVideo\\ForDecideSize_50group\\Group", i, "\\image_", s, ".jpg");
				matImage1 = imread(strImageFile1, CV_LOAD_IMAGE_GRAYSCALE);

				stat(strImageFile1, &filestatus);
				fRefSize = filestatus.st_size;
				fRefSize = fRefSize*1.0/1024;
				fSmaller = fRefSize;

				for (t = s+1; t<=nImageCount; t++) {
					memset(strImageFile2, 0x00, 100);
					sprintf(strImageFile2, "%s%d%s%d%s", "E:\\TestVideo\\ForDecideSize_50group\\Group", i, "\\image_", t, ".jpg");
					matImage2 = imread(strImageFile2, CV_LOAD_IMAGE_GRAYSCALE);
					stat(strImageFile2, &filestatus);
					fQuerySize = filestatus.st_size;
					fQuerySize = fQuerySize*1.0/1024;
					if (fQuerySize < fSmaller) {
						fSmaller = fQuerySize;
					}

					vector<DMatch> myMatches;
//					myMatches = myMatcher.DoMatching_Fixed(matImage1, matImage2, nNumKeypoint1, nNumKeypoint2);
					myMatches = myMatcher.DoMatching(matImage1, matImage2, nArrRequiredKeypointNum[mm], nNumKeypoint1, nNumKeypoint2);

					flMatchedResult<<i<<","<<s<<","<<t<<","<<fSmaller<<","<<myMatches.size()<<","<<nNumKeypoint1<<","<<nNumKeypoint2<<"\n";

				}
			}


		}

		flMatchedResult.close();
	}



}



void Study_KeyPointNum_DifferentCar()
{
	int i, j, s, t;
	ofstream flMatchedResult;

	struct stat filestatus;
	char strFilePathName[100];
	int nImageCount = 0;

	char strImageFile1[100];
	char strImageFile2[100];
	Mat matImage1;
	Mat matImage2;
	OrbMatching myMatcher;
	
	float fRefSize;  //KB
	float fQuerySize;  //KB
	float fSmaller;

	int nNumKeypoint1;
	int nNumKeypoint2;
	char strResultFile[100];
	int nMaxMatchedPoint = 0;

	int nArrRequiredKeypointNum[] = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 250, 300, 500, 1000};
//	int nArrRequiredKeypointNum[] = {500};

	int nRequiredArrayLen = sizeof(nArrRequiredKeypointNum)/sizeof(nArrRequiredKeypointNum[0]);

	memset(strResultFile, 0x00, 100);
	sprintf(strResultFile, "%s%s%d%s", strResultPath.c_str(), "DifferentCar_MatchResult_RequiredKeypoint_", 1000, ".csv");

	//flImageCount.open ("F:\\DriverTalk_DiversityResult\\imageCount.csv", ofstream::out);
	flMatchedResult.open(strResultFile, ofstream::out);


	nMaxMatchedPoint = 0;

	for (s=1; s<260; s++) {
		memset(strImageFile1, 0x00, 100);
		sprintf(strImageFile1, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\query\\query_", s, ".jpg");
		matImage1 = imread(strImageFile1, CV_LOAD_IMAGE_GRAYSCALE);

		stat(strImageFile1, &filestatus);
		fRefSize = filestatus.st_size;
		fRefSize = fRefSize*1.0/1024;
		fSmaller = fRefSize;

		for (t = s+1; t<=260; t++) {
			memset(strImageFile2, 0x00, 100);
			sprintf(strImageFile2,"%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\query\\query_", t, ".jpg");
			matImage2 = imread(strImageFile2, CV_LOAD_IMAGE_GRAYSCALE);
			stat(strImageFile2, &filestatus);
			fQuerySize = filestatus.st_size;
			fQuerySize = fQuerySize*1.0/1024;
			if (fQuerySize < fSmaller) {
				fSmaller = fQuerySize;
			}

			vector<DMatch> myMatches;
//					myMatches = myMatcher.DoMatching_Fixed(matImage1, matImage2, nNumKeypoint1, nNumKeypoint2);
			myMatches = myMatcher.DoMatching(matImage1, matImage2,1000, nNumKeypoint1, nNumKeypoint2);

			flMatchedResult<<s<<","<<t<<","<<fSmaller<<","<<myMatches.size()<<","<<nNumKeypoint1<<","<<nNumKeypoint2<<"\n";

		}
	}


	flMatchedResult.close();



}

int main()
{
	cout<<"Begin..............."<<endl;

	//study_Diversity_tmp();
	//Study_KeyPointNum();
	Study_KeyPointNum_DifferentCar();
	//study_Diversity();

	cout<<"End..............."<<endl;

	getchar();

	return 0;

}

