//Detect Mouth

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

/** Function Headers */
void detectAndDisplay( Mat frame );
void detectAndDisplay_hand( Mat frame );

/** Global variables */
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String mouth_cascade_name = "haarcascade_mcs_mouth.xml";
String nose_cascade_name = "haarcascade_mcs_nose.xml";
String hand_cascade_name = "haarcascade_hand.xml";
//String hand_cascade_name = "Hand.Cascade.xml";
CascadeClassifier face_cascade;
CascadeClassifier mouth_cascade;
CascadeClassifier nose_cascade;
CascadeClassifier hand_cascade;

//string window_name = "Capture - Mouth & Nose detection";
string window_name = "Capture -Hand Detection";

RNG rng(12345);


/** @function main */
int main( int argc, const char** argv )
{

	CvCapture* capture;
	Mat frame;

	//-- 1. Load the cascades
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
//	if( !mouth_cascade.load( mouth_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
//	if( !nose_cascade.load( nose_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
//	if( !hand_cascade.load( hand_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

	//-- 2. Read the video stream
	capture = cvCaptureFromCAM( 0 );
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
void detectAndDisplay_hand( Mat frame )
{
	std::vector<Rect> hands;
	Mat frame_gray;

	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	hand_cascade.detectMultiScale( frame_gray, hands, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(100, 100) );

	for( int i = 0; i < hands.size(); i++ )
	{
		//Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
		//ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

		Point pt1(hands[i].x + hands[i].width, hands[i].y + hands[i].height);            
		Point pt2(hands[i].x, hands[i].y);             
		rectangle(frame, pt1, pt2, Scalar( 255, 255, 0 ), 1, 8, 0);        

	}

	//-- Show what you got
	imshow( window_name, frame );
}


#if 1
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
		continue;
		Mat faceROI = frame_gray( faces[i] );
		//std::vector<Rect> mouths;
		std::vector<Rect> noses;

		//-- In each face, detect eyes
		//mouth_cascade.detectMultiScale( faceROI, mouths, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

		//-- In each face, detect eyes
		nose_cascade.detectMultiScale( faceROI, noses, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30) );
#if 0
		for( int j = 0; j < mouths.size(); j++ )
		{
			Point center( faces[i].x + mouths[j].x + mouths[j].width*0.5, faces[i].y + mouths[j].y + mouths[j].height*0.5 );
			int radius = cvRound( (mouths[j].width + mouths[j].height)*0.25 );
			circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
		}
#endif

		for(int m = 0; m < noses.size(); m++) {            
			Point pt1(noses[m].x + noses[m].width, noses[m].y + noses[m].height);            
			Point pt2(noses[m].x, noses[m].y);             
			rectangle(frame, pt1, pt2, Scalar( 255, 255, 0 ), 1, 8, 0);        
		}         

	}

	//-- Show what you got
	imshow( window_name, frame );
}

#endif
