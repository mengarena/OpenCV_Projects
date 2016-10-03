//Detect Face


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

#if 0  //Solution 1

int main(int argc, const char** argv)
{    

	//create the cascade classifier object used for the face detection    
	CascadeClassifier face_cascade;    

	//use the haarcascade_frontalface_alt.xml library    
	face_cascade.load("haarcascade_frontalface_alt.xml");     
	
	//setup video capture device and link it to the first capture device    
	VideoCapture captureDevice;    
	captureDevice.open(0);     
	
	//setup image files used in the capture process    
	Mat captureFrame;    
	Mat grayscaleFrame;     
	
	//create a window to present the results    
	namedWindow("outputCapture", 1);     
	
	//create a loop to capture and find faces    
	while(true) {        
		//capture a new image frame        
		captureDevice>>captureFrame;         
		
		//convert captured image to gray scale and equalize        
		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);        
		equalizeHist(grayscaleFrame, grayscaleFrame);         
		
		//create a vector array to store the face found        
		std::vector<Rect> faces;         
		
		//find faces and store them in the vector array
		face_cascade.detectMultiScale( grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));         
		
		//draw a rectangle for all found faces in the vector array on the original image        
		for(int i = 0; i < faces.size(); i++) {            
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);            
			Point pt2(faces[i].x, faces[i].y);             
			rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);        
		}         
		
		//print the output        
		imshow("outputCapture", captureFrame);         
		//pause for 33ms        
		waitKey(33);    
	}     

	return 0;
}


#else  //Solution 2 (Detect face and eyes)

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

string window_name = "Capture - Face detection";
RNG rng(12345);

/** @function main */
int main( int argc, const char** argv )
{
	CvCapture* capture;
	Mat frame;

	//-- 1. Load the cascades
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

	//-- 2. Read the video stream
	capture = cvCaptureFromCAM( -1 );
	if( capture )
	{
		while( true )
		{
			frame = cvQueryFrame( capture );

			//-- 3. Apply the classifier to the frame
			if( !frame.empty() )
				{ detectAndDisplay( frame ); }
			else
				{ printf(" --(!) No captured frame -- Break!"); break; }

			int c = waitKey(10);
			if( (char)c == 'c' ) { break; }
		}
	}

	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	for( int i = 0; i < faces.size(); i++ )
	{
		Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
		ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

		Mat faceROI = frame_gray( faces[i] );
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

		for( int j = 0; j < eyes.size(); j++ )
		{
			Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
			int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
			circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
		}
	}

	//-- Show what you got
	imshow( window_name, frame );
}

#endif
