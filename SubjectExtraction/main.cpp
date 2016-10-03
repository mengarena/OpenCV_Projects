//Extract Vehicle

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv; 

String vehicle_cascade_name = "haarcascade_vehicle.xml";
String video_file = "E:\\TestVideo\\sample3.mp4";

int main()
{
	Mat originalFrame;
	Mat captureFrame; //Resized
	Mat grayscaleFrame;
	Mat roiFrame;
	int nDetectedCount;
	static int nFigNum = 0;
	char strSubjectFilename[100];
	int nWaitKey = 0;
	
	double fResizeFactor = 1.0;

	//create the cascade classifier object used for the face detection    
	CascadeClassifier vehicle_cascade;

	//use the haarcascade_frontalface_alt.xml library    
	vehicle_cascade.load(vehicle_cascade_name);     
	
	//setup video capture device and link it to the first capture device    
	VideoCapture captureDevice(video_file);   
	
	double framerate = captureDevice.get(CV_CAP_PROP_FPS);
	int delay = 1000/framerate;
	
	//Get total frames in the video
	int nFrameCount = captureDevice.get(CV_CAP_PROP_FRAME_COUNT);
	
	//create a window to present the results    
	namedWindow("outputCapture");     
	
	//create a loop to capture and find faces    
	while(true) {        
		//capture a new image frame        
		if (!captureDevice.read(originalFrame)) break;
		
		resize(originalFrame, captureFrame, Size(originalFrame.cols*fResizeFactor, originalFrame.rows*fResizeFactor));

		Rect rect(0, captureFrame.rows/3, captureFrame.cols, captureFrame.rows*2/3);

		roiFrame = captureFrame(rect);
		//convert captured image to gray scale and equalize        
		///cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);        
		cvtColor(roiFrame, grayscaleFrame, CV_BGR2GRAY);        

		equalizeHist(grayscaleFrame, grayscaleFrame);         
		
		//create a vector array to store the face found        
		std::vector<Rect> vehicles;         
		
		//find faces and store them in the vector array
		vehicle_cascade.detectMultiScale( grayscaleFrame, vehicles, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(30,30));         
		
		nDetectedCount = vehicles.size();

		//draw a rectangle for all found faces in the vector array on the original image        
		for(int i = 0; i < nDetectedCount; i++) {            
			Point pt1(vehicles[i].x + vehicles[i].width, vehicles[i].y + vehicles[i].height);            
			Point pt2(vehicles[i].x, vehicles[i].y);             
///			rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 2, 8, 0);        
			rectangle(roiFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);        

		}

		
		//print the output        
		imshow("outputCapture", roiFrame); 

//		if ( waitKey(delay) >= 0 ) break;

#if 1
		//pause
		if (nDetectedCount > 0) {
			nWaitKey = waitKey(2000);
		} else {
			nWaitKey = waitKey(33);
		}

		if ( nWaitKey == 's' ) {
			for(int j = 0; j < nDetectedCount; j++) {
				memset(strSubjectFilename, 0x00, 100);
				nFigNum++;
				sprintf(strSubjectFilename, "E:\\TestVideo\\SubjectVehicle_sample3Video\\subjectsamplevideo3_%d.jpg", nFigNum);
				Rect rect(vehicles[j].x+1, vehicles[j].y+1, vehicles[j].width-1, vehicles[j].height-1);
				imwrite(strSubjectFilename,roiFrame(rect));

			}
		} else if (nWaitKey == 'c') {
			continue;
		} else if (nWaitKey > 0) {
			break;
		}
#endif

	}

	captureDevice.release();
	
	return 0;

}