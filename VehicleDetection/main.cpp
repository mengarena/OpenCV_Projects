//Detect Vehicle

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>

#include "Base.h"
#include "SubBase.h"


using namespace std;
using namespace cv; 


String vehicle_cascade_name = "haarcascade_vehicle.xml";
//String vehicle_cascade_name = "cascade_color.xml";
//String vehicle_cascade_name = "cascade_gray.xml";
//String vehicle_cascade_name = "cascade.xml";

//String vehicle_cascade_name = "cars3.xml";


String video_file1 = "E:\\TestVideo\\TestAccuracy\\GN_VID_20131229_144550.mp4";
String video_file2 = "E:\\TestVideo\\TestAccuracy\\GN_VID_20131229_150217.mp4";

String video_file3 = "E:\\TestVideo\\TestAccuracy\\VID_20131222_152312.mp4";  //Rotate
String video_file4 = "E:\\TestVideo\\TestAccuracy\\VID_20131226_151743.mp4";  //Rotate

String video_file5 = "E:\\TestVideo\\TestAccuracy\\VID_20131228_151835.mp4"; 
String video_file6 = "E:\\TestVideo\\TestAccuracy\\VID_20131231_135157.mp4"; 
String video_file7 = "E:\\TestVideo\\TestAccuracy\\VID_20131231_141058.mp4"; 

String video_file8 = "F:\\HomeToSchool.mp4"; 
String video_file9 = "E:\\HomeToSchool.mp4"; 

String video_file10 = "E:\\TestVideo\\ToProcess_forSkyEye\\SelfVideo08.mp4"; 
String video_file11 = "E:\\TestVideo\\ToProcess_forSkyEye\\SelfVideo09.mp4"; 
String video_file12 = "E:\\TestVideo\\ToProcess_forSkyEye\\SelfVideo10.mp4"; 
String video_file13 = "E:\\TestVideo\\sample1.mp4"; 


//String detected_file = "E:\\TestVideo\\sample1_detected.avi";
//String video_file = "E:\\TestVideo\\ToProcess_forSkyEye\\VID_20130511_160530.mp4";
//String video_file = "E:\\TestVideo\\ToProcess_forSkyEye\\SelfVideo06.mp4";

String saveFile = "D:\\DetectedVehicleSets10\\";
String saveFileBig = "D:\\DetectedVehicleSets10\\big\\";


long int m_nImageSetIdx = 0;

ofstream myfile;


Mat rotateImage(const Mat& source, double angle)
{
    Point2f src_center(source.cols/2.0F, source.rows/2.0F);
    Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);
    Mat dst;
    warpAffine(source, dst, rot_mat, source.size());
    return dst;
}



void detectVehicle_OnlySaveFrame(String strVideoFile, int nRotate, int nFrequency)
{
	int nCount1 = 0;
	int nCount2 = 0;
	int nCount3better = 0;
	int nMaxNum = 0;
	int nDetectedCount;
	Mat originalFrame;
	Mat captureFrame; //Resized
	Mat grayscaleFrame;
	Mat roiFrame;
	char strNegFile[150];

	String saveFolder = "D:\\FromSample1\\";

	double fResizeFactor = 1.0;

	char strOutFile[120];

	char strImageSetFolder[120];
	char strDetectedImageFile[120];
	char strCarFile[120];

	static long nDetectedFrameCnt = 0;
	//create the cascade classifier object used for the face detection    
	CascadeClassifier vehicle_cascade;


	//use the haarcascade_frontalface_alt.xml library    
	vehicle_cascade.load(vehicle_cascade_name);     
	
	//setup video capture device and link it to the first capture device    
	VideoCapture captureDevice(strVideoFile);   
	//VideoWriter outputVideo;
	
	//Don't Write int codec = static_cast<int>(captureDevice.get(CV_CAP_PROP_FOURCC));
	double framerate = captureDevice.get(CV_CAP_PROP_FPS);
	int delay = (1000/framerate)/2;
	

	//Get total frames in the video
	int nFrameCount = captureDevice.get(CV_CAP_PROP_FRAME_COUNT);
		

	Mat originalFrame0;

	long nCheckIdx = 0;

	//create a loop to capture and find faces    
	while(true) {        
		//capture a new image frame        
		if (!captureDevice.read(originalFrame)) break;

		nCheckIdx = ( nCheckIdx + 1) % nFrequency;  //Take a frame every two seconds
 		if (nCheckIdx != 0) continue;

		if (nRotate == 1) {
			originalFrame = rotateImage(originalFrame, 180);
		}

		resize(originalFrame, captureFrame, Size(originalFrame.cols*fResizeFactor, originalFrame.rows*fResizeFactor));
		//Define ROI
		cv::Rect rect(0, captureFrame.rows/3, captureFrame.cols, captureFrame.rows*2/3);
		//cv::Rect rect(captureFrame.cols/3, captureFrame.rows/3, captureFrame.cols*2/3, captureFrame.rows*2/3);

		roiFrame = captureFrame(rect);
		//convert captured image to gray scale and equalize        
		///cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);        
		cvtColor(roiFrame, grayscaleFrame, CV_BGR2GRAY);        

		equalizeHist(grayscaleFrame, grayscaleFrame);         
		
		//create a vector array to store the face found        
		std::vector<Rect> vehicles;         
		
		//find faces and store them in the vector array
		vehicle_cascade.detectMultiScale( grayscaleFrame, vehicles, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(50,50));         
		
		nDetectedCount = vehicles.size();

		if (nDetectedCount >= 1) 
			//cout<<"Detected: " << nDetectedCount <<endl;

		if (nDetectedCount == 1) {
			nCount1++;
		} else if (nDetectedCount == 2) {
			nCount2++;
		} else if (nDetectedCount > 2) {
			nCount3better++;
		}

		if (nDetectedCount > nMaxNum) nMaxNum = nDetectedCount;

		if (nDetectedCount >= 2) {
			cout<<"Detected: " << nDetectedCount <<endl;

			//draw a rectangle for all found vehicles in the vector array on the original image        
			for(int i = 0; i < nDetectedCount; i++) {
				//cout<<"Width="<<vehicles[i].width<<endl;;
				Point pt1(vehicles[i].x + vehicles[i].width, vehicles[i].y + vehicles[i].height);            
				Point pt2(vehicles[i].x, vehicles[i].y);

				//rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 2, 8, 0);     
				rectangle(roiFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 3, 8, 0);        

			}

			nDetectedFrameCnt = nDetectedFrameCnt + 1;
			memset(strOutFile, 0x00, 120);
			sprintf(strOutFile, "%s%ld%s",saveFolder.c_str(), nDetectedFrameCnt, ".png");
			imwrite(strOutFile, roiFrame);
		}

	}


	captureDevice.release();

}




void detectVehicle(String strVideoFile, int nRotate, int nFrequency)
{
	int nCount1 = 0;
	int nCount2 = 0;
	int nCount3better = 0;
	int nMaxNum = 0;
	int nDetectedCount;
	Mat originalFrame;
	Mat captureFrame; //Resized
	Mat grayscaleFrame;
	Mat roiFrame;
	char strNegFile[150];
	static int nFileIdx = 1474;

	double fResizeFactor = 1.0;

	char strOutFile[120];

	char strImageSetFolder[120];
	char strDetectedImageFile[120];
	char strCarFile[120];

	static long nDetectedFrameCnt = 0;
	//create the cascade classifier object used for the face detection    
	CascadeClassifier vehicle_cascade;


	//use the haarcascade_frontalface_alt.xml library    
	vehicle_cascade.load(vehicle_cascade_name);     
	
	//setup video capture device and link it to the first capture device    
	VideoCapture captureDevice(strVideoFile);   
	//VideoWriter outputVideo;

	//captureDevice.open(0);    //Open default camera 
	
	//Don't Write int codec = static_cast<int>(captureDevice.get(CV_CAP_PROP_FOURCC));
	double framerate = captureDevice.get(CV_CAP_PROP_FPS);
	int delay = (1000/framerate)/2;
	
#if 0 //Don't Write 
	Size s = Size((int)(captureDevice.get(CV_CAP_PROP_FRAME_WIDTH)*fResizeFactor), (int)(captureDevice.get(CV_CAP_PROP_FRAME_HEIGHT)*fResizeFactor));

	outputVideo.open(detected_file, -1, (int)(framerate/10), s, true);

	if (!outputVideo.isOpened()) {
        cout  << "Could not open the output video for write"<< endl;
        return -1;
    } else {
		cout << "Writing Ready!" <<endl;
	}
#endif

	//HOGDescriptor hog;
	//hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	//Get total frames in the video
	int nFrameCount = captureDevice.get(CV_CAP_PROP_FRAME_COUNT);
	
	//create a window to present the results    
	//namedWindow("outputCapture", 1);     
	

	Mat originalFrame0;

	long nCheckIdx = 0;

	//create a loop to capture and find faces    
	while(true) {        
		//capture a new image frame        
		if (!captureDevice.read(originalFrame)) break;

		nCheckIdx = ( nCheckIdx + 1) % nFrequency;  //Take a frame every two seconds
 		if (nCheckIdx != 0) continue;

		if (nRotate == 1) {
			originalFrame = rotateImage(originalFrame, 180);
		}

		resize(originalFrame, captureFrame, Size(originalFrame.cols*fResizeFactor, originalFrame.rows*fResizeFactor));
		//Define ROI
		cv::Rect rect(0, captureFrame.rows/3, captureFrame.cols, captureFrame.rows*2/3);
		//cv::Rect rect(captureFrame.cols/3, captureFrame.rows/3, captureFrame.cols*2/3, captureFrame.rows*2/3);

		roiFrame = captureFrame(rect);
		//convert captured image to gray scale and equalize        
		///cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);        
		cvtColor(roiFrame, grayscaleFrame, CV_BGR2GRAY);        

		equalizeHist(grayscaleFrame, grayscaleFrame);         
		
		//create a vector array to store the face found        
		std::vector<Rect> vehicles;         
		
		//find faces and store them in the vector array
		vehicle_cascade.detectMultiScale( grayscaleFrame, vehicles, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(70,70));         
		
		nDetectedCount = vehicles.size();

		if (nDetectedCount >= 1) 
			//cout<<"Detected: " << nDetectedCount <<endl;

		if (nDetectedCount == 1) {
			nCount1++;
		} else if (nDetectedCount == 2) {
			nCount2++;
		} else if (nDetectedCount > 2) {
			nCount3better++;
		}

		if (nDetectedCount > nMaxNum) nMaxNum = nDetectedCount;

		if (nDetectedCount >= 2) {
			cout<<"Detected: " << nDetectedCount <<endl;
			//First create folder
			m_nImageSetIdx = m_nImageSetIdx + 1;
			memset(strImageSetFolder, 0x00, 120);
			sprintf(strImageSetFolder, "%s%d", saveFile.c_str(), m_nImageSetIdx);
			mkdir(strImageSetFolder);
			myfile<<m_nImageSetIdx<<","<<nDetectedCount<<"\n";

			//draw a rectangle for all found vehicles in the vector array on the original image        
			for(int i = 0; i < nDetectedCount; i++) {
				//cout<<"Width="<<vehicles[i].width<<endl;;
				Point pt1(vehicles[i].x + vehicles[i].width, vehicles[i].y + vehicles[i].height);            
				Point pt2(vehicles[i].x, vehicles[i].y);
	#if 0
				//Write into file
				Rect rect(vehicles[i].x, vehicles[i].y, vehicles[i].width, vehicles[i].height);
				memset(strNegFile, 0x00, 150);
				nFileIdx = nFileIdx +1;
				sprintf(strNegFile, "%s\\car_%d.jpg", saveFile.c_str(), nFileIdx);
				//cout<<strNegFile<<endl;
				imwrite(strNegFile, roiFrame(rect));
	#endif

				//Write into file
				Rect rect(vehicles[i].x, vehicles[i].y, vehicles[i].width, vehicles[i].height);
				memset(strCarFile, 0x00, 120);
				sprintf(strCarFile, "%s\\car_%d.jpg", strImageSetFolder, i+1);
				//cout<<strNegFile<<endl;
				imwrite(strCarFile, roiFrame(rect));
				//rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 2, 8, 0);     
				rectangle(roiFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 3, 8, 0);        

			}

			nDetectedFrameCnt = nDetectedFrameCnt + 1;
			memset(strOutFile, 0x00, 120);
			sprintf(strOutFile, "%s%ld%s", saveFileBig.c_str(), nDetectedFrameCnt, ".png");
			imwrite(strOutFile, roiFrame);
		}

		//Write frames into video
		//outputVideo.write(captureFrame);
		
		//print the output        
		//imshow("outputCapture", captureFrame); 
		//imshow("outputCapture", roiFrame); 
#if 0
		if (nDetectedCount > 0) {
			//Write roiFrame into file
			nDetectedFrameCnt = nDetectedFrameCnt + 1;
			memset(strOutFile, 0x00, 120);
			sprintf(strOutFile, "%s%d%s", "E:\\TestVideo\\tmp\\tmp1\\frame_", nDetectedFrameCnt, ".jpg");
			imwrite(strOutFile, roiFrame);
		}
#endif
		//pause        
		//if ( waitKey(delay) >= 0 ) break;
		//waitKey(5);
//		vehicles.clear();
//		captureFrame.release();
//		originalFrame.release();
//		grayscaleFrame.release();
	}

//	durationframe = static_cast<double>(getTickCount())-durationframe;
//	durationframe /= getTickFrequency(); // the elapsed time in s

	captureDevice.release();
	//outputVideo.release();

}

void createFolder()
{
	char strImageSetFolder[120];

	for (int i=1001; i<=1200; i++) {
		memset(strImageSetFolder, 0x00, 120);
		sprintf(strImageSetFolder, "%s%d", "F:\\ForDiversityFrame\\scene", i);
		mkdir(strImageSetFolder);
	}

}

int main(int argc, const char** argv)
{    
	int nCount1 = 0;
	int nCount2 = 0;
	int nCount3better = 0;
	int nMaxNum = 0;
	int nDetectedCount;
	Mat originalFrame;
	Mat captureFrame; //Resized
	Mat grayscaleFrame;
	Mat roiFrame;
	char strNegFile[150];
	static int nFileIdx = 1474;

	double fResizeFactor = 1.0;

	double durationframe; //Duration for processing each frame
	double duration; //Duration for processing the total video file

	char strOutFile[120];
	int nDetectedFrmCnt = 0;

	Base *pp = new SubBase();

	delete pp;

	getchar();

	return 0;

	//In folderInfo.csv, each line has the information about subfolder name and the number of images in the subfolder.
	//myfile.open ("D:\\DetectedVehicleSets10\\folderInfo.csv", ofstream::out | ofstream::app);

	m_nImageSetIdx = 0;


	cout<<"Running*****************************************"<<endl;

	createFolder();
#if 1
	//cout<<"Processing....1......."<<video_file1<<endl;
	//detectVehicle(video_file1, 0, 5);

	//cout<<"Processing....2......."<<video_file2<<endl;
	//detectVehicle(video_file2, 0, 5);
	
	//cout<<"Processing....3......."<<video_file3<<endl;
	//detectVehicle(video_file3, 1, 5);
	
	//cout<<"Processing....4......."<<video_file4<<endl;
	//detectVehicle(video_file4, 1, 5);

	//cout<<"Processing....5......."<<video_file5<<endl;
	//detectVehicle(video_file5, 0, 5);

	//cout<<"Processing....6......."<<video_file6<<endl;
	//detectVehicle(video_file6, 0, 5);

	//cout<<"Processing....7......."<<video_file7<<endl;
	//detectVehicle(video_file7, 0, 5);

	//cout<<"Processing....8......."<<video_file8<<endl;
	//detectVehicle(video_file8, 1, 5);
	
	//cout<<"Processing....9......."<<video_file9<<endl;
	//detectVehicle(video_file9, 1, 5);
#endif

	//cout<<"Processing....10......."<<video_file10<<endl;
	//detectVehicle(video_file10, 1, 5);
	
	//cout<<"Processing....11......."<<video_file11<<endl;
	//detectVehicle(video_file11, 1, 5);

	//cout<<"Processing....12......."<<video_file12<<endl;
	//detectVehicle(video_file12, 1, 5);

	//cout<<"Processing....13......."<<video_file13<<endl;
	//detectVehicle_OnlySaveFrame(video_file13, 0, 5);

	cout<<"Done*****************************************"<<endl;
	//myfile.close();


	getchar();
	return 0;



	duration = static_cast<double>(getTickCount());

	//create the cascade classifier object used for the face detection    
	CascadeClassifier vehicle_cascade;

	//use the haarcascade_frontalface_alt.xml library    
	vehicle_cascade.load(vehicle_cascade_name);     
	
	//setup video capture device and link it to the first capture device    
	VideoCapture captureDevice(video_file1);   
	//VideoWriter outputVideo;

	//captureDevice.open(0);    //Open default camera 
	
	//Don't Write int codec = static_cast<int>(captureDevice.get(CV_CAP_PROP_FOURCC));
	double framerate = captureDevice.get(CV_CAP_PROP_FPS);
	int delay = (1000/framerate)/2;
	
#if 0 //Don't Write 
	Size s = Size((int)(captureDevice.get(CV_CAP_PROP_FRAME_WIDTH)*fResizeFactor), (int)(captureDevice.get(CV_CAP_PROP_FRAME_HEIGHT)*fResizeFactor));

	outputVideo.open(detected_file, -1, (int)(framerate/10), s, true);

	if (!outputVideo.isOpened()) {
        cout  << "Could not open the output video for write"<< endl;
        return -1;
    } else {
		cout << "Writing Ready!" <<endl;
	}
#endif

	//HOGDescriptor hog;
	//hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	//Get total frames in the video
	int nFrameCount = captureDevice.get(CV_CAP_PROP_FRAME_COUNT);
	
	//create a window to present the results    
	//namedWindow("outputCapture", 1);     
	
	durationframe = static_cast<double>(getTickCount());

	Mat originalFrame0;

	long nCheckIdx = 0;



	//create a loop to capture and find faces    
	while(true) {        
		//capture a new image frame        
		if (!captureDevice.read(originalFrame)) break;

		nCheckIdx = ( nCheckIdx + 1) % 12;  //Take a frame every two seconds
 		if (nCheckIdx != 0) continue;

		//originalFrame = rotateImage(originalFrame, 180);

		resize(originalFrame, captureFrame, Size(originalFrame.cols*fResizeFactor, originalFrame.rows*fResizeFactor));
		//Define ROI
		cv::Rect rect(0, captureFrame.rows/3, captureFrame.cols, captureFrame.rows*2/3);
		//cv::Rect rect(captureFrame.cols/3, captureFrame.rows/3, captureFrame.cols*2/3, captureFrame.rows*2/3);

		roiFrame = captureFrame(rect);
		//convert captured image to gray scale and equalize        
		///cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);        
		cvtColor(roiFrame, grayscaleFrame, CV_BGR2GRAY);        

		equalizeHist(grayscaleFrame, grayscaleFrame);         
		
		//create a vector array to store the face found        
		std::vector<Rect> vehicles;         
		
		//find faces and store them in the vector array
		vehicle_cascade.detectMultiScale( grayscaleFrame, vehicles, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(40,40));         
		
		nDetectedCount = vehicles.size();

		if (nDetectedCount >= 1) 
			//cout<<"Detected: " << nDetectedCount <<endl;

		if (nDetectedCount == 1) {
			nCount1++;
		} else if (nDetectedCount == 2) {
			nCount2++;
		} else if (nDetectedCount > 2) {
			nCount3better++;
		}

		if (nDetectedCount > nMaxNum) nMaxNum = nDetectedCount;

		if (nDetectedCount >= 3) {
		//draw a rectangle for all found vehicles in the vector array on the original image        
		for(int i = 0; i < nDetectedCount; i++) {
			//cout<<"Width="<<vehicles[i].width<<endl;;
			Point pt1(vehicles[i].x + vehicles[i].width, vehicles[i].y + vehicles[i].height);            
			Point pt2(vehicles[i].x, vehicles[i].y);
#if 0
			//Write into file
			Rect rect(vehicles[i].x, vehicles[i].y, vehicles[i].width, vehicles[i].height);
			memset(strNegFile, 0x00, 150);
			nFileIdx = nFileIdx +1;
			sprintf(strNegFile, "%s\\car_%d.jpg", saveFile.c_str(), nFileIdx);
			//cout<<strNegFile<<endl;
			imwrite(strNegFile, roiFrame(rect));
#endif
			//rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 2, 8, 0);     
			rectangle(roiFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 2, 8, 0);        

		}

		nDetectedFrmCnt = nDetectedFrmCnt + 1;
		memset(strOutFile, 0x00, 120);
		sprintf(strOutFile, "%s%d%s", saveFile, nDetectedFrmCnt, ".jpg");
		imwrite(strOutFile, roiFrame);
		}

		//Write frames into video
		//outputVideo.write(captureFrame);
		
		//print the output        
		//imshow("outputCapture", captureFrame); 
		//imshow("outputCapture", roiFrame); 
#if 0
		if (nDetectedCount > 0) {
			//Write roiFrame into file
			nDetectedFrameCnt = nDetectedFrameCnt + 1;
			memset(strOutFile, 0x00, 120);
			sprintf(strOutFile, "%s%d%s", "E:\\TestVideo\\tmp\\tmp1\\frame_", nDetectedFrameCnt, ".jpg");
			imwrite(strOutFile, roiFrame);
		}
#endif
		//pause        
		//if ( waitKey(delay) >= 0 ) break;
		//waitKey(5);
//		vehicles.clear();
//		captureFrame.release();
//		originalFrame.release();
//		grayscaleFrame.release();
	}

//	durationframe = static_cast<double>(getTickCount())-durationframe;
//	durationframe /= getTickFrequency(); // the elapsed time in s

	captureDevice.release();
	//outputVideo.release();

//	duration = static_cast<double>(getTickCount())-duration;
//	duration /= getTickFrequency(); // the elapsed time in s
	
	
	cout<<"---------------------------------------------------------"<<endl;
	cout<<"Frames in file:	"<<nFrameCount<<endl;
	cout<<endl;
	cout<<"Detected	ONE Vechiles	" << nCount1 << "	Times" << endl;
	cout<<"Detected	TWO Vechiles	" << nCount2 << "	Times" << endl;
	cout<<"Detected	MORE Vechiles	" << nCount3better << "	Times" << endl;
	cout<<endl;
	cout<<"Max:	" << nMaxNum <<endl;
	//cout<<"Total Time:	"<<duration<<"	s"<<endl;
	//cout<<"Average Time per Frame:	"<< durationframe*1000.0/nFrameCount << "	ms" <<endl;
	//cout<<"Detection Rate:	" << (1.0*(nCount1+nCount2+nCount3better)/nFrameCount)*100.0 <<endl;
	cout<<"---------------------------------------------------------"<<endl;


	waitKey(5000);
	getchar();
	return 0;
}
