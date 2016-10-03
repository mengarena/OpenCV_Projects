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


void ExtractImageFromVideo_ForOnePhone()
{
	Mat originalFrame;
	int DistArr[] = {10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nDistArrLen = sizeof(DistArr)/sizeof(int);

	int DistArrRight[] = {10, 20, 30, 40, 50, 60, 70};
	int nDistArrRightLen = sizeof(DistArrRight)/sizeof(int);

	int i;
	char *folder = "Volvo1225";
	char *subVideoFolder = "GalaxyS4_cloudy1230";
	char *filePre = "GS4_c";
	char strVideoFilename[120];
	char strImageFilename[120];

	int nFrameCount;
	int j;
	int nIdx;


	for (i=0; i<nDistArrLen; i++) {

		////////////Rear
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\", subVideoFolder, "\\B_", DistArr[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice1(strVideoFilename);
		nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice1.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				memset(strImageFilename, 0x00, 120);
				sprintf(strImageFilename, "%s%s%s%d%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", DistArr[i], "\\org\\", filePre, "_", nIdx, ".jpg");
				imwrite(strImageFilename, originalFrame);
				if (nIdx == 3) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", DistArr[i], "\\", filePre, "_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}


		////////////Left15
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\", subVideoFolder ,"\\L15_", DistArr[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice2(strVideoFilename);
		nFrameCount = captureDevice2.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice2.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				memset(strImageFilename, 0x00, 120);
				sprintf(strImageFilename, "%s%s%s%d%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", DistArr[i], "\\org\\", filePre, "_", nIdx, ".jpg");
				imwrite(strImageFilename, originalFrame);
				if (nIdx == 3) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", DistArr[i], "\\", filePre, "_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}


		////////////Left30
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\", subVideoFolder, "\\L30_", DistArr[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice3(strVideoFilename);
		nFrameCount = captureDevice3.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice3.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				memset(strImageFilename, 0x00, 120);
				sprintf(strImageFilename, "%s%s%s%d%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", DistArr[i], "\\org\\", filePre, "_", nIdx, ".jpg");
				imwrite(strImageFilename, originalFrame);
				if (nIdx == 3) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", DistArr[i], "\\", filePre, "_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}

	}


	//////////Right
	for (i=0; i<nDistArrRightLen; i++) {

		////////////Right
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\", subVideoFolder, "\\R30_", DistArrRight[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice4(strVideoFilename);
		nFrameCount = captureDevice4.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice4.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				memset(strImageFilename, 0x00, 120);
				sprintf(strImageFilename, "%s%s%s%d%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", DistArrRight[i], "\\org\\", filePre, "_", nIdx, ".jpg");
				imwrite(strImageFilename, originalFrame);
				if (nIdx == 3) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", DistArrRight[i], "\\", filePre, "_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}

	}

}



void ExtractImageFromVideo_Rear()
{
	Mat originalFrame;
	int Rear[] = {10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nRearLen = sizeof(Rear)/sizeof(int);

	int i;
	char *folder = "Volvo1225";
	char strVideoFilename[120];
	char strImageFilename[120];

	int nFrameCount;
	int j;
	int nIdx;


	//////////Rear
	for (i=0; i<nRearLen; i++) {

		////////////Galaxy Nexus
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\GalaxyNexus\\B_", Rear[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice1(strVideoFilename);
		nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice1.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", Rear[i], "\\org\\GN_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);
				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", Rear[i], "\\GN_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}


		////////////Galaxy S4
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\GalaxyS4\\B_", Rear[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice2(strVideoFilename);
		nFrameCount = captureDevice2.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice2.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", Rear[i], "\\org\\GS4_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);

				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", Rear[i], "\\GS4_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}



		////////////iPhone 4S
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\iPhone4S\\B_", Rear[i], ".MOV");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice3(strVideoFilename);
		nFrameCount = captureDevice3.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice3.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", Rear[i], "\\org\\i4S_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);

				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", Rear[i], "\\i4S_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}


	}

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExtractImageFromVideo_Left15()
{
	Mat originalFrame;
	int Left15[] = {10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nLeft15Len = sizeof(Left15)/sizeof(int);

	int i;
	char *folder = "Volvo1225";
	char strVideoFilename[120];
	char strImageFilename[120];

	int nFrameCount;
	int j;
	int nIdx;


	//////////Rear
	for (i=0; i<nLeft15Len; i++) {

		////////////Galaxy Nexus
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\GalaxyNexus\\L15_", Left15[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice1(strVideoFilename);
		nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice1.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", Left15[i], "\\org\\GN_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);
				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", Left15[i], "\\GN_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}


		////////////Galaxy S4
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\GalaxyS4\\L15_", Left15[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice2(strVideoFilename);
		nFrameCount = captureDevice2.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice2.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", Left15[i], "\\org\\GS4_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);

				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", Left15[i], "\\GS4_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}



		////////////iPhone 4S
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\iPhone4S\\L15_", Left15[i], ".MOV");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice3(strVideoFilename);
		nFrameCount = captureDevice3.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice3.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", Left15[i], "\\org\\i4S_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);

				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", Left15[i], "\\i4S_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}



	}


}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExtractImageFromVideo_Left30()
{
	Mat originalFrame;
	int Left30[] = {10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nLeft30Len = sizeof(Left30)/sizeof(int);

	int i;
	char *folder = "Volvo1225";
	char strVideoFilename[120];
	char strImageFilename[120];

	int nFrameCount;
	int j;
	int nIdx;


	//////////Rear
	for (i=0; i<nLeft30Len; i++) {

		////////////Galaxy Nexus
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\GalaxyNexus\\L30_", Left30[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice1(strVideoFilename);
		nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice1.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", Left30[i], "\\org\\GN_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);
				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", Left30[i], "\\GN_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}


		////////////Galaxy S4
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\GalaxyS4\\L30_", Left30[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice2(strVideoFilename);
		nFrameCount = captureDevice2.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice2.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", Left30[i], "\\org\\GS4_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);

				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", Left30[i], "\\GS4_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}



		////////////iPhone 4S
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\iPhone4S\\L30_", Left30[i], ".MOV");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice3(strVideoFilename);
		nFrameCount = captureDevice3.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice3.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				//memset(strImageFilename, 0x00, 120);
				//sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", Left30[i], "\\org\\i4S_", nIdx, ".jpg");
				//imwrite(strImageFilename, originalFrame);

				if (nIdx == 6) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", Left30[i], "\\i4S_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}



	}

}






///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExtractImageFromVideo_Right30()
{
	Mat originalFrame;
	int Right30[] = {10, 20, 30, 40, 50, 60, 70};
	int nRight30Len = sizeof(Right30)/sizeof(int);

	int i;
	char *folder = "Volvo1225";
	char strVideoFilename[120];
	char strImageFilename[120];

	int nFrameCount;
	int j;
	int nIdx;


	//////////Rear
	for (i=0; i<nRight30Len; i++) {

		////////////Galaxy Nexus
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\GalaxyNexus\\R30_", Right30[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice1(strVideoFilename);
		nFrameCount = captureDevice1.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice1.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				memset(strImageFilename, 0x00, 120);
				sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", Right30[i], "\\org\\GN_", nIdx, ".jpg");
				imwrite(strImageFilename, originalFrame);
				if (nIdx == 3) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", Right30[i], "\\GN_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}


		////////////Galaxy S4
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\GalaxyS4\\R30_", Right30[i], ".mp4");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice2(strVideoFilename);
		nFrameCount = captureDevice2.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice2.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				memset(strImageFilename, 0x00, 120);
				sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", Right30[i], "\\org\\GS4_", nIdx, ".jpg");
				imwrite(strImageFilename, originalFrame);

				if (nIdx == 3) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", Right30[i], "\\GS4_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}



		////////////iPhone 4S
		memset(strVideoFilename, 0x00, 120);
		sprintf(strVideoFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\OriginalData\\iPhone4S\\R30_", Right30[i], ".MOV");
		cout<<"Processing...."<<strVideoFilename<<endl;

		//setup video capture device and link it to the first capture device    
		VideoCapture captureDevice3(strVideoFilename);
		nFrameCount = captureDevice3.get(CV_CAP_PROP_FRAME_COUNT);

		nIdx = 0;
		j = 0;

		while(true) {        
			//capture a new image frame        
			if (!captureDevice3.read(originalFrame)) break;
			j = j + 1;

			if (j % 10 == 0) {
				nIdx = nIdx + 1;
				memset(strImageFilename, 0x00, 120);
				sprintf(strImageFilename, "%s%s%s%d%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", Right30[i], "\\org\\i4S_", nIdx, ".jpg");
				imwrite(strImageFilename, originalFrame);

				if (nIdx == 3) {
					memset(strImageFilename, 0x00, 120);
					sprintf(strImageFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", Right30[i], "\\i4S_org.jpg");
					imwrite(strImageFilename, originalFrame);
				}

			}
		}



	}

}








void ExtractImgFromVideo()
{
	cout<<"Start........................................................"<<endl;

	cout<<"Processing........................Rear"<<endl;
	ExtractImageFromVideo_Rear();

	cout<<"Processing........................Left15"<<endl;
	ExtractImageFromVideo_Left15();

	cout<<"Processing........................Left30"<<endl;
	ExtractImageFromVideo_Left30();

	//cout<<"Processing........................Right30"<<endl;
	//ExtractImageFromVideo_Right30();

	cout<<"Done........................................................"<<endl;

}




#if 0
void MeasureMatching()
{
	char strRefFilename[120];
	char strQueryFilename[120];
	ofstream myfile;

	myfile.open ("E:\\TestVideo\\ForDecideSize\\Size_MatchedPoints_ORB_withFinal.csv", ofstream::out | ofstream::app);

	int nRefCountArray[] = {3, 4, 3, 4, 3, 3, 2, 3, 3, 3, 2, 3, 3, 2};

	//int nRefCountArray[] = {3, 3, 3, 3, 4, 3, 2, 3, 3, 3, 3, 3, 3, 3};   //Different car
	int nQueryCountArray[] = {34, 59, 113, 29, 111, 47, 102, 40, 42, 25, 18, 38, 45, 63};

	Mat queryImage;
	Mat refImage;
	Size matSizeRef;
	Size matSizeQuery;
	float fRefSize;  //KB
	float fQuerySize;  //KB
	OrbMatching myMatcher;
	
	double processTime = 0.0;
	struct stat filestatus;
	

	for (int i = 1; i<=14; i++) {
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

				myMatches = myMatcher.DoMatching(refImage, queryImage, processTime);

				myfile<<i<<","<<j<<","<<k<<","<<fRefSize<<","<<fQuerySize<<","<<myMatches.size()<<"\n";
			}
		}
	}

	myfile.close();

	return;

}


void MeasureMatching_forDifferentImage()
{
	char strRefFilename[120];
	char strQueryFilename[120];
	ofstream myfile;

	myfile.open ("E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\allQ_260_withFinal.csv", ofstream::out | ofstream::app);

	Mat queryImage;
	Mat refImage;
	Size matSizeRef;
	Size matSizeQuery;
	float fRefSize;  //KB
	float fQuerySize;  //KB
	OrbMatching myMatcher;
	
	double processTime = 0.0;
	struct stat filestatus;
	

	for (int i = 1; i<=260; i++) {
		memset(strRefFilename, 0x00, 120);
		//sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", i,  ".jpg");
		sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\query\\query_", i, ".jpg");
//		sprintf(strRefFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", i, ".jpg");

		refImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);

		stat(strRefFilename, &filestatus);
		fRefSize = filestatus.st_size;
		fRefSize = fRefSize*1.0/1024;

		for (int j = i+1; j<=260; j++) {
			memset(strQueryFilename, 0x00, 120);
			sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\query\\query_", j, ".jpg");
//			sprintf(strQueryFilename, "%s%d%s", "E:\\TestVideo\\ForChooseSize_DifferentCar\\Total\\ref_", j, ".jpg");

			queryImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			stat(strQueryFilename, &filestatus);
			fQuerySize = filestatus.st_size;
			fQuerySize = fQuerySize*1.0/1024;

			vector<DMatch> myMatches;

			myMatches = myMatcher.DoMatching(refImage, queryImage, processTime);

			myfile<<i<<","<<j<<","<<fRefSize<<","<<fQuerySize<<","<<myMatches.size()<<"\n";
		}
	}

	myfile.close();

	return;

}
#endif



void MatchLeftRight()
{
	int nBaseDistantArray[] = {10, 20, 30, 40, 50, 60, 70};
	int nDistCnt = sizeof(nBaseDistantArray)/sizeof(int);

	char *folder = "Volvo1225";
	char strResult[120];

	char strLeftFilename[120];
	char strRightFilename[120];
	Mat leftImage;
	Mat rightImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;
	int nMatchedCount = 0;

	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\LeftRightMatch.csv");

	myfile.open (strResult, ofstream::out | ofstream::app);

	// "E:\\TestVideo\\BigParking"
	//Base is Galaxy Nexus 1
	//Query Phone: Galaxy Nexus 3, iPhone 4S, NexusOne, WP
	for (int i=0; i<nDistCnt; i++) {

		///////////Galaxy Nexus
		memset(strLeftFilename, 0x00, 120);	
		sprintf(strLeftFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN.jpg");
		leftImage = imread(strLeftFilename, CV_LOAD_IMAGE_GRAYSCALE);

		memset(strRightFilename, 0x00, 120);
		sprintf(strRightFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nBaseDistantArray[i], "\\GN.jpg");
		rightImage = imread(strRightFilename, CV_LOAD_IMAGE_GRAYSCALE);

		nMatchedCount = 0;
		fMaxFeatureRatio=0.0;
		fAvgFeatureRatio=0.0;
		fEuDistRatio = 0.0;

		myMatches = myMatcher.DoMatching(leftImage, rightImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

		cout<<"GN,"<<nMatchedCount<<endl;

		//First: Galaxy Nexus
		//Distance, Matched Count
		myfile<<nBaseDistantArray[i]<<","<<nMatchedCount;


		/////////////////Galaxy S4
		memset(strLeftFilename, 0x00, 120);	
		sprintf(strLeftFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GS4.jpg");
		leftImage = imread(strLeftFilename, CV_LOAD_IMAGE_GRAYSCALE);

		memset(strRightFilename, 0x00, 120);
		sprintf(strRightFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nBaseDistantArray[i], "\\GS4.jpg");
		rightImage = imread(strRightFilename, CV_LOAD_IMAGE_GRAYSCALE);

		nMatchedCount = 0;
		fMaxFeatureRatio=0.0;
		fAvgFeatureRatio=0.0;
		fEuDistRatio=0.0;

		myMatches = myMatcher.DoMatching(leftImage, rightImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio,fEuDistRatio);

		cout<<"GS4,"<<nMatchedCount<<endl;

		//Second: Galaxy S4
		//Distance, Matched Count
		myfile<<","<<nMatchedCount;


		/////////////////iPhone 4S
		memset(strLeftFilename, 0x00, 120);	
		sprintf(strLeftFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\i4S.jpg");
		leftImage = imread(strLeftFilename, CV_LOAD_IMAGE_GRAYSCALE);

		memset(strRightFilename, 0x00, 120);
		sprintf(strRightFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nBaseDistantArray[i], "\\i4S.jpg");
		rightImage = imread(strRightFilename, CV_LOAD_IMAGE_GRAYSCALE);

		nMatchedCount = 0;
		fMaxFeatureRatio=0.0;
		fAvgFeatureRatio=0.0;
		fEuDistRatio = 0.0;

		myMatches = myMatcher.DoMatching(leftImage, rightImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

		cout<<"i4S,"<<nMatchedCount<<endl;

		//Third: iPhone 4S
		//Distance, Matched Count
		myfile<<","<<nMatchedCount<<"\n";

	}	

			
	myfile.close();

	return;

}


///////////////////////////////////////////////////////////////////////////////////
//Measure the focal length ratio between different phones at the same angle, same distance
//GN1~GN2:
//GN~GS4:
//GN~i4S:
void MeasureRatio()
{
	int nBaseDistantArray[] = {10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nDistCnt = sizeof(nBaseDistantArray)/sizeof(int);

	char *folder = "Volvo1225";
	char strResult[120];
	char strRefFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat receivedImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;
	int nMatchedCount = 0;

	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Result\\PhoneCameraFocalRatio.csv");

//	myfile.open ("E:\\TestVideo\\TestAccuracy\\Car1_HondaOdyssey1217\\PhoneCameraFocalRatio.csv", ofstream::out | ofstream::app);
	myfile.open (strResult, ofstream::out | ofstream::app);

	for (int k=1; k<=3; k++) {  //Three angles
		for (int i=0; i<nDistCnt; i++) {
			cout<<k<<","<<nBaseDistantArray[i]<<endl;

			memset(strRefFilename, 0x00, 120);
			if (k==1) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==2) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==3) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN.jpg");
			}

			baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);

			memset(strQueryFilename, 0x00, 120);

			if (k==1) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN_6.jpg");
			} else if (k==2) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN_6.jpg");
			} else if (k==3) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN_6.jpg");
			}

			receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;

			//GN1~GN2
			myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//Galaxy Nexus is the base
			//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
			myfile<<k<<","<<nBaseDistantArray[i]<<","<<nMatchedCount<<","<<fMaxFeatureRatio<<","<<fAvgFeatureRatio<<","<<fEuDistRatio;
			cout<<k<<","<<nBaseDistantArray[i]<<","<<nMatchedCount<<","<<fMaxFeatureRatio<<","<<fAvgFeatureRatio<<","<<fEuDistRatio;

			////////////////////////////////////
			memset(strQueryFilename, 0x00, 120);

			if (k==1) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GS4.jpg");
			} else if (k==2) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GS4.jpg");
			} else if (k==3) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GS4.jpg");
			}

			receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;

			//GN~GS4
			myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//Galaxy Nexus is the base
			//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
			myfile<<","<<nMatchedCount<<","<<fMaxFeatureRatio<<","<<fAvgFeatureRatio<<","<<fEuDistRatio;
			cout<<","<<nMatchedCount<<","<<fMaxFeatureRatio<<","<<fAvgFeatureRatio<<","<<fEuDistRatio;


			////////////////////////////////////
			memset(strQueryFilename, 0x00, 120);

			if (k==1) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\i4S.jpg");
			} else if (k==2) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\i4S.jpg");
			} else if (k==3) {
				sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\i4S.jpg");
			}

			receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;

			//GN~i4S
			myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
			myfile<<","<<nMatchedCount<<","<<fMaxFeatureRatio<<","<<fAvgFeatureRatio<<","<<fEuDistRatio<<"\n";
			cout<<","<<nMatchedCount<<","<<fMaxFeatureRatio<<","<<fAvgFeatureRatio<<","<<fEuDistRatio<<"\n";

		}	
	}

			
	myfile.close();

	return;

}


///////////////////////////////////////////////////////////////////////////////////////
// Measure how many matched point can get between Different phones
// Matching image from GN2, GS4, iPhone 4S to GN1 at Right30
///////////////////////////////////////////////////////////////////////////////////////
void MeasureDistance()
{
	float fRatioNS4 = 1.059;	//1.138
	float fRatioN4S = 0.912;	//0.874
	float fRatioNN = 0.999;

	int nSelfDistantArray[] = {10, 20, 25, 30, 35, 40, 45};
	int nSelfDistCnt = sizeof(nSelfDistantArray)/sizeof(int);
	int nGroundTruthDistantArray[] = {10, 20, 30, 40, 50};
	int nGroundTruthDistCnt = sizeof(nGroundTruthDistantArray)/sizeof(int);

	char *folder = "Volvo1225";
	char strResult[120];
	char strRefFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat receivedImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;
	int nMatchedCount = 0;

	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Result_scaledX\\DistanceMeasure_MatchedNum_self10to40_scaled.csv");

//	myfile.open ("E:\\TestVideo\\TestAccuracy\\Car1_HondaOdyssey1217\\PhoneCameraFocalRatio.csv", ofstream::out | ofstream::app);
	myfile.open (strResult, ofstream::out | ofstream::app);

	for (int i=0; i<nSelfDistCnt; i++) {
		///////////Galaxy Nexus
		memset(strRefFilename, 0x00, 120);	
		sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nSelfDistantArray[i], "\\GN_scaled.jpg");
		baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);

		for (int j=0; j<nGroundTruthDistCnt; j++) {
			memset(strQueryFilename, 0x00, 120);
			sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nGroundTruthDistantArray[j], "\\GN_6.jpg");
			receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;
			//GN1~GN2
			myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//cout<<"GN1-GN2,"<<nMatchedCount<<endl;

			//First: Galaxy Nexus
			//Distance, Matched Count
			myfile<<nSelfDistantArray[i]<<","<<nGroundTruthDistantArray[j]<<","<<1<<","<<nMatchedCount<<","<<fAvgFeatureRatio;

			/////////////////////////////////
			memset(strQueryFilename, 0x00, 120);
			sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nGroundTruthDistantArray[j], "\\GS4.jpg");
			receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;
			//GN~GS4
			myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//cout<<"GN-GS4,"<<nMatchedCount<<endl;

			//First: Galaxy Nexus
			//Distance, Matched Count
			myfile<<","<<2<<","<<nMatchedCount<<","<<fAvgFeatureRatio;


			memset(strQueryFilename, 0x00, 120);
			sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nGroundTruthDistantArray[j], "\\i4S.jpg");
			receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;
			//GN~i4S
			myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//cout<<"GN,"<<nMatchedCount<<endl;

			//First: Galaxy Nexus
			//Distance, Matched Count
			myfile<<","<<3<<","<<nMatchedCount<<","<<fAvgFeatureRatio<<"\n";

		}

	}

	myfile.close();

	return;


}


///New image is matched with ground truth
void MeasureDistance_GT_Self()
{
	float fRatioNS4 = 1.059;	//1.138
	float fRatioN4S = 0.912;	//0.874
	float fRatioNN = 0.999;

	int nSelfDistantArray[] = {10, 20, 25, 30, 35, 40, 45};
	int nSelfDistCnt = sizeof(nSelfDistantArray)/sizeof(int);
	int nGroundTruthDistantArray[] = {10, 20, 30, 40, 50};
	int nGroundTruthDistCnt = sizeof(nGroundTruthDistantArray)/sizeof(int);

	char *folder = "Volvo1225";
	char strResult[120];
	char strSelfFilename[120];
	char strReceivedFilename[120];
	Mat selfImage;
	Mat receivedImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;
	int nMatchedCount = 0;

	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Result_scaledX\\DistanceMeasure_MatchedNum_self10to40_scaled.csv");

//	myfile.open ("E:\\TestVideo\\TestAccuracy\\Car1_HondaOdyssey1217\\PhoneCameraFocalRatio.csv", ofstream::out | ofstream::app);
	myfile.open (strResult, ofstream::out | ofstream::app);

	for (int j=0; j<nGroundTruthDistCnt; j++) {

		for (int i=0; i<nSelfDistCnt; i++) {
			////Self Image from Galaxy Nexus
			memset(strSelfFilename, 0x00, 120);	
			sprintf(strSelfFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nSelfDistantArray[i], "\\GN_scaled.jpg");
			selfImage = imread(strSelfFilename, CV_LOAD_IMAGE_GRAYSCALE);

			///Received new Galaxy Nexus image
			memset(strReceivedFilename, 0x00, 120);
			sprintf(strReceivedFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nGroundTruthDistantArray[j], "\\GN_6.jpg");
			receivedImage = imread(strReceivedFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;
			//GN1~GN2
			myMatches = myMatcher.DoMatching(selfImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//Distance, Matched Count
			myfile<<nGroundTruthDistantArray[j]<<","<<nSelfDistantArray[i]<<","<<1<<","<<nMatchedCount<<","<<fAvgFeatureRatio;
			//////////////////////////////////////
			///Reeived new Galaxy S4 image
			memset(strReceivedFilename, 0x00, 120);
			sprintf(strReceivedFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nGroundTruthDistantArray[j], "\\GS4.jpg");
			receivedImage = imread(strReceivedFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;
			//GN~GS4
			myMatches = myMatcher.DoMatching(selfImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//Distance, Matched Count
			myfile<<","<<2<<","<<nMatchedCount<<","<<fAvgFeatureRatio;
			////////////////////////////////////////
			///Received new iPhone 4S image
			memset(strReceivedFilename, 0x00, 120);
			sprintf(strReceivedFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Right30\\", nGroundTruthDistantArray[j], "\\i4S.jpg");
			receivedImage = imread(strReceivedFilename, CV_LOAD_IMAGE_GRAYSCALE);

			nMatchedCount = 0;
			fMaxFeatureRatio=0.0;
			fAvgFeatureRatio=0.0;
			fEuDistRatio = 0.0;
			//GN~i4S
			myMatches = myMatcher.DoMatching(selfImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

			//Distance, Matched Count
			myfile<<","<<3<<","<<nMatchedCount<<","<<fAvgFeatureRatio<<"\n";


		}

	}


	myfile.close();

	return;

}



// Matching image from different angles to see how many matched points gotten (Images from Same phone)
void MatchingDiffAngle()
{
	int nBaseDistantArray[] = {10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nDistCnt = sizeof(nBaseDistantArray)/sizeof(int);

	char *folder = "Volvo1225";
	char strResult[120];
	char strRefFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat receivedImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;
	int nMatchedCount = 0;

	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Result\\MatchedPoint_SamePhone.csv");

	myfile.open (strResult, ofstream::out | ofstream::app);

	for (int i=0; i<nDistCnt; i++) {
		//GN:  Rear-Rear, Rear-Left15, Rear-Left30, Left15-Left15, Left15-Left30, Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;
		myfile<<1<<","<<nBaseDistantArray[i]; //Galaxy Nexus

		for (int k=1; k<=3; k++) {
			memset(strRefFilename, 0x00, 120);
			if (k==1) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==2) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==3) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN.jpg");
			}

			baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);
		
			for (int m=k; m<=3; m++) {
				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}
		}

		myfile<<"\n";
	}	


	for (int i=0; i<nDistCnt; i++) {
		//GN:  Rear-Rear, Rear-Left15, Rear-Left30, Left15-Left15, Left15-Left30, Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;
		myfile<<2<<","<<nBaseDistantArray[i]; //Galaxy S4

		for (int k=1; k<=3; k++) {
			memset(strRefFilename, 0x00, 120);
			if (k==1) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GS4.jpg");
			} else if (k==2) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GS4.jpg");
			} else if (k==3) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GS4.jpg");
			}

			baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);
		
			for (int m=k; m<=3; m++) {
				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GS4.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GS4.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GS4.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}
		}

		myfile<<"\n";
	}	


	for (int i=0; i<nDistCnt; i++) {
		//GN:  Rear-Rear, Rear-Left15, Rear-Left30, Left15-Left15, Left15-Left30, Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;
		myfile<<3<<","<<nBaseDistantArray[i]; //iPhone 4S

		for (int k=1; k<=3; k++) {
			memset(strRefFilename, 0x00, 120);
			if (k==1) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\i4S.jpg");
			} else if (k==2) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\i4S.jpg");
			} else if (k==3) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\i4S.jpg");
			}

			baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);
		
			for (int m=k; m<=3; m++) {
				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\i4S.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\i4S.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\i4S.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}
		}

		myfile<<"\n";
	}	



	myfile.close();

	return;

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Matching image from at same distance but various angles to see how many matched points gotten (Images from Different phones)
// This it to see whether the most matching comes from the same/close angle, i.e. the matching could help to identify the direction of the vehicle
// GN1~GN2:  Rear-Rear, Rear-Left15, Rear-Left30, Left15-Rear, Left15-Left15, Left15-Left30, Left30-Rear, Left30-Left15, Left30-Left30
// GN1~GS4:
// GN1~i4S:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MatchingAllAngle_SameDistance_DifferentPhones()
{
	int nBaseDistantArray[] = {10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nDistCnt = sizeof(nBaseDistantArray)/sizeof(int);

	char *folder = "Volvo1225";
	char strResult[120];
	char strRefFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat receivedImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;
	int nMatchedCount = 0;

	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Result\\MatchedNum_DiffPhoneSameDistAllAngle.csv");

	myfile.open (strResult, ofstream::out | ofstream::app);

	for (int i=0; i<nDistCnt; i++) {
		//GN1-GN2:  Rear-Rear, Rear-Left15, Rear-Left30, Left15-Rear, Left15-Left15, Left15-Left30, Left30-Rear, Left30-Left15, Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;
		myfile<<1<<","<<1<<","<<nBaseDistantArray[i]; //Galaxy Nexus--Galaxy Nexus

		for (int k=1; k<=3; k++) {
			memset(strRefFilename, 0x00, 120);
			if (k==1) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==2) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==3) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN.jpg");
			}

			baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);
		
			for (int m=1; m<=3; m++) {
				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN_6.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN_6.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN_6.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}
		}

		myfile<<"\n";
	}	

	for (int i=0; i<nDistCnt; i++) {
		//GN1-GS4:  Rear-Rear, Rear-Left15, Rear-Left30, Left15-Rear, Left15-Left15, Left15-Left30, Left30-Rear, Left30-Left15, Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;
		myfile<<1<<","<<2<<","<<nBaseDistantArray[i]; //Galaxy Nexus--Galaxy S4

		for (int k=1; k<=3; k++) {
			memset(strRefFilename, 0x00, 120);
			if (k==1) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==2) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==3) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN.jpg");
			}

			baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);
		
			for (int m=1; m<=3; m++) {
				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GS4.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GS4.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GS4.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}
		}

		myfile<<"\n";
	}	


	for (int i=0; i<nDistCnt; i++) {
		//GN-iPhone 4S:  Rear-Rear, Rear-Left15, Rear-Left30, Left15-Rear, Left15-Left15, Left15-Left30, Left30-Rear, Left30-Left15, Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;
		myfile<<1<<","<<3<<","<<nBaseDistantArray[i]; //Galaxy Nexus--iPhone 4S

		for (int k=1; k<=3; k++) {
			memset(strRefFilename, 0x00, 120);
			if (k==1) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==2) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN.jpg");
			} else if (k==3) {
				sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN.jpg");
			}

			baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);
		
			for (int m=1; m<=3; m++) {
				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\i4S.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\i4S.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\i4S.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}
		}

		myfile<<"\n";
	}	



	myfile.close();

	return;

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Matching image from at various distance but same angles to see how many matched points gotten (Images from Different phones)
// This it to see whether the most matching comes from the same/close distance, i.e. the matching could help to identify the distance of the vehicle
// GN1~GN2:  10~70, Rear-Rear, Left15-Left15, Left30-Left30
// GN1~GS4:
// GN1~i4S:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MatchingSameAngle_AllDistance_DifferentPhones()
{
//	int nBaseDistantArray[] = {10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nBaseDistantArray[] = {10, 20, 25, 30, 35, 40, 45};

	int nDistCnt = sizeof(nBaseDistantArray)/sizeof(int);

	char *folder = "Volvo1225";
	char strResult[120];
	char strRefFilename[120];
	char strQueryFilename[120];
	Mat baseImage;
	Mat receivedImage;
	float fMaxFeatureRatio=0.0;
	float fAvgFeatureRatio=0.0;
	float fEuDistRatio = 0.0;
	int nMatchedCount = 0;
	int i,j,k,m;
	double processTime = 0.0;
				
	OrbMatching myMatcher;
	vector<DMatch> myMatches;

	ofstream myfile;

	memset(strResult, 0x00, 120);
	sprintf(strResult, "%s%s%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Result_scaledX\\MatchedNum_DiffPhoneAllDistSameAngle_withOrgwithGN1.csv");

	myfile.open (strResult, ofstream::out | ofstream::app);

///////////////////////////////
#if 1
	for (i=0; i<nDistCnt; i++) {
		//GN1-GN2:  10~70: Rear-Rear,Left15-Left15,  Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;

		for (k=0; k<nDistCnt; k++) {
			myfile<<1<<","<<1<<","<<nBaseDistantArray[i]<<","<<nBaseDistantArray[k]; //Galaxy Nexus--Galaxy Nexus
		
			for (m=1; m<=3; m++) {
				memset(strRefFilename, 0x00, 120);
				if (m==1) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN.jpg");
				} else if (m==2) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN.jpg");
				} else if (m==3) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN.jpg");
				}

				baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);


				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[k], "\\GN_6.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[k], "\\GN_6.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[k], "\\GN_6.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}

			myfile<<"\n";
		}
	}	
#endif
///////////////////////////////

#if 0
	for (i=0; i<nDistCnt; i++) {
		//GN1-GN2:  10~70: Rear-Rear,Left15-Left15,  Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;

		for (k=0; k<nDistCnt; k++) {
			myfile<<1<<","<<1<<","<<nBaseDistantArray[i]<<","<<nBaseDistantArray[k]; //Galaxy Nexus--Galaxy Nexus
		
			for (m=1; m<=3; m++) {
				memset(strRefFilename, 0x00, 120);
				if (m==1) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				} else if (m==2) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				} else if (m==3) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				}

				baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);


				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[k], "\\GN3.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[k], "\\GN3.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[k], "\\GN3.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}

			myfile<<"\n";
		}
	}	



	for (i=0; i<nDistCnt; i++) {
		//GN-GS4:  10~70: Rear-Rear,Left15-Left15,  Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;

		for (k=0; k<nDistCnt; k++) {
			myfile<<1<<","<<2<<","<<nBaseDistantArray[i]<<","<<nBaseDistantArray[k]; //Galaxy Nexus--Galaxy S4
		
			for (m=1; m<=3; m++) {
				memset(strRefFilename, 0x00, 120);
				if (m==1) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				} else if (m==2) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				} else if (m==3) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				}

				baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);


				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[k], "\\GS4.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[k], "\\GS4.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[k], "\\GS4.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}

			myfile<<"\n";
		}
	}	



	for (i=0; i<nDistCnt; i++) {
		//GN1-i4S:  10~70: Rear-Rear,Left15-Left15,  Left30-Left30
		cout<<nBaseDistantArray[i]<<endl;

		for (k=0; k<nDistCnt; k++) {
			myfile<<1<<","<<3<<","<<nBaseDistantArray[i]<<","<<nBaseDistantArray[k]; //Galaxy Nexus--iPhone 4S
		
			for (m=1; m<=3; m++) {
				memset(strRefFilename, 0x00, 120);
				if (m==1) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				} else if (m==2) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				} else if (m==3) {
					sprintf(strRefFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[i], "\\GN_scaled.jpg");
				}

				baseImage = imread(strRefFilename, CV_LOAD_IMAGE_GRAYSCALE);


				memset(strQueryFilename, 0x00, 120);

				if (m==1) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Rear\\", nBaseDistantArray[k], "\\i4S.jpg");
				} else if (m==2) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left15\\", nBaseDistantArray[k], "\\i4S.jpg");
				} else if (m==3) {
					sprintf(strQueryFilename, "%s%s%s%d%s", "E:\\TestVideo\\TestAccuracy\\", folder, "\\Left30\\", nBaseDistantArray[k], "\\i4S.jpg");
				}

				receivedImage = imread(strQueryFilename, CV_LOAD_IMAGE_GRAYSCALE);

				nMatchedCount = 0;
				fMaxFeatureRatio=0.0;
				fAvgFeatureRatio=0.0;
				fEuDistRatio = 0.0;

				myMatches = myMatcher.DoMatching(baseImage, receivedImage, processTime, nMatchedCount, fMaxFeatureRatio, fAvgFeatureRatio, fEuDistRatio);

				//Galaxy Nexus is the base
				//Angle, Distance, Matched Count, Max Feature Ratio, Avg Feature Ratio
				myfile<<","<<nMatchedCount;
			}

			myfile<<"\n";
		}
	}	

#endif

	myfile.close();

	return;


}



void ScaleImage()
{
	char *baseFolder = "E:\\TestVideo\\TestAccuracy\\Volvo1225\\";
//	char *subFolder = "Rear\\";
//	char *subFolder = "Left15\\";
	char *subFolder = "Left30\\";
//	char *subFolder = "Right30\\";

	char *baseFileName = "GN";
	int nBaseDist = 40;

//	int nDistantArray[] = {20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nDistantArray[] = {45};

	int nDistCnt = sizeof(nDistantArray)/sizeof(int);
	char strBaseFile[120];
	char strScaledFile[120];
	Mat baseImage;
	Mat scaledImage;

	for (int m=0; m<3; m++) {
		memset(strBaseFile, 0x00, 120);
		if (m==0) {
			sprintf(strBaseFile, "%s%s%d%s%s%s", baseFolder, "Rear\\", nBaseDist, "\\", baseFileName, ".jpg");
		} else if (m==1) {
			sprintf(strBaseFile, "%s%s%d%s%s%s", baseFolder, "Left15\\", nBaseDist, "\\", baseFileName, ".jpg");		
		} else {
			sprintf(strBaseFile, "%s%s%d%s%s%s", baseFolder, "Left30\\", nBaseDist, "\\", baseFileName, ".jpg");
		}

		baseImage = imread(strBaseFile);

		for (int i=0; i<nDistCnt; i++) {
			memset(strScaledFile, 0x00, 120);
			if (m==0) {
				sprintf(strScaledFile, "%s%s%d%s%s%s", baseFolder, "Rear\\", nDistantArray[i], "\\", baseFileName, "_scaled.jpg");
			} else if (m==1) {
				sprintf(strScaledFile, "%s%s%d%s%s%s", baseFolder, "Left15\\", nDistantArray[i], "\\", baseFileName, "_scaled.jpg");			
			} else {
				sprintf(strScaledFile, "%s%s%d%s%s%s", baseFolder, "Left30\\", nDistantArray[i], "\\", baseFileName, "_scaled.jpg");
			}

			resize(baseImage, scaledImage, Size(baseImage.cols*nBaseDist*1.0/nDistantArray[i], baseImage.rows*nBaseDist*1.0/nDistantArray[i]));
			imwrite(strScaledFile, scaledImage);
		}
	}

}


void ScaleImage_SingleDirection()
{
	char *baseFolder = "E:\\TestVideo\\TestAccuracy\\Volvo1225\\";
//	char *subFolder = "Rear\\";
//	char *subFolder = "Left15\\";
//	char *subFolder = "Left30\\";
	char *subFolder = "Right30\\";

	char *baseFileName = "GN";
	int nBaseDist = 40;

//	int nDistantArray[]= {20, 25, 30, 35, 40, 45, 50, 55, 60, 70};
	int nDistantArray[] = {45};

	int nDistCnt = sizeof(nDistantArray)/sizeof(int);
	char strBaseFile[120];
	char strScaledFile[120];
	Mat baseImage;
	Mat scaledImage;

	memset(strBaseFile, 0x00, 120);
	sprintf(strBaseFile, "%s%s%d%s%s%s", baseFolder, subFolder, nBaseDist, "\\", baseFileName, ".jpg");

	baseImage = imread(strBaseFile);

	for (int i=0; i<nDistCnt; i++) {
		memset(strScaledFile, 0x00, 120);
		sprintf(strScaledFile, "%s%s%d%s%s%s", baseFolder, subFolder, nDistantArray[i], "\\", baseFileName, "_scaled.jpg");

		resize(baseImage, scaledImage, Size(baseImage.cols*nBaseDist*1.0/nDistantArray[i], baseImage.rows*nBaseDist*1.0/nDistantArray[i]));
		imwrite(strScaledFile, scaledImage);
	}

}



String baseImageFile = "F:\\tmp\\tt\\car2.jpg";
//String baseImageFile = "E:\\TestVideo\\ParkingLot\\GalaxyNexus\\Rear\\Rear_30feet.png";
//String receivedImageFile = "E:\\TestVideo\ForPaper\\SameCar2.jpg";
//String receivedImageFile = "E:\\TestVideo\\ForPaper\\Self3.jpg";
//String receivedImageFile = "E:\\TestVideo\\ForPaper\\t3.jpg";
//String receivedImageFile = "E:\\TestVideo\\ForPaper\\Other4.jpg";
//String receivedImageFile = "F:\\tmp\\tt\\car1.jpg";
String receivedImageFile = "F:\\tmp\\tt\\car6.jpg";
//String receivedImageFile = "F:\\tmp\\tt\\car4.jpg";
//String receivedImageFile = "F:\\tmp\\tt\\car5.jpg";
//String receivedImageFile = "F:\\tmp\\tt\\car6.jpg";


String folderBase = "E:\\TestVideo\\TestAccuracy\\Car1_HondaOdyssey1217";
String videoFileBase = "E:\\TestVideo\\TestAccuracy\\Car1_HondaOdyssey1217\\OriginalData";




int main()
{
//	ScaleImage();
	//ScaleImage_SingleDirection();
	//ExtractImageFromVideo_ForOnePhone();

	//MatchingDiffAngle();
	//MatchingAllAngle_SameDistance_DifferentPhones();
//	MatchingSameAngle_AllDistance_DifferentPhones();
	//ExtractImgFromVideo();
	//MeasureDistance();
	MeasureDistance_GT_Self();
	//MeasureRatio();
	
	//MatchLeftRight();

	return 0;
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
	OrbMatching myMatcher;
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
