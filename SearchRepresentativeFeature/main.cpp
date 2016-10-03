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
#include <direct.h>
#include <sstream>
#include <string>


#include "OrbMatching.h"

using namespace std;
using namespace cv; 


String strImagePath = "E:\\TestVideo\\ForDecideSize_50group\\";
//String strResultFeaturePath = "F:\\ImageFeature\\";
String strResultFeaturePath = "F:\\ImageFeature_SizeLimit\\";

//String strMatchedFeaturePointPath = "F:\\ImageFeature_MatchedPointPos\\";
String strMatchedFeaturePointPath = "F:\\ImageFeature_MatchedPointPos_SizeLimit\\";


void Get_FeaturePoints(Mat& matImage, char* strFeatureFile, int nRequiredKeypointNum)
{
	vector<KeyPoint> keypoints;
	Mat descriptors;
	int nNumKeypoint;
	ofstream flResult;
	Size matSize;
	int featureSize;
	int i,j;

	OrbFeatureDetector detector(nRequiredKeypointNum, 1.1, 10); 
	OrbDescriptorExtractor extractor;

	detector.detect(matImage, keypoints);
	nNumKeypoint = keypoints.size();
	if (nNumKeypoint == 0) {
		return;
	}

	extractor.compute(matImage, keypoints, descriptors);

	matSize = descriptors.size();

	flResult.open(strFeatureFile, ofstream::out);

	for (i=0; i<matSize.height; i++) {
		for (j=0; j<matSize.width; j++) {
			flResult<<(int)(descriptors.at<unsigned char>(i, j))<<",";
		}
		flResult<<"\n";
	}

	flResult.close();

#if 0
	featureSize = descriptors.elemSize()* matSize.width * matSize.height;  //Bytes

	cout<<"[Size] [Cols]= " <<matSize.width <<" ,[Rows]= "<<matSize.height<<endl;
	cout<<"[Channel]= "<<descriptors.channels()<<endl;
	cout<<"[Depth]= "<<descriptors.depth()<<endl;
	cout<<"[Element Size]= "<<descriptors.elemSize()<<endl;
	cout<<"[size of element channel]= " <<descriptors.elemSize1()<<endl;
	cout<<"[Descriptor Col]= " <<descriptors.cols << ",[Descriptor Row]= "<<descriptors.rows <<endl;
	cout<<"[Step0]= "<<descriptors.step[0]<<",[Step1]="<<descriptors.step[1]<<endl;
	cout<<"KeypointSize="<<sizeof(KeyPoint)<<",Keypoint number="<<keypoints.size()<<",KeypointSize="<<keypoints.size()*sizeof(KeyPoint)<<",DescriptorSize="<<featureSize<<endl;
#endif

}


void Extract_Features()
{
	int i, j, s, t;
	ofstream flMatchedResult;

	struct stat filestatus;
	char strFeatureFileFolder[100];
	char strFeatureFile[100];
	int nImageCount = 0;
	char strImageFile[100];
	Mat matImage;
	
	float fRefSize;  //KB
	int nRequiredKeypointNum = 1000;
	int nImageFeatureIndex = 0;

	char strResultFile[100];

	for (i=1; i<=50; i++) {
		memset(strFeatureFileFolder, 0x00, 100);
		sprintf(strFeatureFileFolder, "%s%s%d", strResultFeaturePath.c_str(), "Group", i);
		mkdir(strFeatureFileFolder);

		nImageCount = 0;

		for (j=1; j<=35; j++) {
			memset(strImageFile, 0x00, 100);
			sprintf(strImageFile, "%s%s%d%s%d%s", strImagePath.c_str(), "Group", i, "\\image_", j, ".jpg");
			if (stat(strImageFile, &filestatus) == 0) {  //File exists
				nImageCount = nImageCount + 1;
			} else {
				break;
			}
		}

		nImageFeatureIndex = 0;

		for (s=1; s<=nImageCount; s++) {

			memset(strImageFile, 0x00, 100);
			sprintf(strImageFile, "%s%s%d%s%d%s", strImagePath.c_str(), "Group", i, "\\image_", s, ".jpg");
			matImage = imread(strImageFile, CV_LOAD_IMAGE_GRAYSCALE);

			stat(strImageFile, &filestatus);
			fRefSize = filestatus.st_size;
			fRefSize = fRefSize*1.0/1024;

			if (fRefSize >= 10.0) {
				nImageFeatureIndex = nImageFeatureIndex + 1;
				memset(strFeatureFile, 0x00, 100);
//				sprintf(strFeatureFile, "%s%s%d%s%d%s", strResultFeaturePath.c_str(), "Group", i, "\\imageFeature_", s, ".csv");
				sprintf(strFeatureFile, "%s%s%d%s%d%s", strResultFeaturePath.c_str(), "Group", i, "\\imageFeature_", nImageFeatureIndex, ".csv");

				Get_FeaturePoints(matImage, strFeatureFile, nRequiredKeypointNum);
			}
		}
	}

}


void Search_CommonKeypoints_byMatching_SizeLimit()
{
	int i, j, s, t;
	ofstream flMatchedResult;

	struct stat filestatus;
	char strFeatureFileFolder[100];
	int nImageCount = 0;
	char strImageFileRef[100];
	char strImageFileQuery[100];
	Mat matImage1, matImage2;
	OrbMatching myMatcher;
	int nNumKeypoint1, nNumKeypoint2;
	float fRefSize;  //KB
	float fQuerySize;
	float fSmaller;
	int nRequiredKeypointNum = 1000;
	int nImageFeatureIndex = 0;
	ofstream flResult;

	char strResultFile[100];

	for (i=1; i<=50; i++) {
		memset(strFeatureFileFolder, 0x00, 100);
		sprintf(strFeatureFileFolder, "%s%s%d", strMatchedFeaturePointPath.c_str(), "Group", i);
		mkdir(strFeatureFileFolder);

		nImageCount = 0;

		for (j=1; j<=35; j++) {
			memset(strImageFileRef, 0x00, 100);
			sprintf(strImageFileRef, "%s%s%d%s%d%s", strImagePath.c_str(), "Group", i, "\\image_", j, ".jpg");
			if (stat(strImageFileRef, &filestatus) == 0) {  //File exists
				nImageCount = nImageCount + 1;
			} else {
				break;
			}
		}

		nImageFeatureIndex = 0;

//		for (s=1; s<=nImageCount; s++) {

		memset(strImageFileRef, 0x00, 100);
		sprintf(strImageFileRef, "%s%s%d%s", strImagePath.c_str(), "Group", i, "\\image_1.jpg");
		matImage1 = imread(strImageFileRef, CV_LOAD_IMAGE_GRAYSCALE);

		stat(strImageFileRef, &filestatus);
		fRefSize = filestatus.st_size;
		fRefSize = fRefSize*1.0/1024;

		for (t=2; t<=nImageCount; t++) {
			fSmaller = fRefSize;
			memset(strImageFileQuery, 0x00, 100);
			sprintf(strImageFileQuery, "%s%s%d%s%d%s", strImagePath.c_str(), "Group", i, "\\image_", t, ".jpg");
			matImage2 = imread(strImageFileQuery, CV_LOAD_IMAGE_GRAYSCALE);

			stat(strImageFileQuery, &filestatus);
			fQuerySize = filestatus.st_size;
			fQuerySize = fQuerySize*1.0/1024;

			if (fQuerySize < fSmaller) {
				fSmaller = fQuerySize;
			}

			if (fSmaller >= 10.0) {
				vector<DMatch> myMatches;
				myMatches = myMatcher.DoMatching_Fixed(matImage1, matImage2, nRequiredKeypointNum, nNumKeypoint1, nNumKeypoint2);

				if (myMatches.size() > 0) {
					nImageFeatureIndex = nImageFeatureIndex + 1;
					memset(strResultFile, 0x00, 100);
					sprintf(strResultFile, "%s%s%d%s%d%s", strMatchedFeaturePointPath.c_str(), "Group", i, "\\MatchedPointIdx_", nImageFeatureIndex, ".csv");
					flResult.open(strResultFile, ofstream::out);
					//Get the index of the matched points in the first image (i.e. ref image)
					for(vector<DMatch>::const_iterator it = myMatches.begin(); it != myMatches.end(); ++it) {
						flResult<<it->queryIdx<<"\n";
					} 

					flResult.close();
				}
			}

		}

//		}

	}

}


//All other images compare with the first image in each group
void Search_CommonKeypoints_byMatching()
{
	int i, j, s, t;
	ofstream flMatchedResult;

	struct stat filestatus;
	char strFeatureFileFolder[100];
	int nImageCount = 0;
	char strImageFileRef[100];
	char strImageFileQuery[100];
	Mat matImage1, matImage2;
	OrbMatching myMatcher;
	int nNumKeypoint1, nNumKeypoint2;
	float fRefSize;  //KB
	float fQuerySize;
	float fSmaller;
	int nRequiredKeypointNum = 1000;
	int nImageFeatureIndex = 0;
	ofstream flResult;

	char strResultFile[100];

	for (i=1; i<=50; i++) {
		memset(strFeatureFileFolder, 0x00, 100);
		sprintf(strFeatureFileFolder, "%s%s%d", strMatchedFeaturePointPath.c_str(), "Group", i);
		mkdir(strFeatureFileFolder);

		nImageCount = 0;

		for (j=1; j<=35; j++) {
			memset(strImageFileRef, 0x00, 100);
			sprintf(strImageFileRef, "%s%s%d%s%d%s", strImagePath.c_str(), "Group", i, "\\image_", j, ".jpg");
			if (stat(strImageFileRef, &filestatus) == 0) {  //File exists
				nImageCount = nImageCount + 1;
			} else {
				break;
			}
		}

		nImageFeatureIndex = 0;

//		for (s=1; s<=nImageCount; s++) {

		memset(strImageFileRef, 0x00, 100);
		sprintf(strImageFileRef, "%s%s%d%s", strImagePath.c_str(), "Group", i, "\\image_1.jpg");
		matImage1 = imread(strImageFileRef, CV_LOAD_IMAGE_GRAYSCALE);

		stat(strImageFileRef, &filestatus);
		fRefSize = filestatus.st_size;
		fRefSize = fRefSize*1.0/1024;

		for (t=2; t<=nImageCount; t++) {
			fSmaller = fRefSize;
			memset(strImageFileQuery, 0x00, 100);
			sprintf(strImageFileQuery, "%s%s%d%s%d%s", strImagePath.c_str(), "Group", i, "\\image_", t, ".jpg");
			matImage2 = imread(strImageFileQuery, CV_LOAD_IMAGE_GRAYSCALE);

			stat(strImageFileQuery, &filestatus);
			fQuerySize = filestatus.st_size;
			fQuerySize = fQuerySize*1.0/1024;

			if (fQuerySize < fSmaller) {
				fSmaller = fQuerySize;
			}


			vector<DMatch> myMatches;
			myMatches = myMatcher.DoMatching_Fixed(matImage1, matImage2, nRequiredKeypointNum, nNumKeypoint1, nNumKeypoint2);

			if (myMatches.size() > 0) {
				nImageFeatureIndex = nImageFeatureIndex + 1;
				memset(strResultFile, 0x00, 100);
				sprintf(strResultFile, "%s%s%d%s%d%s", strMatchedFeaturePointPath.c_str(), "Group", i, "\\MatchedPointIdx_", nImageFeatureIndex, ".csv");
				flResult.open(strResultFile, ofstream::out);
				//Get the index of the matched points in the first image (i.e. ref image)
				for(vector<DMatch>::const_iterator it = myMatches.begin(); it != myMatches.end(); ++it) {
					flResult<<it->queryIdx<<"\n";
				} 

				flResult.close();
			}

		
		}

//		}

	}
}


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


void Show_CommonFeaturePoint(int nRequiredKeypointNum, int nGroupIndex, int nCommonFeatureCnt, String sFeatureIndexLine)
{
	Mat matImage;
	vector<KeyPoint> keypoints;
	vector<string> svFeatureIndex;
	int nFeaturePointIndex;
	char strGroup[100];
	svFeatureIndex = split(sFeatureIndexLine, ',');

	char strImageFile[100];

	memset(strImageFile, 0x00, 100);
	sprintf(strImageFile,  "%s%s%d%s", strImagePath.c_str(), "Group", nGroupIndex, "\\image_1.jpg");

	matImage = imread(strImageFile, CV_LOAD_IMAGE_GRAYSCALE);

	OrbFeatureDetector detector(nRequiredKeypointNum, 1.1, 10); 
	OrbDescriptorExtractor extractor;

	detector.detect(matImage, keypoints);

	for (int i=0; i<nCommonFeatureCnt; i++) {
		nFeaturePointIndex = atoi(svFeatureIndex[i].c_str());
		circle(matImage, keypoints[nFeaturePointIndex].pt, 2, Scalar(255, 0, 0), 3);
	}

	memset(strGroup, 0x00, 100);
	sprintf(strGroup, "Group_%d", nGroupIndex);
	namedWindow(strGroup);
	imshow(strGroup,matImage);
	waitKey(2000);

}


void ShowCommonFeaturePoint()
{
	String sFeaturePointIndexFile = "F:\\ImageFeature_MatchedPointPos_SizeLimit\\FeaturePointIndex.csv";
	String sCommonMatchedPointIndexStatFile = "F:\\ImageFeature_MatchedPointPos_SizeLimit\\CommonMatchedPointIndexStat.csv";
	char strLine[100];
	String sCommonStatLine;
	String sFeatureIndexLine;
	int nRequiredKeypointNum = 1000;

//	ifstream fileCommonStat(sCommonMatchedPointIndexStatFile);
//	ifstream fileFeatureIndex(sFeaturePointIndexFile);
	ifstream fileCommonStat;
	ifstream fileFeatureIndex;

	vector<string> svStat;
	
	int nGroupIndex;
	int nCommonFeatureCnt;

	fileCommonStat.open(sCommonMatchedPointIndexStatFile);
	fileFeatureIndex.open(sFeaturePointIndexFile);

	while( getline(fileCommonStat, sCommonStatLine) ) {
		getline(fileFeatureIndex, sFeatureIndexLine);

		svStat = split(sCommonStatLine, ',');
		nGroupIndex = atoi(svStat[0].c_str());
		nCommonFeatureCnt = atoi(svStat[1].c_str());

		if (nCommonFeatureCnt > 0) {
			cout<<"Group["<<nGroupIndex<<"],  Common Feature Count---"<<nCommonFeatureCnt<<endl;
			Show_CommonFeaturePoint(nRequiredKeypointNum, nGroupIndex, nCommonFeatureCnt, sFeatureIndexLine);
			getchar();
		}

	}

	fileFeatureIndex.close();
	fileCommonStat.close();	



}


void Get_MainImageSize()
{
	ofstream flResult;

	struct stat filestatus;
	int i;
	char strMainImageFile[100];
	char strResultFile[100];
	float fSize;
	
	memset(strResultFile, 0x00, 100);
	sprintf(strResultFile, "%s%s", strMatchedFeaturePointPath.c_str(), "mainImageSize.csv");
	flResult.open(strResultFile, ofstream::out);

	for (i=1; i<=50; i++) {
		memset(strMainImageFile, 0x00, 100);
		sprintf(strMainImageFile, "%s%s%d%s", strImagePath.c_str(), "Group", i, "\\image_1.jpg");
		stat(strMainImageFile, &filestatus);
		fSize = filestatus.st_size;
		fSize = fSize*1.0/1024;

		if (fSize >= 10.0) {
			flResult<<",1"<<"\n";
		} else {
			flResult<<",0"<<"\n";
		}

	}

	flResult.close();
}



int main()
{
	cout<<"Begin..............."<<endl;

	//Extract_Features();
	//Search_CommonKeypoints_byMatching();
	//Search_CommonKeypoints_byMatching_SizeLimit();
	//ShowCommonFeaturePoint();
	Get_MainImageSize();
	cout<<"End..............."<<endl;

	getchar();

	return 0;

}

