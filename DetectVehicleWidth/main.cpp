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


using namespace std;
using namespace cv; 

//String baseImageFile = "E:\\TestVideo\\Set1\\SelfTook.jpg";
//String baseImageFile = "E:\\TestVideo\\Set1\\self_fromOthers1.jpg";	//self_fromOthers1~2
//String baseImageFile = "E:\\TestVideo\\Set1\\self_back1.jpg"; //self_back1~3
//String baseImageFile = "E:\\TestVideo\\Set1\\self_light1.jpg"; //self_light1~2
//String baseImageFile = "E:\\TestVideo\\Set1\\othercar1_1.jpg"; //othercar1_1~3
//String baseImageFile = "E:\\TestVideo\\Set1\\othercar2_1.jpg"; //othercar2_1~2
//String baseImageFile = "E:\\TestVideo\\Set1\\othercar3_1.jpg"; //othercar3_1~5
//String baseImageFile = "E:\\TestVideo\\tmp_forlanemark\\sample2.png"

String baseImageFile = "D:\\good1\\selected\\adjusted\\712.png";
//String baseImageFile = "D:\\good1\\selected\\adjusted\\328.png";


vector<Vec4i> ExtendLines(vector<Vec4i> lines, int minX, int maxX, int minY, int maxY)
{
	vector<Vec4i> newLines;
	float fCurGradient, fTmpGradient;
	int nCurX1, nCurY1, nCurX2, nCurY2; 
	int nTmpX1, nTmpY1, nTmpX2, nTmpY2; 
	int nLeftMostIdx = -1;
	int nRightMostIdx = -1;

	int nLeftX = 9999;
	int nRightX = -9999;

	for( size_t i = 0; i < lines.size(); i++ )
	{
		nCurX1 = lines[i][0];
		nCurY1 = lines[i][1];
		nCurX2 = lines[i][2];
		nCurY2 = lines[i][3];

		fCurGradient = (nCurY2-nCurY1)*1.0/(nCurX2-nCurX1);

		if (fCurGradient > 0) {
			if (nCurX1 > nRightX) {
				nRightMostIdx = i;
				nRightX = nCurX1;
			}
		} else if (fCurGradient < 0) {
			if (nCurX2 < nLeftX) {
				nLeftMostIdx = i;
				nLeftX = nCurX2;
			}
		}

	
	}


	for( size_t i = 0; i < lines.size(); i++ )
    {
		nCurX1 = lines[i][0];
		nCurY1 = lines[i][1];
		nCurX2 = lines[i][2];
		nCurY2 = lines[i][3];

		fCurGradient = (nCurY2-nCurY1)*1.0/(nCurX2-nCurX1);

		if (fCurGradient > 0) {
			nTmpY2 = (int)((maxX - nCurX1)*fCurGradient + nCurY1);

			if (nTmpY2 <= maxY) {
				nCurX2 = maxX;
				nCurY2 = nTmpY2;
			} else {
				nTmpX2 = (int)((maxY - nCurY1)/fCurGradient + nCurX1);
				if (nTmpX2 <= maxX) {
					nCurX2 = nTmpX2;
					nCurY2 = maxY;
				}
			}
			
			if (i == nLeftMostIdx || i == nRightMostIdx) {
				nTmpY1 = (int)(nCurY2 - fCurGradient*(nCurX2 - minX));
				if (nTmpY1 >= minY) {
					nCurX1 = minX;
					nCurY1 = nTmpY1;
				} else {
					nTmpX1 = (int)(nCurX2 - (nCurY2-minY)/fCurGradient);
					if (nTmpX1 >= minX) {
						nCurX1 = nTmpX1;
						nCurY1 = minY;
					}
				}
			}	

		} else if (fCurGradient < 0) {
			nTmpY1 = (int)( nCurY2 - (nCurX2 -minX)*fCurGradient);
			if (nTmpY1 <= maxY) {
				nCurX1 = minX;
				nCurY1 = nTmpY1;
			} else {
				nTmpX1 = (int) ( nCurX2 - (nCurY2 - maxY)/fCurGradient);
				if (nTmpX1 >= minX) {
					nCurX1 = nTmpX1;
					nCurY1 = maxY;
				}
			}

			if (i == nLeftMostIdx || i == nRightMostIdx) {
				nTmpY2 = (int)(nCurY1 + (maxX-nCurX1)*fCurGradient);
				if (nTmpY2 >=minY) {
					nCurY2 = nTmpY2;
					nCurX2 = maxX;
				} else {
					nTmpX2 = (int)(nCurX1 + (minY-nCurY1)/fCurGradient);
					if (nTmpX2 <= maxX) {
						nCurY2 = minY;
						nCurX2 = nTmpX2;
					}
				}
			}
		} else {
			nCurX1 = minX;
			nCurX2 = maxX;
		}

		newLines.push_back(Vec4i(nCurX1,nCurY1,nCurX2,nCurY2));
	}

	return newLines;

}


vector<Vec4i> MergeLines(vector<Vec4i> lines)
{
	vector<Vec4i> newLines;
	float fLineLengh = 0.0;
	int nHeight, nWidth;
	float fCurGradient, fTmpGradient;
	int nCurX1, nCurY1, nCurX2, nCurY2; 
	int nTmpX1, nTmpY1, nTmpX2, nTmpY2; 
	int nSameDiriectionLineExist = 0;
	vector<int> vValidFlag;

	for (size_t i=0; i< lines.size(); i++) 
	{
		vValidFlag.push_back(1);
	}

    for( size_t i = 0; i < lines.size(); i++ )
    {
		if (vValidFlag[i] == 0) continue;

		nCurX1 = lines[i][0];
		nCurY1 = lines[i][1];
		nCurX2 = lines[i][2];
		nCurY2 = lines[i][3];
		fCurGradient = (nCurY2-nCurY1)*1.0/(nCurX2-nCurX1);
		
		for( size_t j = i+1; j < lines.size(); j++ )
		{
			nTmpX1 = lines[j][0];
			nTmpY1 = lines[j][1];
			nTmpX2 = lines[j][2];
			nTmpY2 = lines[j][3];
			fTmpGradient = (nTmpY2-nTmpY1)*1.0/(nTmpX2-nTmpX1);
			nSameDiriectionLineExist = 0;
			if ( ((fCurGradient * fTmpGradient > 0) && (abs(fCurGradient - fTmpGradient) < abs(fCurGradient)*0.12)) || 
				( (fCurGradient * fTmpGradient == 0) && (abs(fCurGradient - fTmpGradient) < abs(fCurGradient)*0.12) ) ) {  //Coule Merge   //0.08 for image 362

				if (fCurGradient >= 0) {
					if (nCurX1 > nTmpX1) nCurX1 = nTmpX1;
					if (nCurY1 > nTmpY1) nCurY1 = nTmpY1;
					if (nCurX2 < nTmpX2) nCurX2 = nTmpX2;
					if (nCurY2 < nTmpY2) nCurY2 = nTmpY2;
				} else {
					if (nCurX1 > nTmpX1) nCurX1 = nTmpX1;
					if (nCurY1 < nTmpY1) nCurY1 = nTmpY1;
					if (nCurX2 < nTmpX2) nCurX2 = nTmpX2;
					if (nCurY2 > nTmpY2) nCurY2 = nTmpY2;
				}

				//fCurGradient = (fCurGradient + fTmpGradient)/2.0;

				vValidFlag[j] = 0;
				nSameDiriectionLineExist = 1;
			}		
		}
		
		newLines.push_back(Vec4i(nCurX1,nCurY1,nCurX2,nCurY2));

	}

	return newLines;

}


int main()
{
	Mat baseImage = imread(baseImageFile);
	Mat grayImage;
	Mat contours;

	namedWindow("Original");
	imshow("Original",baseImage);

	cvtColor(baseImage, grayImage, CV_BGR2GRAY);

	cout<<"Channels:	"<<grayImage.channels()<<endl;
	Canny(grayImage, contours, 100, 200, 3 );

	namedWindow("Edge");
	imshow("Edge",contours);
	imwrite("F:\\tmp\\edges.jpg", contours);

	//waitKey(30000); 

	vector<Vec4i> lines;
	vector<Vec4i> newLines;
	vector<Vec4i> newNewLines;
	int nMyOffset = 177;

#if 0
	HoughLinesP( contours, lines, 
			1, CV_PI/180, //Resolution (step size) in searching
			grayImage.cols/4,  //threshold (votes)
			grayImage.cols/2,  //minLineLength
			grayImage.cols/10  //maxLineGap
			);
#endif

#if 1
	//Draw contour
	Mat baseImageC = imread(baseImageFile);
	Mat grayImageC, binaryImageC;
	Mat roiFrame;
	//Define ROI
	cv::Rect rect(30, nMyOffset, baseImageC.cols-30, baseImageC.rows-nMyOffset);
	//cv::Rect rect(captureFrame.cols/3, captureFrame.rows/3, captureFrame.cols*2/3, captureFrame.rows*2/3);

	roiFrame = baseImageC(rect);
	//convert captured image to gray scale and equalize        
	///cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);        
	cvtColor(roiFrame, grayImageC, CV_BGR2GRAY);        


	//cvtColor(baseImageC, grayImageC, CV_BGR2GRAY);
	threshold(grayImageC, binaryImageC, 192, 255, THRESH_BINARY);  //image 362:  215   image 712: 194
//	threshold(grayImageC, binaryImageC, 180, 255, THRESH_BINARY);

	cout<<"Width:	"<<grayImage.cols<<endl;

	if (binaryImageC.rows > 180) {
		HoughLinesP( binaryImageC, lines, 
				1, CV_PI/200, //Resolution (step size) in searching
				45,  //threshold (votes)
				binaryImageC.rows/20,  //minLineLength
				180  //maxLineGap
				);
	} else if ((binaryImageC.rows > 100) && (binaryImageC.rows <= 180)){
		HoughLinesP( binaryImageC, lines, 
				1, CV_PI/180, //Resolution (step size) in searching
				20,  //threshold (votes)
				binaryImageC.rows/20,  //minLineLength
				160  //maxLineGap
				);	
	} else {
		HoughLinesP( binaryImageC, lines, 
				1, CV_PI/180, //Resolution (step size) in searching
				15,  //threshold (votes)
				binaryImageC.rows/20,  //minLineLength
				140  //maxLineGap
				);	
	}


#endif

#if 0
	cout<<"Width:	"<<grayImage.cols<<endl;

	if (grayImage.cols > 180) {
		HoughLinesP( contours, lines, 
				1, CV_PI/180, //Resolution (step size) in searching
				25,  //threshold (votes)
				grayImage.cols/2,  //minLineLength
				15  //maxLineGap
				);
	} else if ((grayImage.cols > 100) && (grayImage.cols <= 180)){
		HoughLinesP( contours, lines, 
				1, CV_PI/180, //Resolution (step size) in searching
				20,  //threshold (votes)
				grayImage.cols/2,  //minLineLength
				12  //maxLineGap
				);	
	} else {
		HoughLinesP( contours, lines, 
				1, CV_PI/180, //Resolution (step size) in searching
				15,  //threshold (votes)
				grayImage.cols/2,  //minLineLength
				10  //maxLineGap
				);	
	}
#endif

	cout<<"Lines:	"<< lines.size()<<endl;
	float fLineLengh = 0.0;
	int nHeight, nWidth;

	newLines = MergeLines(lines);
	cout<<"New Lines:	"<< newLines.size()<<endl;


	newNewLines = ExtendLines(newLines, -30, baseImageC.cols, 0, baseImageC.rows);

    for( size_t i = 0; i < newNewLines.size(); i++ )
    {
		//if (i==3) continue;
		nHeight = abs(newNewLines[i][1] - newNewLines[i][3]);
		nWidth = abs(newNewLines[i][0] - newNewLines[i][2]);

		fLineLengh = sqrt(1.0*nHeight*nHeight + nWidth*nWidth);
		cout<<"NewLine["<<i<<"] Length="<<fLineLengh<<endl;
		cout<<"("<<newNewLines[i][0]<<","<<newNewLines[i][1]<<")"<<"---("<<newNewLines[i][2]<<","<<newNewLines[i][3]<<")"<<endl;

		if (nHeight*1.0 <=  fLineLengh/6) {  //If tilt >30 degree, get rid of it.
		} else {
//			line( binaryImageC, Point(lines[i][0], lines[i][1]),
//				Point(lines[i][2], lines[i][3]), Scalar(255,0,0), 2, 8 );  //baseImage
			line( baseImageC, Point(newNewLines[i][0]+30, newNewLines[i][1]+nMyOffset),Point(newNewLines[i][2]+30, newNewLines[i][3]+nMyOffset), Scalar(255,0,0), 3, 8);  //baseImage
		}
    }

#if 0
	int n=3;
	Mat oneline(contours.size(), CV_8U, Scalar(0));
	line(oneline, Point(lines[n][0], lines[n][1]),Point(lines[n][2], lines[n][3]), Scalar(255), 5);
	bitwise_and(contours, oneline, oneline);

	namedWindow("Oneline");
	imshow("Oneline",oneline);


	vector<Point> points;
	for(int y =0; y<oneline.rows; y++) {
		uchar* rowPtr = oneline.ptr<uchar>(y);

		for(int x=0; x<oneline.cols; x++) {
			if (rowPtr[x]) {
				points.push_back(Point(x,y));
			}
		}
	}


	Vec4f line1;
	fitLine(cv::Mat(points),line1, CV_DIST_L2, // distance type
											0, // not used with L2 distance 
									0.01,0.01);

#if 1

	int k = points.size();
	int x0= points.at(0).x;
	int y0= points.at(0).y;
	int xend = points.at(k-1).x;
	int yend = points.at(k-1).y;
	float linelength = sqrt( 1.0*(xend-x0)*(xend-x0) + (yend-y0)*(yend-y0) );

	int x1 = x0-linelength*line1[0];
	int y1 = y0+linelength*line1[1];
#else
	int x0 = line1[2];
	int y0 = line1[3];
	int x1 = x0 - 200*line1[0];
	int y1 = y0 - 200*line1[1];

#endif
	line(grayImage, Point(x0, y0), Point(x1,y1), Scalar(255,255,255), 3, 8);

	namedWindow("Fit line");
	imshow("Fit line",grayImage);

#endif

//	namedWindow("Vehicle Width");
//	imshow("Vehicle Width",baseImage);

	//imwrite("F:\\tmp\\withLine.jpg", baseImage);

#if 0
	//Draw contour
//	Mat baseImageC = imread(baseImageFile);
//	Mat grayImageC, binaryImageC;
	baseImageC = imread(baseImageFile);

	cvtColor(baseImageC, grayImageC, CV_BGR2GRAY);
//	threshold(grayImageC, binaryImageC, 120, 255, THRESH_BINARY);
	threshold(grayImageC, binaryImageC, 180, 255, THRESH_BINARY);

	imwrite("F:\\tmp\\laneMark.png", binaryImageC);
#endif

	namedWindow("Combined");
	imshow("Combined",baseImageC);
	imwrite("D:\\good1\\selected\\adjusted\\712_combined.png", baseImageC);

	namedWindow("Binary");
	imshow("Binary",binaryImageC);
	imwrite("D:\\good1\\selected\\adjusted\\712_binary.png", binaryImageC);


	//vector<vector<Point>> contoursC;
	//findContours(binaryImageC, contoursC, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE  );
	//Mat result(baseImageC.size(), CV_8U, Scalar(255));
	//drawContours(result, contoursC, -1, Scalar(0), 2);


	//namedWindow("Vehicle Contours");
	//imshow("Vehicle Contours",result);
	

	waitKey(80000); 

	return 0;
}

