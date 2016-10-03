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

String sPlace = "D:\\TestAccuracy_201405\\";


void ExtractImageFromVideo_ForOnePhone_GN(int nCarStartIdx, int nCarEndIdx, int nDirectionStart, int nDirectionEnd)
{
	Mat originalFrame;
	char strVideoFilename[120];
	char strImageFilename[120];
	char strFrameFolder[120];

	int nFrameCount;
	int i,j, k, jj;
	int nIdx;
	int nDistance;

	for (i=nCarStartIdx; i<=nCarEndIdx; i++) {  // Car numbers

		for (j=nDirectionStart; j<=nDirectionEnd; j++) {  // Three directions
			memset(strFrameFolder, 0x00, 120);
			if (j==1) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GN\\B_Frames");
			} else if (j==2) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GN\\L_Frames");			
			} else if (j==3) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GN\\R_Frames");
			}
			mkdir(strFrameFolder);

			for (k=1; k<=10; k++) {  // Distance Index
				nDistance = k*5;

				memset(strVideoFilename, 0x00, 120);
				if (j==1) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GN\\B", nDistance, ".mp4");
				} else if (j==2) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GN\\L", nDistance, ".mp4");				
				} else if (j==3) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GN\\R", nDistance, ".mp4");
				}

				VideoCapture captureDevice1(strVideoFilename);
				nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

				nIdx = 0;
				jj = 0;

				while(true) {
					//capture a new image frame        
					if (!captureDevice1.read(originalFrame)) break;
					jj = jj + 1;

					if (jj % 15 == 0) {
						nIdx = nIdx + 1;
						memset(strImageFilename, 0x00, 120);
						if (j==1) { 
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\B_", nDistance, "_org_", nIdx,".jpg");
						} else if (j==2) {
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\L_", nDistance, "_org_", nIdx,".jpg");
						} else if (j==3) {
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\R_", nDistance, "_org_", nIdx,".jpg");
						}
						imwrite(strImageFilename, originalFrame);


						if (nIdx == 3) {
							memset(strImageFilename, 0x00, 120);
							if (j==1) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\Rear\\", nDistance, "\\GN_org.jpg");
							} else if (j==2) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\L30\\", nDistance, "\\GN_org.jpg");
							} else if (j==3) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\R30\\", nDistance, "\\GN_org.jpg");							
							}
							imwrite(strImageFilename, originalFrame);
						}

					}
					
				}
			}
		}
	}

}


void ExtractImageFromVideo_ForOnePhone_GN1(int nCarStartIdx, int nCarEndIdx, int nDirectionStart, int nDirectionEnd)
{
	Mat originalFrame;
	char strVideoFilename[120];
	char strImageFilename[120];
	char strFrameFolder[120];

	int nFrameCount;
	int i,j, k, jj;
	int nIdx;
	int nDistance;

	for (i=nCarStartIdx; i<=nCarEndIdx; i++) {  // Car numbers

		for (j=nDirectionStart; j<=nDirectionEnd; j++) {  // Three directions
			memset(strFrameFolder, 0x00, 120);
			if (j==1) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GN1\\B_Frames");
			} else if (j==2) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GN1\\L_Frames");			
			} else if (j==3) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GN1\\R_Frames");
			}
			mkdir(strFrameFolder);

			for (k=1; k<=10; k++) {  // Distance Index
				nDistance = k*5;

				memset(strVideoFilename, 0x00, 120);
				if (j==1) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GN1\\B", nDistance, ".mp4");
				} else if (j==2) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GN1\\L", nDistance, ".mp4");				
				} else if (j==3) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GN1\\R", nDistance, ".mp4");
				}

				VideoCapture captureDevice1(strVideoFilename);
				nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

				nIdx = 0;
				jj = 0;

				while(true) {
					//capture a new image frame        
					if (!captureDevice1.read(originalFrame)) break;
					jj = jj + 1;

					if (jj % 15 == 0) {
						nIdx = nIdx + 1;
						memset(strImageFilename, 0x00, 120);
						if (j==1) { 
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\B_", nDistance, "_org_", nIdx,".jpg");
						} else if (j==2) {
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\L_", nDistance, "_org_", nIdx,".jpg");
						} else if (j==3) {
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\R_", nDistance, "_org_", nIdx,".jpg");
						}
						imwrite(strImageFilename, originalFrame);


						if (nIdx == 3) {
							memset(strImageFilename, 0x00, 120);
							if (j==1) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\Rear\\", nDistance, "\\GN1_org.jpg");
							} else if (j==2) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\L30\\", nDistance, "\\GN1_org.jpg");
							} else if (j==3) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\R30\\", nDistance, "\\GN1_org.jpg");							
							}
							imwrite(strImageFilename, originalFrame);
						}

					}
					
				}
			}
		}
	}

}



void ExtractImageFromVideo_ForOnePhone_GS4(int nCarStartIdx, int nCarEndIdx, int nDirectionStart, int nDirectionEnd)
{
	Mat originalFrame;
	char strVideoFilename[120];
	char strImageFilename[120];
	char strFrameFolder[120];

	int nFrameCount;
	int i,j, k, jj;
	int nIdx;
	int nDistance;

	for (i=nCarStartIdx; i<=nCarEndIdx; i++) {  // Car numbers

		for (j=nDirectionStart; j<=nDirectionEnd; j++) {  // Three directions
			memset(strFrameFolder, 0x00, 120);
			if (j==1) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GS4\\B_Frames");
			} else if (j==2) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GS4\\L_Frames");			
			} else if (j==3) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\GS4\\R_Frames");
			}
			mkdir(strFrameFolder);

			for (k=1; k<=10; k++) {  // Distance Index
				nDistance = k*5;

				memset(strVideoFilename, 0x00, 120);
				if (j==1) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GS4\\B", nDistance, ".mp4");
				} else if (j==2) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GS4\\L", nDistance, ".mp4");				
				} else if (j==3) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\GS4\\R", nDistance, ".mp4");
				}

				VideoCapture captureDevice1(strVideoFilename);
				nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

				nIdx = 0;
				jj = 0;

				while(true) {
					//capture a new image frame        
					if (!captureDevice1.read(originalFrame)) break;
					jj = jj + 1;

					if (jj % 15 == 0) {
						nIdx = nIdx + 1;
						memset(strImageFilename, 0x00, 120);
						if (j==1) { 
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\B_", nDistance, "_org_", nIdx,".jpg");
						} else if (j==2) {
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\L_", nDistance, "_org_", nIdx,".jpg");
						} else if (j==3) {
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\R_", nDistance, "_org_", nIdx,".jpg");
						}
						imwrite(strImageFilename, originalFrame);


						if (nIdx == 3) {
							memset(strImageFilename, 0x00, 120);
							if (j==1) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\Rear\\", nDistance, "\\GS4_org.jpg");
							} else if (j==2) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\L30\\", nDistance, "\\GS4_org.jpg");
							} else if (j==3) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\R30\\", nDistance, "\\GS4_org.jpg");							
							}
							imwrite(strImageFilename, originalFrame);
						}

					}
					
				}
			}
		}
	}

}


void ExtractImageFromVideo_ForOnePhone_I4S(int nCarStartIdx, int nCarEndIdx, int nDirectionStart, int nDirectionEnd)
{
	Mat originalFrame;
	char strVideoFilename[120];
	char strImageFilename[120];
	char strFrameFolder[120];

	int nFrameCount;
	int i,j, k, jj;
	int nIdx;
	int nDistance;

	for (i=nCarStartIdx; i<=nCarEndIdx; i++) {  // Car numbers

		for (j=nDirectionStart; j<=nDirectionEnd; j++) {  // Three directions
			memset(strFrameFolder, 0x00, 120);
			if (j==1) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\I4S\\B_Frames");
			} else if (j==2) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\I4S\\L_Frames");			
			} else if (j==3) {
				sprintf(strFrameFolder, "%s%s%d%s",  sPlace.c_str(), "Car_", i, "\\Video\\I4S\\R_Frames");
			}
			mkdir(strFrameFolder);

			for (k=1; k<=10; k++) {  // Distance Index
				nDistance = k*5;

				memset(strVideoFilename, 0x00, 120);
				if (j==1) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\I4S\\B", nDistance, ".MOV");
				} else if (j==2) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\I4S\\L", nDistance, ".MOV");				
				} else if (j==3) {
					sprintf(strVideoFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", i, "\\Video\\I4S\\R", nDistance, ".MOV");
				}

				VideoCapture captureDevice1(strVideoFilename);
				nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

				nIdx = 0;
				jj = 0;

				while(true) {
					//capture a new image frame        
					if (!captureDevice1.read(originalFrame)) break;
					jj = jj + 1;

					if (jj % 15 == 0) {
						nIdx = nIdx + 1;
						memset(strImageFilename, 0x00, 120);
						if (j==1) { 
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\B_", nDistance, "_org_", nIdx,".jpg");
						} else if (j==2) {
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\L_", nDistance, "_org_", nIdx,".jpg");
						} else if (j==3) {
							sprintf(strImageFilename, "%s%s%d%s%d%s", strFrameFolder, "\\R_", nDistance, "_org_", nIdx,".jpg");
						}
						imwrite(strImageFilename, originalFrame);


						if (nIdx == 3) {
							memset(strImageFilename, 0x00, 120);
							if (j==1) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\Rear\\", nDistance, "\\I4S_org.jpg");
							} else if (j==2) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\L30\\", nDistance, "\\I4S_org.jpg");
							} else if (j==3) {
								sprintf(strImageFilename, "%s%s%d%s%d%s",  sPlace.c_str(),  "Car_" , i,  "\\R30\\", nDistance, "\\I4S_org.jpg");							
							}
							imwrite(strImageFilename, originalFrame);
						}

					}
					
				}
			}
		}
	}

}


void ExtractImageFromVideo()
{
	int nCarStartIdx = 11;
	int nCarEndIdx = 12;

	int nDirectionStart = 1;
	int nDirectionEnd = 3;

	cout<<"Beginning Extract frames from video......"<<endl;
	ExtractImageFromVideo_ForOnePhone_GN(nCarStartIdx, nCarEndIdx, nDirectionStart, nDirectionEnd);
	ExtractImageFromVideo_ForOnePhone_GN1(nCarStartIdx, nCarEndIdx, nDirectionStart, nDirectionEnd);
	ExtractImageFromVideo_ForOnePhone_GS4(nCarStartIdx, nCarEndIdx, nDirectionStart, nDirectionEnd);
	ExtractImageFromVideo_ForOnePhone_I4S(nCarStartIdx, nCarEndIdx, nDirectionStart, nDirectionEnd);
	cout<<"Extract frames Finished!!!!"<<endl;
}



void CalculateFocalRatio_GN1_GN()
{
	char strResult[120];
	char strBaseFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat queryImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;

	int nMatchedCount = 0;
	int nNumKeypoint1, nNumKeypoint2;
	int narrRatioGroup[] = {4, 5};
	int nRatioGroupCnt = sizeof(narrRatioGroup)/sizeof(int);

	int i,j,k;
	int nDistance;
	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", sPlace.c_str(), "Result\\Ratio\\", "ratio_GN1_GN.csv");
	myfile.open (strResult, ofstream::out | ofstream::app);

	for (i=0; i<nRatioGroupCnt; i++) {
		for (j=1; j<=3; j++) {
			for (k=1; k<=10; k++) {
				nDistance = k*5;
				
				memset(strBaseFilename, 0x00, 120);
				memset(strQueryFilename, 0x00, 120);

				if (j==1) { //Rear
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\Rear\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\Rear\\", nDistance, "\\GN.jpg");
				} else if (j==2) {
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\L30\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\L30\\", nDistance, "\\GN.jpg");				
				} else if (j==3) {
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\R30\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\R30\\", nDistance, "\\GN.jpg");				
				}

				baseImage = imread(strBaseFilename, CV_LOAD_IMAGE_GRAYSCALE);
				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				myMatches = myMatcher.DoMatching_Fixed(baseImage, queryImage, nNumKeypoint1, nNumKeypoint2, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);
				myfile << j << "," << nDistance << "," << myMatches.size() << "," << fMaxFeatureRatio << "," << fAvgFeatureRatio << "," << fEuDistRatio << "\n";

			}

		}
	}

	myfile.close();

}



void CalculateFocalRatio_GN1_GS4()
{
	char strResult[120];
	char strBaseFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat queryImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;
	struct stat filestatus;
	int nMatchedCount = 0;
	int nNumKeypoint1, nNumKeypoint2;
	int narrRatioGroup[] = {4, 5, 7};
	int nRatioGroupCnt = sizeof(narrRatioGroup)/sizeof(int);

	int i,j,k;
	int nDistance;
	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", sPlace.c_str(), "Result\\Ratio\\", "ratio_GN1_GS4.csv");
	myfile.open (strResult, ofstream::out | ofstream::app);

	for (i=0; i<nRatioGroupCnt; i++) {
		for (j=1; j<=3; j++) {
			for (k=1; k<=10; k++) {
				nDistance = k*5;
				
				memset(strBaseFilename, 0x00, 120);
				memset(strQueryFilename, 0x00, 120);

				if (j==1) { //Rear
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\Rear\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\Rear\\", nDistance, "\\GS4.jpg");
				} else if (j==2) {
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\L30\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\L30\\", nDistance, "\\GS4.jpg");				
				} else if (j==3) {
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\R30\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\R30\\", nDistance, "\\GS4.jpg");				
				}

				if (stat(strQueryFilename, &filestatus) != 0) {  //File does not exist
					continue;
				}

				baseImage = imread(strBaseFilename, CV_LOAD_IMAGE_GRAYSCALE);


				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				myMatches = myMatcher.DoMatching_Fixed(baseImage, queryImage, nNumKeypoint1, nNumKeypoint2, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);
				myfile << j << "," << nDistance << "," << myMatches.size() << "," << fMaxFeatureRatio << "," << fAvgFeatureRatio << "," << fEuDistRatio << "\n";

			}

		}
	}

	myfile.close();


}


void CalculateFocalRatio_GN1_I4S()
{
	char strResult[120];
	char strBaseFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat queryImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;

	int nMatchedCount = 0;
	int nNumKeypoint1, nNumKeypoint2;
	int narrRatioGroup[] = {4, 5};
	int nRatioGroupCnt = sizeof(narrRatioGroup)/sizeof(int);

	int i,j,k;
	int nDistance;
	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", sPlace.c_str(), "Result\\Ratio\\", "ratio_GN1_I4S.csv");
	myfile.open (strResult, ofstream::out | ofstream::app);

	for (i=0; i<nRatioGroupCnt; i++) {
		for (j=1; j<=3; j++) {
			for (k=1; k<=10; k++) {
				nDistance = k*5;
				
				memset(strBaseFilename, 0x00, 120);
				memset(strQueryFilename, 0x00, 120);

				if (j==1) { //Rear
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\Rear\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\Rear\\", nDistance, "\\I4S.jpg");
				} else if (j==2) {
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\L30\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\L30\\", nDistance, "\\I4S.jpg");				
				} else if (j==3) {
					sprintf(strBaseFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\R30\\", nDistance, "\\GN1.jpg");
					sprintf(strQueryFilename, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrRatioGroup[i], "\\R30\\", nDistance, "\\I4S.jpg");				
				}

				baseImage = imread(strBaseFilename, CV_LOAD_IMAGE_GRAYSCALE);
				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				myMatches = myMatcher.DoMatching_Fixed(baseImage, queryImage, nNumKeypoint1, nNumKeypoint2, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);
				myfile << j << "," << nDistance << "," << myMatches.size() << "," << fMaxFeatureRatio << "," << fAvgFeatureRatio << "," << fEuDistRatio << "\n";

			}

		}
	}

	myfile.close();

}



void CalculateFocalRatio()
{
	cout<<"Beginnning calculating Focal Ratio......"<<endl;
	//CalculateFocalRatio_GN1_GN();
	CalculateFocalRatio_GN1_GS4();
	//CalculateFocalRatio_GN1_I4S();
	cout<<"Calcualte focal ratio Finished!!!!"<<endl;
}



void CalculateDistance_GN3_GNS(int nSelfImageScaled)
{
	float fFocalRatio_GN3_GNS = 1.000;
	int narrCarGroup[] = {15,16};
	int nCarGroupCnt = sizeof(narrCarGroup)/sizeof(int);
	char strResult[120];
	char strSelfFilename[120];
	char strQueryFilename[120];
	Mat selfImage;
	Mat queryImage;
	int nQueryDistance;
	int nSelfDistance;

	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;

	int nMatchedCount = 0;
	int nNumKeypoint1, nNumKeypoint2;

	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;
	int i,j,k,m;

	memset(strResult, 0x00, 120);
	if (nSelfImageScaled == 0) {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_AllDistance\\GN3_GNS.csv");
	} else {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_Scaled\\GN3_GNS.csv");	
	}

	myfile.open (strResult, ofstream::out | ofstream::app);

	for (i=0; i<nCarGroupCnt; i++) {
		for (j=1; j<=3; j++) {
			for (k=1; k<=5; k++) {
				nQueryDistance = k;
				memset(strQueryFilename, 0x00, 120);
				
				if (j==1) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nQueryDistance, "\\GNS.jpg");
				} else if (j==2) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nQueryDistance, "\\GNS.jpg");				
				} else if (j==3) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nQueryDistance, "\\GNS.jpg");
				}

				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);


				for (m=1; m<=5; m++) {
					nSelfDistance = m;
					memset(strSelfFilename, 0x00, 120);
					if (j==1) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN3.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN3_scaled.jpg");						
						}
					} else if (j==2) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN3.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN3_scaled.jpg");						
						}
					} else if (j==3) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN3.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN3_scaled.jpg");						
						}
					}

					selfImage = imread(strSelfFilename, CV_LOAD_IMAGE_GRAYSCALE);

					myMatches = myMatcher.DoMatching_Fixed(selfImage, queryImage, nNumKeypoint1, nNumKeypoint2, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

					// Ground truth, matched self image distance (Z0), direction, matched count, average ratio (w0/wNew) 
					myfile << nQueryDistance << "," << nSelfDistance << "," << j << "," << myMatches.size() << "," << fAvgFeatureRatio << "\n";
				}
			}

		}
	}


	myfile.close();


}




void CalculateDistance_GN1_GN(int nSelfImageScaled)
{
	float fFocalRatio_GN1_GN = 1.000;
	int narrCarGroup[] = {1, 2, 3, 6, 7, 8, 9, 10, 11, 12};
	int nCarGroupCnt = sizeof(narrCarGroup)/sizeof(int);
	char strResult[120];
	char strSelfFilename[120];
	char strQueryFilename[120];
	Mat selfImage;
	Mat queryImage;
	int nQueryDistance;
	int nSelfDistance;

	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;

	int nMatchedCount = 0;
	int nNumKeypoint1, nNumKeypoint2;

	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;
	int i,j,k,m;

	memset(strResult, 0x00, 120);
	if (nSelfImageScaled == 0) {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_AllDistance\\GN1_GN.csv");
	} else {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_Scaled\\GN1_GN.csv");	
	}

	myfile.open (strResult, ofstream::out | ofstream::app);

	for (i=0; i<nCarGroupCnt; i++) {
		for (j=1; j<=3; j++) {
			for (k=1; k<=10; k++) {
				nQueryDistance = k*5;
				memset(strQueryFilename, 0x00, 120);
				
				if (j==1) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nQueryDistance, "\\GN.jpg");
				} else if (j==2) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nQueryDistance, "\\GN.jpg");				
				} else if (j==3) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nQueryDistance, "\\GN.jpg");
				}

				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);


				for (m=1; m<=10; m++) {
					nSelfDistance = m*5;
					memset(strSelfFilename, 0x00, 120);
					if (j==1) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN1.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN1_scaled.jpg");						
						}
					} else if (j==2) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN1.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN1_scaled.jpg");						
						}
					} else if (j==3) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN1.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN1_scaled.jpg");						
						}
					}

					selfImage = imread(strSelfFilename, CV_LOAD_IMAGE_GRAYSCALE);

					myMatches = myMatcher.DoMatching_Fixed(selfImage, queryImage, nNumKeypoint1, nNumKeypoint2, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

					// Ground truth, matched self image distance (Z0), direction, matched count, average ratio (w0/wNew) 
					myfile << nQueryDistance << "," << nSelfDistance << "," << j << "," << myMatches.size() << "," << fAvgFeatureRatio << "\n";
				}
			}

		}
	}


	myfile.close();


}



void CalculateDistance_GN3_GS4(int nSelfImageScaled)
{
	float fFocalRatio_GN3_GS4 = 1.058;
	int narrCarGroup[] = {15,16};
	int nCarGroupCnt = sizeof(narrCarGroup)/sizeof(int);
	char strResult[120];
	char strSelfFilename[120];
	char strQueryFilename[120];
	Mat selfImage;
	Mat queryImage;
	int nQueryDistance;
	int nSelfDistance;

	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;

	int nMatchedCount = 0;
	int nNumKeypoint1, nNumKeypoint2;

	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;
	int i,j,k,m;

	memset(strResult, 0x00, 120);
	if (nSelfImageScaled == 0) {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_AllDistance\\GN3_GS4.csv");
	} else {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_Scaled\\GN3_GS4.csv");	
	}

	myfile.open (strResult, ofstream::out | ofstream::app);

	for (i=0; i<nCarGroupCnt; i++) {
		for (j=1; j<=3; j++) {
			for (k=1; k<=5; k++) {
				nQueryDistance = k;
				memset(strQueryFilename, 0x00, 120);
				
				if (j==1) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nQueryDistance, "\\GS4.jpg");
				} else if (j==2) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nQueryDistance, "\\GS4.jpg");				
				} else if (j==3) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nQueryDistance, "\\GS4.jpg");
				}

				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);


				for (m=1; m<=5; m++) {
					nSelfDistance = m;
					memset(strSelfFilename, 0x00, 120);
					if (j==1) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN3.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN3_scaled.jpg");						
						}
					} else if (j==2) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN3.jpg");	
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN3_scaled.jpg");							
						}
					} else if (j==3) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN3.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN3_scaled.jpg");						
						}
					}

					selfImage = imread(strSelfFilename, CV_LOAD_IMAGE_GRAYSCALE);

					myMatches = myMatcher.DoMatching_Fixed(selfImage, queryImage, nNumKeypoint1, nNumKeypoint2, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

					// Ground truth, matched self image distance (Z0), direction, matched count, average ratio (w0/wNew) 
					myfile << nQueryDistance << "," << nSelfDistance << "," << j << "," << myMatches.size() << "," << fAvgFeatureRatio << "\n";
				}
			}

		}
	}

	myfile.close();

}



void CalculateDistance_GN1_GS4(int nSelfImageScaled)
{
	float fFocalRatio_GN1_GS4 = 1.058;
	int narrCarGroup[] = {1, 2, 3, 6, 8, 9, 10, 11, 12};
	int nCarGroupCnt = sizeof(narrCarGroup)/sizeof(int);
	char strResult[120];
	char strSelfFilename[120];
	char strQueryFilename[120];
	Mat selfImage;
	Mat queryImage;
	int nQueryDistance;
	int nSelfDistance;

	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;

	int nMatchedCount = 0;
	int nNumKeypoint1, nNumKeypoint2;

	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;
	int i,j,k,m;

	memset(strResult, 0x00, 120);
	if (nSelfImageScaled == 0) {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_AllDistance\\GN1_GS4.csv");
	} else {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_Scaled\\GN1_GS4.csv");	
	}

	myfile.open (strResult, ofstream::out | ofstream::app);

	for (i=0; i<nCarGroupCnt; i++) {
		for (j=1; j<=3; j++) {
			for (k=1; k<=10; k++) {
				nQueryDistance = k*5;
				memset(strQueryFilename, 0x00, 120);
				
				if (j==1) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nQueryDistance, "\\GS4.jpg");
				} else if (j==2) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nQueryDistance, "\\GS4.jpg");				
				} else if (j==3) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nQueryDistance, "\\GS4.jpg");
				}

				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);


				for (m=1; m<=10; m++) {
					nSelfDistance = m*5;
					memset(strSelfFilename, 0x00, 120);
					if (j==1) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN1.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN1_scaled.jpg");						
						}
					} else if (j==2) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN1.jpg");	
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN1_scaled.jpg");							
						}
					} else if (j==3) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN1.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN1_scaled.jpg");						
						}
					}

					selfImage = imread(strSelfFilename, CV_LOAD_IMAGE_GRAYSCALE);

					myMatches = myMatcher.DoMatching_Fixed(selfImage, queryImage, nNumKeypoint1, nNumKeypoint2, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

					// Ground truth, matched self image distance (Z0), direction, matched count, average ratio (w0/wNew) 
					myfile << nQueryDistance << "," << nSelfDistance << "," << j << "," << myMatches.size() << "," << fAvgFeatureRatio << "\n";
				}
			}

		}
	}

	myfile.close();

}


void CalculateDistance_GN1_I4S(int nSelfImageScaled)
{
	float fFocalRatio_GN1_I4S = 0.910;
	int narrCarGroup[] = {1, 2, 3, 6, 7, 8, 9, 10, 11, 12};
	int nCarGroupCnt = sizeof(narrCarGroup)/sizeof(int);
	char strResult[120];
	char strSelfFilename[120];
	char strQueryFilename[120];
	Mat selfImage;
	Mat queryImage;
	int nQueryDistance;
	int nSelfDistance;

	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;

	int nMatchedCount = 0;
	int nNumKeypoint1, nNumKeypoint2;

	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;
	int i,j,k,m;

	memset(strResult, 0x00, 120);
	if (nSelfImageScaled == 0) {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_AllDistance\\GN1_I4S.csv");
	} else {
		sprintf(strResult, "%s%s", sPlace.c_str(), "Result\\MeasuredDistance\\SelfImage_Scaled\\GN1_I4S.csv");	
	}

	myfile.open (strResult, ofstream::out | ofstream::app);

	for (i=0; i<nCarGroupCnt; i++) {
		cout<<"Car Group " <<  narrCarGroup[i] << endl;
		for (j=1; j<=3; j++) {
			for (k=1; k<=10; k++) {
				
				nQueryDistance = k*5;

				cout<<"Query Distance==" << nQueryDistance << endl;

				memset(strQueryFilename, 0x00, 120);
				
				if (j==1) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nQueryDistance, "\\I4S.jpg");
				} else if (j==2) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nQueryDistance, "\\I4S.jpg");				
				} else if (j==3) {
					sprintf(strQueryFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nQueryDistance, "\\I4S.jpg");
				}

				queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);


				for (m=1; m<=10; m++) {
					nSelfDistance = m*5;

					cout<<"Self Distance = " << nSelfDistance << endl;

					memset(strSelfFilename, 0x00, 120);
					if (j==1) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN1.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\Rear\\", nSelfDistance, "\\GN1_scaled.jpg");						
						}
					} else if (j==2) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN1.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\L30\\", nSelfDistance, "\\GN1_scaled.jpg");						
						}
					} else if (j==3) {
						if (nSelfImageScaled == 0) {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN1.jpg");
						} else {
							sprintf(strSelfFilename,"%s%s%d%s%d%s", sPlace.c_str(), "Car_",  narrCarGroup[i], "\\R30\\", nSelfDistance, "\\GN1_scaled.jpg");
						}
					}

					selfImage = imread(strSelfFilename, CV_LOAD_IMAGE_GRAYSCALE);

					myMatches = myMatcher.DoMatching_Fixed(selfImage, queryImage, nNumKeypoint1, nNumKeypoint2, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

					// Ground truth, matched self image distance (Z0), direction, matched count, average ratio (w0/wNew) 
					myfile << nQueryDistance << "," << nSelfDistance << "," << j << "," << myMatches.size() << "," << fAvgFeatureRatio << "\n";
				}
			}

		}
	}

	myfile.close();
}


//This function is used to scale some self images
void ScaleSelfImage()
{
	int narrSelfImgDist[] = {5, 15, 25, 35, 45};
	int nSelfImgDistCnt = sizeof(narrSelfImgDist)/sizeof(int);

	int narrCarGroup[] = {1, 2, 3, 6, 7, 8, 9, 10, 11, 12};
	int nCarGroupCnt = sizeof(narrCarGroup)/sizeof(int);

	int i, j, k, m;
	int nDistance, nDistanceScaled; 
	Mat baseImage;
	Mat scaledImage;
	char strBaseFile[120];
	char strScaledFile_SameAsOrg[120];
	char strScaledFile[120];

	for (i=0; i<nCarGroupCnt; i++) {	//Car Group
		for (j=1; j<=3; j++) {		//Direction
			for (k=1; k<=10; k++) {	//Distance
				if (k % 2  == 1) { //for dist 5, 15, 25, 35, 45---scale=original,  for 10, 20, 30, 40, 50---scaled from previous distance
					nDistance = k*5;
					nDistanceScaled = nDistance + 5;

					memset(strBaseFile, 0x00, 120);
					memset(strScaledFile_SameAsOrg, 0x00, 120);
					memset(strScaledFile, 0x00, 120);

					if (j==1) {
						sprintf(strBaseFile, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\Rear\\", nDistance, "\\GN1.jpg");
						sprintf(strScaledFile_SameAsOrg, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\Rear\\", nDistance, "\\GN1_scaled.jpg");
						sprintf(strScaledFile, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\Rear\\", nDistanceScaled, "\\GN1_scaled.jpg");

					} else if (j==2) {
						sprintf(strBaseFile, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\L30\\", nDistance, "\\GN1.jpg");				
						sprintf(strScaledFile_SameAsOrg, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\L30\\", nDistance, "\\GN1_scaled.jpg");
						sprintf(strScaledFile, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\L30\\", nDistanceScaled, "\\GN1_scaled.jpg");

					} else if (j==3) {
						sprintf(strBaseFile, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\R30\\", nDistance, "\\GN1.jpg");
						sprintf(strScaledFile_SameAsOrg, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\R30\\", nDistance, "\\GN1_scaled.jpg");
						sprintf(strScaledFile, "%s%s%d%s%d%s", sPlace.c_str(), "Car_", narrCarGroup[i], "\\R30\\", nDistanceScaled, "\\GN1_scaled.jpg");

					}

					baseImage = imread(strBaseFile);
					imwrite(strScaledFile_SameAsOrg, baseImage); //Equals to rename

					resize(baseImage, scaledImage, Size(baseImage.cols*nDistance*1.0/nDistanceScaled, baseImage.rows*nDistance*1.0/nDistanceScaled));
					imwrite(strScaledFile, scaledImage);
				}

			}
		}
	}
}



void CalculateDistanceBasedOnRatio(int nSelfImageScaled)
{
	cout<<"Beginnning matching all possible self images for calculating Distance......"<<endl;
	cout<<"######GN3 vs. GNS"<<endl;
//	CalculateDistance_GN1_GN(nSelfImageScaled);
	CalculateDistance_GN3_GNS(nSelfImageScaled);

	cout<<"######GN3 vs. GS4"<<endl;
//	CalculateDistance_GN1_GS4(nSelfImageScaled);
	CalculateDistance_GN3_GS4(nSelfImageScaled);

	//cout<<"######GN1 vs. I4S"<<endl;
	//CalculateDistance_GN1_I4S(nSelfImageScaled);
	cout<<"Matching all possible self images for calculating distance Finished!!!!"<<endl;

}


int main()
{
	int nSelfImageScaled = 0;

	cout<<"Beging-----------------------------------"<<endl;
	
	//ExtractImageFromVideo();
	//CalculateFocalRatio();
	CalculateDistanceBasedOnRatio(nSelfImageScaled);
	//ScaleSelfImage();
	cout<<"End!!!!!!!"<<endl;

	getchar();
	
	return 0;
}

