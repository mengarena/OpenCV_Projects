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


#include "SurfMatching.h"
#include "SiftMatching.h"

using namespace std;
using namespace cv; 

//String baseImageFile = "E:\\TestVideo\\Set1\\SelfTook.jpg";
//String receivedImageFile = "E:\\TestVideo\\Set1\\SelfTook_33.png";
//String receivedImageFile = "E:\\TestVideo\\Set1\\SelfTook_40.png";
//String receivedImageFile = "E:\\TestVideo\\Set1\\SelfTook_40_2.png";
//String receivedImageFile = "E:\\TestVideo\\Set1\\SelfTook_50.png";
//String receivedImageFile = "E:\\TestVideo\\Set1\\SelfTook_75.png";
//String receivedImageFile = "E:\\TestVideo\\Set2\\SelfTook.jpg";
//String receivedImageFile = "E:\\TestVideo\\Set2\\SelfTook_38.png";
//String receivedImageFile = "E:\\TestVideo\\Set2\\SelfTook_90.png";

//String baseImageFile = "E:\\TestVideo\\Set1\\self_fromOthers1.jpg";	//self_fromOthers1~2
//String baseImageFile = "E:\\TestVideo\\Set1\\self_back1.jpg"; //self_back1~3
//String receivedImageFile = "E:\\TestVideo\\Set1\\self_light1.jpg"; //self_light1~2
//String receivedImageFile = "E:\\TestVideo\\Set1\\othercar1_1.jpg"; //othercar1_1~3
//String receivedImageFile = "E:\\TestVideo\\Set1\\othercar2_1.jpg"; //othercar2_1~2
//String baseImageFile = "E:\\TestVideo\\Set1\\othercar3_1.jpg"; //othercar3_1~5
//String receivedImageFile = "E:\\TestVideo\\Set1\\othercar3_3.jpg"; //othercar3_1~5

/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Original///////////////////////////////////////////////////////////
//Galaxy Nexus (Rear)
//String baseImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_20feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_30feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_50feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_80feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_110feet.png";

//Galaxy Nexus (Rear Side 15)
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_20feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_30feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_50feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_80feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_110feet.png";

//Galaxy Nexus (Rear Side 30)
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_20feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_30feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_50feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_80feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_110feet.png";

/////////////////////////////////////////////////////////////////////////////////////////////////
//Galaxy Nexus (Rear) --Scaled for Nexus S with Height
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_20feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_30feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_50feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_80feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_110feet_forS.png";

//Galaxy Nexus (Rear Side 15) --Scaled for Nexus S with Height
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_20feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_30feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_50feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_80feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_110feet_forS.png";

//Galaxy Nexus (Rear Side 30) --Scaled for Nexus S with Height
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_20feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_30feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_50feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_80feet_forS.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_110feet_forS.png";


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Galaxy Nexus (Rear) --Scaled for Nexus S with Width
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_20feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_30feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_50feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_80feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_110feet_forS720.png";

//Galaxy Nexus (Rear Side 15) --Scaled for Nexus S with Width
//String baseImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_20feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_30feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_50feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_80feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_15\\RearSide15_110feet_forS720.png";

//Galaxy Nexus (Rear Side 30) --Scaled for Nexus S with Width
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_20feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_30feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_50feet_forS720.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_80feet_for720S.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\RearSide_30\\RearSide30_110feet_forS720.png";

////////////////////////////////////////////////////////////////
//Nexus S (Rear)
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\Rear\\Rear_20feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\Rear\\Rear_30feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\Rear\\Rear_50feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\Rear\\Rear_80feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\Rear\\Rear_110feet.png";

//Nexus S (Rear Side 15)
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_15\\RearSide15_20feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_15\\RearSide15_30feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_15\\RearSide15_50feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_15\\RearSide15_80feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_15\\RearSide15_110feet.png";

//Nexus S (Rear Side 30)
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_30\\RearSide30_20feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_30\\RearSide30_30feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_30\\RearSide30_50feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_30\\RearSide30_80feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\RearSide_30\\RearSide30_110feet.png";


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////iPhone 4S (Scale to Galaxy Nexus width)/////////////////////////////////////////////////////
//////////Rear//////Focal scaled
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_20feet_forGN1280ss.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_30feet_forGN1280ss.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_50feet_forGN1280ss.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_80feet_forGN1280ss.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_110feet_forGN1280ss.png";

//////////Rear Side 15//////Focal scaled
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_20feet_forGN1280ss.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_30feet_forGN1280ss.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_50feet_forGN1280ss.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_80feet_forGN1280ss.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_110feet_forGN1280ss.png";


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////iPhone 4S (Scale to Nexus S width)//////////////////////////////////////////////////////////
//////////Rear//////
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_20feet_forS720s.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_30feet_forS720s.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_50feet_forS720s.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_80feet_forS720s.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_110feet_forS720s.png";

//////////Rear Side 15//////
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_20feet_forS720s.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_30feet_forS720s.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_50feet_forS720s.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_80feet_forS720s.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\RearSide15\\RearSide15_110feet_forS720s.png";


////////////////////////////////////////////////////////////////////////////////////////////////////

//String baseImageFile = "E:\\TestVideo\\Lab_Video\\S_Close.jpg";
//String baseImageFile = "E:\\TestVideo\\Lab_Video\\S_Far.jpg";
//String receivedImageFile = "E:\\TestVideo\\Lab_Video\\iPhone_Close.jpg";
//String receivedImageFile = "E:\\TestVideo\\Lab_Video\\iPhone_Far.jpg";
////////////////////////////////////////////////////////////////////////////////////////////////////

//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_20feet_org.jpg";
//String baseImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_30feet_org.jpg";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_30feet_org_resized.jpg";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_30feet_org_resizedForSs.jpg";

//String baseImageFile = "E:\\TestVideo\\ParkingLot\\iPhone4S\\Rear\\Rear_50feet_org.jpg";

//String baseImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\Rear\\Rear_20feet.png";
//String baseImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\Rear\\Rear_30feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\NexusS\\Rear\\Rear_50feet.png";


//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_20feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_30feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_50feet.png";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_30feet_resizedForS.jpg";
//String receivedImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_50feet_resizedForS.jpg";
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////Big Parking Lot///////////////////////////////////////////////////////////////////////////////////
//////////////////Galaxy Nexus - 1////////////////////////////////////////////////////////////////////////
//String receivedImageFile = "E:\\TestVideo\\BigParking\\GN1\\Rear_20feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\GN1\\Rear_30feet.jpg";
//String baseImageFile = "E:\\TestVideo\\BigParking\\GN1\\Rear_40feet.jpg";
//String baseImageFile = "E:\\TestVideo\\BigParking\\GN1\\Rear_60feet.jpg";
//String baseImageFile = "E:\\TestVideo\\BigParking\\GN1\\Rear_80feet.jpg";
//String baseImageFile = "E:\\TestVideo\\BigParking\\GN1\\Rear_100feet.jpg";
//String baseImageFile = "E:\\TestVideo\\BigParking\\GN1\\60feet.png";
//String baseImageFile = "E:\\TestVideo\\BigParking\\GN1\\80feet.png";

//////////////////Galaxy Nexus - 3////////////////////////////////////////////////////////////////////////
//String baseImageFile = "E:\\TestVideo\\BigParking\\GN3\\Rear_20feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\GN3\\Rear_30feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\GN3\\Rear_40feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\GN3\\Rear_60feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\GN3\\Rear_80feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\GN3\\Rear_100feet.jpg";

//////////////////Nexus One////////////////////////////////////////////////////////////////////////
//String receivedImageFile = "E:\\TestVideo\\BigParking\\NexusOne\\Rear_20feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\NexusOne\\Rear_30feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\NexusOne\\Rear_40feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\NexusOne\\Rear_60feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\NexusOne\\Rear_80feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\NexusOne\\Rear_100feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\NexusOne\\60feet.png";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\NexusOne\\80feet.png";

//////////////////iPhone 4S////////////////////////////////////////////////////////////////////////
//String receivedImageFile = "E:\\TestVideo\\BigParking\\iPhone4S\\Rear_20feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\iPhone4S\\Rear_30feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\iPhone4S\\Rear_40feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\iPhone4S\\Rear_60feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\iPhone4S\\Rear_80feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\iPhone4S\\Rear_100feet.jpg";

//////////////////Windows Phone////////////////////////////////////////////////////////////////////////
//String receivedImageFile = "E:\\TestVideo\\BigParking\\WP\\Rear_20feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\WP\\Rear_30feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\WP\\Rear_40feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\WP\\Rear_60feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\WP\\Rear_80feet.jpg";
//String receivedImageFile = "E:\\TestVideo\\BigParking\\WP\\Rear_100feet.jpg";

////////////////////////////////////////

//String baseImageFile = "F:\\tt\\20feet.jpg";
//String receivedImageFile = "F:\\tt\\20feet_compressed.jpg";

#if 1
void MeasureMatching_SpecialVersion()
{
	char strRefFilename[120];
	char strQueryFilename[120];
	ofstream myfile;

	int nNumKeypoint1 = 0;
	int nNumKeypoint2 = 0; 
	double processTime = 0.0;
	struct stat filestatus;
	double featureSize1 = 0.0;
	double featureSize2 = 0.0;
	int nFeatureNum = 100;
	vector<DMatch> myMatches;
	double duration = 0.0; //Duration for image matching
	char strFilenameBase[120];

	memset(strFilenameBase, 0x00, 100);
	sprintf(strFilenameBase, "%s%d%s", "F:\\forImageFeatureSize\\ORB_SameGroups_", nFeatureNum, ".csv");

	myfile.open (strFilenameBase, ofstream::out | ofstream::app);
//	myfile.open ("E:\\TestVideo\\ForDecideSize\\Size_MatchedPoints_SURF_withFinal.csv", ofstream::out | ofstream::app);
//	myfile.open ("E:\\TestVideo\\ForDecideSize\\Size_MatchedPoints_SIFT_withFinal.csv", ofstream::out | ofstream::app);

	int nRefCountArray[] =    {2,  4,   3,  4,   3,  3,  4,  3,  3,  3,  2,  3,  3,  2, 3};

	//int nRefCountArray[] = {3, 3, 3, 3, 4, 3, 2, 3, 3, 3, 3, 3, 3, 3};   //Different car
	int nQueryCountArray[] = {10, 52, 111, 29, 111, 47, 17, 40, 37, 20, 18, 38, 30, 54, 14};

	Mat queryImage;
	Mat refImage;
	Size matSizeRef;
	Size matSizeQuery;
	float fRefSize;  //KB
	float fQuerySize;  //KB
	SurfMatching myMatcher;
//	SiftMatching myMatcher;
	
	

	for (int i = 1; i<=15; i++) {
		for (int j = 1; j<=nRefCountArray[i-1]; j++) {
			memset(strRefFilename, 0x00, 120);
			sprintf(strRefFilename, "%s%d%s%d%s", "E:\\TestVideo\\ForDecideSize\\Group", i, "\\ref", j, ".jpg");
			refImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);

			stat(strRefFilename, &filestatus);
			fRefSize = filestatus.st_size;
			fRefSize = fRefSize*1.0/1024;

			for (int k = 1; k<=nQueryCountArray[i-1]; k++) {
				memset(strQueryFilename, 0x00, 120);
				sprintf(strQueryFilename, "%s%d%s%d%s", "E:\\TestVideo\\ForDecideSize\\Group", i, "\\query\\image_", k, ".jpg");
				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);
				stat(strQueryFilename, &filestatus);
				fQuerySize = filestatus.st_size;
				fQuerySize = fQuerySize*1.0/1024;

				myMatches = myMatcher.DoMatching(refImage, queryImage, nFeatureNum, processTime, nNumKeypoint1, nNumKeypoint2, featureSize1, featureSize2);

				myfile<<i<<","<<j<<","<<k<<","<<fRefSize<<","<<fQuerySize<<","<<myMatches.size()<<"\n";
			}
		}
	}

	myfile.close();

	return;

}





void MeasureMatching()
{
	char strRefFilename[120];
	char strQueryFilename[120];
	ofstream myfile;
	ofstream myfile2;

	myfile.open ("F:\\forImageFeatureSize\\Size_MatchedPoints_ORB_withFinal.csv", ofstream::out | ofstream::app);
//	myfile.open ("E:\\TestVideo\\ForDecideSize\\Size_MatchedPoints_ORB_withFinal.csv", ofstream::out | ofstream::app);

//	myfile.open ("E:\\TestVideo\\ForDecideSize\\Size_MatchedPoints_SURF_withFinal.csv", ofstream::out | ofstream::app);
//	myfile.open ("E:\\TestVideo\\ForDecideSize\\Size_MatchedPoints_SIFT_withFinal.csv", ofstream::out | ofstream::app);

	myfile2.open ("F:\\forImageFeatureSize\\ORB_SameGroupSmallerSizeOnly.csv", ofstream::out | ofstream::app);

	int nRefCountArray[] =    {2,  4,   3,  4,   3,  3,  4,  3,  3,  3,  2,  3,  3,  2, 3};

	//int nRefCountArray[] = {3, 3, 3, 3, 4, 3, 2, 3, 3, 3, 3, 3, 3, 3};   //Different car
	int nQueryCountArray[] = {10, 52, 111, 29, 111, 47, 17, 40, 37, 20, 18, 38, 30, 54, 14};

	Mat queryImage;
	Mat refImage;
	Size matSizeRef;
	Size matSizeQuery;
	float fRefSize;  //KB
	float fQuerySize;  //KB
	SurfMatching myMatcher;
//	SiftMatching myMatcher;
	int nFeatureNum = 1000;
	double featureSize1 = 0.0;
	double featureSize2 = 0.0;
	int nNumKeypoint1;
	int nNumKeypoint2; 	
	double fSmallSize = 0.0;

	
	double processTime = 0.0;
	struct stat filestatus;
	

	for (int i = 1; i<=15; i++) {
		for (int j = 1; j<=nRefCountArray[i-1]; j++) {
			memset(strRefFilename, 0x00, 120);
			sprintf(strRefFilename, "%s%d%s%d%s", "E:\\TestVideo\\ForDecideSize\\Group", i, "\\ref", j, ".jpg");
			refImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);

			stat(strRefFilename, &filestatus);
			fRefSize = filestatus.st_size;
			fRefSize = fRefSize*1.0/1024;

			for (int k = 1; k<=nQueryCountArray[i-1]; k++) {
				memset(strQueryFilename, 0x00, 120);
				sprintf(strQueryFilename, "%s%d%s%d%s", "E:\\TestVideo\\ForDecideSize\\Group", i, "\\query\\image_", k, ".jpg");
				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);
				stat(strQueryFilename, &filestatus);
				fQuerySize = filestatus.st_size;
				fQuerySize = fQuerySize*1.0/1024;

				vector<DMatch> myMatches;

//				myMatches = myMatcher.DoMatching(refImage, queryImage, processTime);
				myMatches = myMatcher.DoMatching(refImage, queryImage, nFeatureNum, processTime, nNumKeypoint1, nNumKeypoint2, featureSize1, featureSize2);

				fSmallSize = fRefSize;
				if (fSmallSize > fQuerySize) fSmallSize = fQuerySize;

				myfile<<i<<","<<j<<","<<k<<","<<fRefSize<<","<<fQuerySize<<","<<myMatches.size()<<"\n";
				
				if (fSmallSize >= 8.0) {
					myfile2<<i<<","<<j<<","<<k<<","<<fSmallSize<<","<<myMatches.size()<<"\n";
				}

			}
		}
	}

	myfile.close();
	myfile2.close();

	return;

}


void MeasureMatching_forDifferentImage_RefQuery()
{
	char strRefFilename[120];
	char strQueryFilename[120];
	ofstream myfile1;
	ofstream myfile2;
	ofstream myfile3;

//	myfile1.open ("E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\allQ_260_withFinal.csv", ofstream::out | ofstream::app);

	myfile1.open ("F:\\forImageFeatureSize\\ORB_DifferentGroupRQ.csv", ofstream::out | ofstream::app);
	myfile2.open ("F:\\forImageFeatureSize\\ORB_DifferentGroupSmallerSizeRQ.csv", ofstream::out | ofstream::app);
	myfile3.open ("F:\\forImageFeatureSize\\ORB_DifferentGroupSmallerSizeOnlyRQ.csv", ofstream::out | ofstream::app);

	Mat queryImage;
	Mat refImage;
	Size matSizeRef;
	Size matSizeQuery;
	float fRefSize;  //KB
	float fQuerySize;  //KB
	SurfMatching myMatcher;
	int nFeatureNum = 1000;
	double processTime = 0.0;
	struct stat filestatus;
	double featureSize1 = 0.0;
	double featureSize2 = 0.0;
	int nNumKeypoint1;
	int nNumKeypoint2; 	
	double fSmallSize = 0.0;

	for (int i = 1; i<=60; i++) {
		memset(strRefFilename, 0x00, 120);
		//sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", i,  ".jpg");
///		sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\query\\query_", i, ".jpg");
		sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", i, ".jpg");

		refImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);

		stat(strRefFilename, &filestatus);
		fRefSize = filestatus.st_size;
		fRefSize = fRefSize*1.0/1024;

		for (int j = 1; j<=260; j++) {
			memset(strQueryFilename, 0x00, 120);
			sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\query\\query_", j, ".jpg");
//			sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", j, ".jpg");

			queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			stat(strQueryFilename, &filestatus);
			fQuerySize = filestatus.st_size;
			fQuerySize = fQuerySize*1.0/1024;

			vector<DMatch> myMatches;

			myMatches = myMatcher.DoMatching(refImage, queryImage, nFeatureNum, processTime, nNumKeypoint1, nNumKeypoint2, featureSize1, featureSize2);

			myfile1<<i<<","<<j<<","<<fRefSize<<","<<fQuerySize<<","<<myMatches.size()<<"\n";

			fSmallSize = fRefSize;
			if (fSmallSize > fQuerySize) fSmallSize = fQuerySize;

			myfile2<<i<<","<<j<<","<<fSmallSize<<","<<myMatches.size()<<"\n";

			if (fSmallSize <= 14.0 && fSmallSize >= 10.0) {
				myfile3<<i<<","<<j<<","<<fSmallSize<<","<<myMatches.size()<<"\n";			
			}

		}
	}

	myfile1.close();
	myfile2.close();
	myfile3.close();

	return;

}


void MeasureMatching_forDifferentImage()
{
	char strRefFilename[120];
	char strQueryFilename[120];
	ofstream myfile1;
	ofstream myfile2;
	ofstream myfile3;
	ofstream myfile4;

//	myfile1.open ("E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\allQ_260_withFinal.csv", ofstream::out | ofstream::app);

//	myfile1.open ("F:\\forImageFeatureSize\\ORB_DifferentGroup.csv", ofstream::out | ofstream::app);
	myfile2.open ("F:\\forImageFeatureSize\\ORB_DifferentGroupSmallerSizeSmallSet.csv", ofstream::out | ofstream::app);
//	myfile3.open ("F:\\forImageFeatureSize\\ORB_DifferentGroupSmallerSizeIn30KB.csv", ofstream::out | ofstream::app);
	myfile4.open ("F:\\forImageFeatureSize\\ORB_DifferentGroupSmallerSizeIn30KB_OnlyMatchedSmallSet.csv", ofstream::out | ofstream::app);

	Mat queryImage;
	Mat refImage;
	Size matSizeRef;
	Size matSizeQuery;
	float fRefSize;  //KB
	float fQuerySize;  //KB
	SurfMatching myMatcher;
	int nFeatureNum = 1000;
	double processTime = 0.0;
	struct stat filestatus;
	double featureSize1 = 0.0;
	double featureSize2 = 0.0;
	int nNumKeypoint1;
	int nNumKeypoint2; 	
	double fSmallSize = 0.0;

	for (int i = 1; i<=260; i++) {
		memset(strRefFilename, 0x00, 120);
		//sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", i,  ".jpg");
		sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\query\\query_", i, ".jpg");
//		sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", i, ".jpg");

		refImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);

		stat(strRefFilename, &filestatus);
		fRefSize = filestatus.st_size;
		fRefSize = fRefSize*1.0/1024;

		for (int j = 276; j<=280; j++) {
			memset(strQueryFilename, 0x00, 120);
			sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\query\\query_", j, ".jpg");
//			sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", j, ".jpg");

			queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			stat(strQueryFilename, &filestatus);
			fQuerySize = filestatus.st_size;
			fQuerySize = fQuerySize*1.0/1024;

			vector<DMatch> myMatches;

			myMatches = myMatcher.DoMatching(refImage, queryImage, nFeatureNum, processTime, nNumKeypoint1, nNumKeypoint2, featureSize1, featureSize2);

///			myfile1<<i<<","<<j<<","<<fRefSize<<","<<fQuerySize<<","<<myMatches.size()<<"\n";

			fSmallSize = fRefSize;
			if (fSmallSize > fQuerySize) fSmallSize = fQuerySize;

			myfile2<<i<<","<<j<<","<<fSmallSize<<","<<myMatches.size()<<"\n";

			if (fSmallSize <= 30.0) {

//			if (fSmallSize >= 10.0) {
///				myfile3<<i<<","<<j<<","<<fSmallSize<<","<<myMatches.size()<<"\n";
				if (myMatches.size() > 0) {
					myfile4<<i<<","<<j<<","<<fSmallSize<<","<<myMatches.size()<<"\n";
				}
			}

		}
	}

//	myfile1.close();
	myfile2.close();
//	myfile3.close();
	myfile4.close();

	return;

}
#endif

#if 0
void MeasureRatio()
{
	int nBaseDistantArray[] = {20, 30, 40, 60, 80, 100};
	char strRefFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat receivedImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;

	double processTime = 0.0;
				
	SurfMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	myfile.open ("E:\\TestVideo\\BigParking\\PhoneCameraFocalRatio.csv", ofstream::out | ofstream::app);

	// "E:\\TestVideo\\BigParking"
	//Base is Galaxy Nexus 1
	//Query Phone: Galaxy Nexus 3, iPhone 4S, NexusOne, WP
	for (int i=0; i<6; i++) {
		memset(strRefFilename, 0x00, 120);
		sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\BigParking\\GN1\\Rear_", nBaseDistantArray[i], "feet.jpg");
		baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);

		for (int j=1; j<=4; j++) {
			memset(strQueryFilename, 0x00, 120);
			if (j==1) {
				sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\BigParking\\GN3\\Rear_", nBaseDistantArray[i], "feet.jpg");
			} else if (j==2) {
				sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\BigParking\\iPhone4S\\Rear_", nBaseDistantArray[i], "feet.jpg");
			} else if (j==3) {
				sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\BigParking\\NexusOne\\Rear_", nBaseDistantArray[i], "feet.jpg");
			} else if (j==4) {
				sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\BigParking\\WP\\Rear_", nBaseDistantArray[i], "feet.jpg");
			}

			receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;

			myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, fMaxFeatureRatio, fAvgFeatureRatio);

			//Distance, Compared Phone(Galaxy Nexus 3, iPhone 4S, NexusOne, WP), Max Feature Ratio, Avg Feature Ratio
			myfile<<nBaseDistantArray[i]<<","<<j<<","<<fMaxFeatureRatio<<","<<fAvgFeatureRatio<<"\n";

		}

		
	}

			
	myfile.close();

	return;

}
#endif



void MatchingSeveralImage()
{
	char strFilenameBase[100];
	char strFilenameRecv[100];
	int distArr[] = {20, 30, 40, 60};
	int nMatchCount;
	int nAvgMatchCount;
	Mat baseImage;
	Mat receivedImage;

	ofstream myfile;

	Size matSizeRef;
	Size matSizeQuery;
	float fBaseSize = 0.0;  //KB
	float fReceivedSize = 0.0;  //KB
	SurfMatching myMatcher;
//	SiftMatching myMatcher;
	int nNumKeypoint1 = 0;
	int nNumKeypoint2 = 0; 
	double processTime = 0.0;
	struct stat filestatus;
	double featureSize1 = 0.0;
	double featureSize2 = 0.0;
	int nFeatureNum = 100;
	vector<DMatch> myMatches;
	double duration = 0.0; //Duration for image matching


	myfile.open ("F:\\forImageFeatureSize\\ORB_Several.csv", ofstream::out | ofstream::app);

	for(int i = 0; i<=3; i++) {
		memset(strFilenameBase, 0x00, 100);
		sprintf(strFilenameBase, "%s%d%s", "E:\\USC_Project\\Vehicle_Talk\\ForChooseMatchAlgorithm\\image\\Rear_", distArr[i], "feet.jpg");

		baseImage = imread(strFilenameBase, CV_LOAD_IMAGE_GRAYSCALE);
		stat(strFilenameBase, &filestatus);
		fBaseSize = filestatus.st_size;
		fBaseSize = fBaseSize*1.0/1024;

		for(int j = i; j<=3; j++) {
			processTime = 0.0;
			nNumKeypoint1 = 0;
			nNumKeypoint2 = 0;
			featureSize1 = 0.0;
			featureSize2 = 0.0;

			memset(strFilenameRecv, 0x00, 100);
			sprintf(strFilenameRecv, "%s%d%s","E:\\USC_Project\\Vehicle_Talk\\ForChooseMatchAlgorithm\\image\\Rear_", distArr[j], "feet.jpg");

			receivedImage = imread(strFilenameRecv, CV_LOAD_IMAGE_GRAYSCALE);
			stat(strFilenameRecv, &filestatus);
			fReceivedSize = filestatus.st_size;
			fReceivedSize = fReceivedSize*1.0/1024;
			
			duration = static_cast<double>(getTickCount());

			myMatches = myMatcher.DoMatching(baseImage, receivedImage, nFeatureNum, processTime, nNumKeypoint1, nNumKeypoint2, featureSize1, featureSize2);
			
			duration = static_cast<double>(getTickCount())-duration;
			duration /= getTickFrequency(); // the elapsed time in s
			duration = duration *1000.0; //the elapsed time in ms

			myfile<<nFeatureNum<<","<<duration<<",,"<<fBaseSize<<","<<nNumKeypoint1<<","<<featureSize1/1024<<",,"<<fReceivedSize<<","<<nNumKeypoint2<<","<<featureSize2/1024<<",,"<<myMatches.size()<<"\n";

		}
	}

	myfile.close();

	return;
}



void MatchingTwoImage()
{
	char strRefFilename[120];
	char strQueryFilename[120];
//	String baseImageFile = "F:\\forImageFeatureSize\\GN.jpg";
//	String receivedImageFile = "F:\\forImageFeatureSize\\i4S.jpg";
//	String baseImageFile = "E:\\USC_Project\\Vehicle_Talk\\ForChooseMatchAlgorithm\\image\\Rear_20feet.jpg";
//	String receivedImageFile = "E:\\USC_Project\\Vehicle_Talk\\ForChooseMatchAlgorithm\\image\\Rear_30feet.jpg";
	String baseImageFile = "F:\\ForDiversityFrame\\scene164\\1.jpg";
	String receivedImageFile = "F:\\ForDiversityFrame\\scene164\\6.jpg";

	//ofstream myfile;

	//myfile.open ("F:\\forImageFeatureSize\\Size_MatchedPoints_ORB.csv", ofstream::out | ofstream::app);
	int nFeatureNum = 2000;
	Mat queryImage;
	Mat refImage;
	Size matSizeRef;
	Size matSizeQuery;
	float fRefSize = 0.0;  //KB
	float fQuerySize = 0.0;  //KB
	SurfMatching myMatcher;
//	SiftMatching myMatcher;
	int nNumKeypoint1 = 0;
	int nNumKeypoint2 = 0; 
	double processTime = 0.0;
	struct stat filestatus;
	double featureSize1 = 0.0;
	double featureSize2 = 0.0;
	
	refImage = imread(baseImageFile, CV_LOAD_IMAGE_GRAYSCALE);

	stat(baseImageFile.c_str(), &filestatus);
	fRefSize = filestatus.st_size;
	fRefSize = fRefSize*1.0/1024;

	queryImage = imread(receivedImageFile, CV_LOAD_IMAGE_GRAYSCALE);
	stat(receivedImageFile.c_str(), &filestatus);
	fQuerySize = filestatus.st_size;
	fQuerySize = fQuerySize*1.0/1024;

	vector<DMatch> myMatches;

	double duration = 0.0; //Duration for image matching
	duration = static_cast<double>(getTickCount());

	myMatches = myMatcher.DoMatching(refImage, queryImage, nFeatureNum, processTime, nNumKeypoint1, nNumKeypoint2, featureSize1, featureSize2);
//	myMatches = myMatcher.DoMatching(refImage, queryImage, processTime);

	duration = static_cast<double>(getTickCount())-duration;
	duration /= getTickFrequency(); // the elapsed time in s
	duration = duration *1000.0; //the elapsed time in ms

	//myfile<<1000<<","<<duration<<","<<fRefSize<<","<<nNumKeypoint1<<","<<featureSize1/1024<<","<<fQuerySize<<","<<nNumKeypoint2<<","<<featureSize2/1014<<","<<myMatches.size()<<"\n";

	cout<<"MatchePoint====="<<myMatches.size()<<endl;

	//myfile.close();

	return;

}



String baseImageFile = "F:\\forImageFeatureSize\\GN.jpg";
//String baseImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_30feet.png";
//String receivedImageFile = "E:\\TestVideo\ForPaper\\SameCar2.jpg";
//String receivedImageFile = "E:\\TestVideo\\ForPaper\\Self3.jpg";
//String receivedImageFile = "E:\\TestVideo\\ForPaper\\t3.jpg";
//String receivedImageFile = "E:\\TestVideo\\ForPaper\\Other4.jpg";
//String receivedImageFile = "F:\\tmp\\tt\\car1.jpg";
String receivedImageFile = "F:\\forImageFeatureSize\\i4S.jpg";
//String receivedImageFile = "F:\\tmp\\tt\\car4.jpg";
//String receivedImageFile = "F:\\tmp\\tt\\car5.jpg";
//String receivedImageFile = "F:\\tmp\\tt\\car6.jpg";


String folderBase = "E:\\TestVideo\\TestAccuracy\\Car1_HondaOdyssey1217";
String videoFileBase = "E:\\TestVideo\\TestAccuracy\\Car1_HondaOdyssey1217\\OriginalData";



int main()
{
	cout<<"Begin..............."<<endl;
	//MatchingSeveralImage();
//	MeasureMatching_forDifferentImage_RefQuery();
//	MeasureMatching_forDifferentImage();
	//MeasureMatching_SpecialVersion();

	MatchingTwoImage();
//	MeasureRatio();


	///MeasureMatching();   //For deciding image size

	//	MeasureMatching_forDifferentImage();
	cout<<"End..............."<<endl;

	getchar();

	return 0;

//####	ExtractImgFromVideo();
//####	return 0;

///Dictionary///Begin//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//to store the input file names
	char * filename = new char[100];  

//	Mat baseImage = imread(baseImageFile, CV_LOAD_IMAGE_GRAYSCALE);
//	Mat receivedImage = imread(receivedImageFile, CV_LOAD_IMAGE_GRAYSCALE);
	Mat baseImage;
	Mat receivedImage;

#if 0
	//to store the current input image
	Mat input;  

	//To store the keypoints that will be extracted by SIFT
	vector<KeyPoint> keypoints;
	//To store the SIFT descriptor of current image
	Mat descriptor;
	//To store all the descriptors that are extracted from all the images.
	Mat featuresUnclustered;

	OrbDescriptorExtractor detector;

	for(int f=1;f<=406;f++){        
		//create the file name of an image
		sprintf(filename,"E:\\TestVideo\\MeasureTimeOnPhone_SizeInRange\\query_%d.jpg",f);
		//open the file
		input = imread(filename, CV_LOAD_IMAGE_GRAYSCALE); //Load as grayscale                
		//detect feature points
		detector.detect(input, keypoints);
		//compute the descriptors for each keypoint
		detector.compute(input, keypoints,descriptor);        
		//put the all feature descriptors in a single Mat object 
		featuresUnclustered.push_back(descriptor);        
		//print the percentage
		printf("%f percent done\n",f*1.0*100/406);
	}    

	//Construct BOWKMeansTrainer
	//the number of bags
	int dictionarySize=800;
	//define Term Criteria
	TermCriteria tc(CV_TERMCRIT_ITER,100,0.001);
	//retries number
	int retries=1;
	//necessary flags
	int flags=KMEANS_PP_CENTERS;
	//Create the BoW (or BoF) trainer
	BOWKMeansTrainer bowTrainer(dictionarySize,tc,retries,flags);
	//cluster the feature vectors
	//convert featuresUnclustered to type CV_32F
	Mat featuresUnclusteredF(featuresUnclustered.rows,featuresUnclustered.cols,CV_32F);
	featuresUnclustered.convertTo(featuresUnclusteredF,CV_32F);
	//cluster the feature vectors
	Mat dictionary=bowTrainer.cluster(featuresUnclusteredF); 
	
	//store the vocabulary
	FileStorage fs("F:\\tmp\\tt\\dictionaryORB800.yml", FileStorage::WRITE);
	fs << "vocabulary" << dictionary;
	fs.release();
#endif
///Dictionary///End//////////////////////////////////////////////////////////////////////////////////////////////////////////////

///Get Image cluster index and position ///Begin//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat dictionaryF;
    FileStorage fs1("F:\\tmp\\tt\\Dict\\DictORB1600.yml", FileStorage::READ);

//	Mat dictionaryA; 
//    FileStorage fs("F:\\tmp\\tt\\dictionarySURF800.yml", FileStorage::READ);
//	FileStorage fs("F:\\tmp\\tt\\dictionarySIFT1600.yml", FileStorage::READ);
//	FileStorage fs("F:\\tmp\\tt\\Dict\\DictORB3200.yml", FileStorage::READ);

///	fs["vocabulary"] >> dictionaryA;
//    fs.release();    

    fs1["vocabulary"] >> dictionaryF;
    fs1.release();    
    
	//convert to 8bit unsigned format
	Mat dictionaryA(dictionaryF.rows,dictionaryF.cols,CV_8U);
	dictionaryF.convertTo(dictionaryA, CV_8U); 
	//create a matcher with BruteForce-Hamming distance
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
//	Ptr<DescriptorMatcher> matcher(new BFMatcher(NORM_L2));
//    Ptr<DescriptorMatcher> matcher(new FlannBasedMatcher);

	//	BFMatcher matcher(NORM_L2);

    //create Orb feature point extracter
    Ptr<FeatureDetector> detectorP(new OrbFeatureDetector(1000, 1.2, 5));
    Ptr<DescriptorExtractor> extractor(new OrbDescriptorExtractor);    
//    Ptr<FeatureDetector> detectorP(new SiftFeatureDetector());
//    Ptr<DescriptorExtractor> extractor(new SiftDescriptorExtractor);   
//    Ptr<FeatureDetector> detectorP(new SurfFeatureDetector());
//   Ptr<DescriptorExtractor> extractor(new SurfDescriptorExtractor);    

	//create BoF (or BoW) descriptor extractor
    BOWImgDescriptorExtractor bowDE(extractor, matcher);
    //Set the dictionary with the vocabulary we created in the first step
    bowDE.setVocabulary(dictionaryA);
 
	Mat bowDescriptor1;
    
//	memset(filename, 0x00, 100);
	//the image file with the location. change it according to your image file location
//	sprintf(filename,"F:\\tmp\\tt\\car2.jpg");        

	//read the image
	baseImage=imread(baseImageFile,CV_LOAD_IMAGE_GRAYSCALE);

	int widthBase = baseImage.cols;
	//To store the keypoints that will be extracted by SIFT
	vector<KeyPoint> keypoints1;        
	//Detect SIFT keypoints (or feature points)
	detectorP->detect(baseImage, keypoints1);
	//To store the BoW (or BoF) representation of the image
	//Mat bowDescriptor;        
	vector<vector<int>> myvec1;
	Mat dess1;

	vector<KeyPoint> keypoints11, keypoints22; //////////////////

	//extract BoW (or BoF) descriptor from given image
	bowDE.compute(baseImage, keypoints1, bowDescriptor1, &myvec1, &dess1);
 
	Mat descriptors1;
	vector<Point2f> points1;

	vector<vector<int>>::iterator u;
	vector<int>::iterator v;
	int cnt = 0;
	for(u = myvec1.begin(); u != myvec1.end(); u++)
	{
		for(v = (*u).begin(); v != (*u).end(); v++)
		{
			//cout<<"CNT=" <<cnt << "     ,Index="<<*v<<endl;
			descriptors1.push_back(dictionaryA.row(cnt));
			float x = keypoints1[*v].pt.x;
			float y = keypoints1[*v].pt.y;
			points1.push_back(Point2f(x,y));
			//cout <<"X:" <<x <<"   Y:" <<y<<endl;
			//getchar();
			keypoints11.push_back(KeyPoint(x, y, keypoints1[*v].size));
		}

		cnt = cnt + 1;
		
	}

//	cout<<"CNT1===="<<cnt<<endl;

	//getchar();




	Mat bowDescriptor2;

//	memset(filename, 0x00, 100);

	//the image file with the location. change it according to your image file location
//	sprintf(filename,"F:\\tmp\\tt\\car4.jpg");        

	//read the image
	receivedImage=imread(receivedImageFile,CV_LOAD_IMAGE_GRAYSCALE);        
	//To store the keypoints that will be extracted by SIFT
	vector<KeyPoint> keypoints2;        
	//Detect SIFT keypoints (or feature points)
	detectorP->detect(receivedImage, keypoints2);
	//To store the BoW (or BoF) representation of the image
	//Mat bowDescriptor;        
	vector<vector<int>> myvec2;
	Mat dess2;

	//extract BoW (or BoF) descriptor from given image
	bowDE.compute(receivedImage, keypoints2, bowDescriptor2, &myvec2, &dess2);
 
	Mat descriptors2;
	vector<Point2f> points2;

//	vector<vector<int>>::iterator u;
//	vector<int>::iterator v;
	cnt = 0;
	for(u = myvec2.begin(); u != myvec2.end(); u++)
	{
		for(v = (*u).begin(); v != (*u).end(); v++)
		{
			descriptors2.push_back(dictionaryA.row(cnt));
			float x = keypoints2[*v].pt.x;
			float y = keypoints2[*v].pt.y;
			points2.push_back(Point2f(x,y));
			if (y > 75 && y < 77) {
				cout <<"==========[" << *v <<"]=========X:" <<x <<"   Y:" <<y<<endl;
			}

			keypoints22.push_back(KeyPoint(x, y, keypoints2[*v].size));

		}

		cnt = cnt + 1;
		
	}

//	cout<<"CNT2===="<<cnt<<endl;







///Get Image cluster index and position ///End//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//	MeasureRatio();
//	return 0;
//	MeasureMatching();
//	MeasureMatching_forDifferentImage();
//	return 0;

#if 1
///////	Mat baseImage = imread(baseImageFile);
//////	Mat receivedImage = imread(receivedImageFile);
//	Mat baseImage = imread(baseImageFile, CV_LOAD_IMAGE_GRAYSCALE);
//	Mat receivedImage = imread(receivedImageFile, CV_LOAD_IMAGE_GRAYSCALE);

	//Convert to grayscale
	//cvtColor(baseImage, baseImage, CV_BGR2GRAY);
	//cvtColor(receivedImage, receivedImage, CV_BGR2GRAY);


	/////////////////////////////////////////////////////////
#if 1
	//Matching with Surf
	SurfMatching myMatcher;
	vector<DMatch> myMatches;
#else
	//Matching with Sift
	SiftMatching myMatcher;
	vector<DMatch> myMatches;
#endif

	double processTime = 0.0;
	double duration; //Duration for image matching
	duration = static_cast<double>(getTickCount());

//	myMatches = myMatcher.DoMatching(baseImage, receivedImage);
//	myMatches = myMatcher.DoMatching(baseImage, baseImage);

//	myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime);
///	myMatches = myMatcher.DoMatching_Special(baseImage, receivedImage, keypoints1, keypoints2, descriptors1, descriptors2, points1, points2, widthBase, processTime);
	myMatches = myMatcher.DoMatching_Special(baseImage, receivedImage, keypoints11, keypoints22, descriptors1, descriptors2, widthBase, processTime);



//	myMatches = myMatcher.DoMatchingSimple(baseImage, receivedImage);

	duration = static_cast<double>(getTickCount())-duration;
	duration /= getTickFrequency(); // the elapsed time in s

	double fDistance = 0.0;
	double fDistance20 = 0.0;
	for(int i = 0; i<myMatches.size(); i++) {
		fDistance = fDistance + myMatches.at(i).distance;
		if (i<20) {
			fDistance20 = fDistance20 + myMatches.at(i).distance;
		}
	}
	cout<<"##########################################"<<endl;
	cout<<"Matched:"	<<myMatches.size()<<endl;
	cout<<"Total Distance:	"<<fDistance<<endl;
	cout<<"Total First 20 Distance:	"<<fDistance20<<endl;
	cout<<"Total processing time:	"<<	duration*1000.0 <<"	ms"<<endl;
	cout<<"Process Time:	"<<processTime*1000.0<<"	ms"<<endl;

	getchar();

	return 0;
#endif
}




#if 0
	Mat image = imread(selfTakeImage);
	vector<KeyPoint> keypointsSurf, keypointsSift;
	Mat featureImageSurf, featureImageSift;
	double durationSurf, durationSift; 

	//SURF method
//	SurfFeatureDetector surf(400.);
	SurfFeatureDetector surf; //All default parameters

	durationSurf = static_cast<double>(getTickCount());
	surf.detect(image, keypointsSurf);
	durationSurf = static_cast<double>(getTickCount())-durationSurf;
	durationSurf /= getTickFrequency();

	drawKeypoints(image, keypointsSurf, featureImageSurf, Scalar(0,255,0), DrawMatchesFlags::DEFAULT);

	namedWindow("SURF");
	imshow("SURF",featureImageSurf);
	
	//SIFT method
//	SiftFeatureDetector sift(0.03, 10.);
	SiftFeatureDetector sift; //All default parameters

	durationSift = static_cast<double>(getTickCount());
	sift.detect(image, keypointsSift);
	durationSift = static_cast<double>(getTickCount())-durationSift;
	durationSift /= getTickFrequency();

	drawKeypoints(image, keypointsSift, featureImageSift, Scalar(0,255,0), DrawMatchesFlags::DEFAULT);

	namedWindow("SIFT");
	imshow("SIFT",featureImageSift);

	cout<<"SURF Feature Points:	"<<keypointsSurf.size()<<endl;
	cout<<"SIFT Feature Points:	"<<keypointsSift.size()<<endl;
	cout<<endl;
	cout<<"SURF Time:	"<<durationSurf*1000.0<<"	ms"<<endl;
	cout<<"SIFT Time:	"<<durationSift*1000.0<<"	ms"<<endl;

	waitKey(30000);

	return 0;

#endif
