#include "OrbMatching.h"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;
using namespace cv; 


OrbMatching::OrbMatching(void):ratio(0.8f),distance(1.0),confidence(0.98),refineF(true)
{
}


OrbMatching::~OrbMatching(void)
{
}


void OrbMatching::setRatio(float rt)
{
	ratio = rt;
}


void OrbMatching::setDistance(double dst)
{
	distance = dst;
}


void OrbMatching::setConfidence(double confd)
{
	confidence = confd;
}


//Clear matches for which NN ratio is > threshold, return the number of removed points
//(corresponding entries are cleared)
int OrbMatching::ratioTest(vector<vector<DMatch>> &matches)
{
	int removed = 0;

	for (vector<vector<DMatch>>::iterator matchIterator = matches.begin(); matchIterator != matches.end(); ++matchIterator) {
		//If 2 NN has been identified
		if (matchIterator->size() > 1) {
			//Check distance ratio
			if ((*matchIterator)[0].distance/(*matchIterator)[1].distance > ratio) {
				matchIterator->clear();	//Remove match
				removed++;
			}
		} else {	//Does not have 2 neighbours
			matchIterator->clear();	//Remove match
			removed++;
		}
	}

	return removed;
}


//Symmetrical matches, save result in symMatches 
void OrbMatching::symmetryTest(const vector<vector<DMatch>>& matches1,const vector<vector<DMatch>>& matches2, vector<DMatch>& symMatches)
{
	//For all matches image1->image2
	for(vector<vector<DMatch>>::const_iterator matchIterator1 = matches1.begin(); matchIterator1 != matches1.end(); ++matchIterator1) {
		//Ignore deleted matches
		if (matchIterator1->size() < 2) continue;

		//For all matches image2->image1
		for(vector<vector<DMatch>>::const_iterator matchIterator2 = matches2.begin(); matchIterator2 != matches2.end(); ++matchIterator2) {
			//Ignore deleted matches
			if (matchIterator2->size() < 2) continue;

			//Match symmetry test
			if ((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx &&
				(*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx) {
					//Add symmetrical match
					symMatches.push_back(DMatch((*matchIterator1)[0].queryIdx, (*matchIterator1)[0].trainIdx, (*matchIterator1)[0].distance));
					break; //Next match in image1->image2
			}
		}
	}
}


void OrbMatching::ransacTest(const vector<DMatch>& matches, const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2, vector<DMatch>& outMatches)
{
	//Convert keypoints into Point2f
	vector<Point2f> points1,points2;

	for(vector<DMatch>::const_iterator it = matches.begin(); it != matches.end(); ++it) {
		//Get the position of left keypoints
		float x = keypoints1[it->queryIdx].pt.x;
		float y = keypoints1[it->queryIdx].pt.y;
		points1.push_back(Point2f(x,y));
		//Get the position of right keypoints
		x = keypoints2[it->trainIdx].pt.x;
		y = keypoints2[it->trainIdx].pt.y;
		points2.push_back(Point2f(x,y));
	}

	//Computer Fundamental matrix using RANSAC
	vector<uchar> inliers(points1.size(), 0);
	Mat fundamental = findFundamentalMat(Mat(points1), Mat(points2), inliers, CV_FM_RANSAC, distance, confidence);

	//Extract the surviving(inliers) matches
	vector<uchar>::const_iterator itIn = inliers.begin();
	vector<DMatch>::const_iterator itM = matches.begin();

	//For all matches
	for (; itIn != inliers.end(); ++itIn, ++itM) {
		if (*itIn) {	//It is a valid match
			outMatches.push_back(*itM);
		}
	}

#if 0
	if (refineF) {
		//The fundamental matrix will be recomputed with all accepted matches
		//Convert keypoints into Point2f for final fundamental computation
		points1.clear();
		points2.clear();

		for(vector<DMatch>::const_iterator it = outMatches.begin(); it != outMatches.end(); ++it) {
			//Get the position of left keypoints
			float x = keypoints1[it->queryIdx].pt.x;
			float y = keypoints1[it->queryIdx].pt.y;
			points1.push_back(Point2f(x,y));
			//Get the position of right keypoints
			x = keypoints2[it->trainIdx].pt.x;
			y = keypoints2[it->trainIdx].pt.y;
			points2.push_back(Point2f(x,y));
		}

		//Computer 8-point fundamental from all accepted matches
		fundamental = findFundamentalMat(Mat(points1), Mat(points2), CV_FM_8POINT);
	}

	//return fundamental
#endif

}


void OrbMatching::filterWithSlopeDistance(	Mat& image1, 
											Mat& image2, 
											const vector<KeyPoint>& keypoints1, 
											const vector<KeyPoint>& keypoints2, 
											const vector<DMatch>& inMatches,
											vector<DMatch>& finalMatches )
{
	//Two images will be merged together, so the x-axis value of the second image will be original x + width of image1
	float pi = 3.1416;
	int width1 = image1.cols;
	
	vector<float> pointsEuDist;
	vector<float> linesAngle;

	///////////////////////////////////////////////////////////////////////////////////////////
	//Calculate angle and length of lines between matched points in inMatches
	for(vector<DMatch>::const_iterator it = inMatches.begin(); it != inMatches.end(); ++it) {
		//Get the position of left keypoints
		float x1 = keypoints1[it->queryIdx].pt.x;
		float y1 = keypoints1[it->queryIdx].pt.y;

		//Get the position of right keypoints
		float x2 = keypoints2[it->trainIdx].pt.x + width1;
		float y2 = keypoints2[it->trainIdx].pt.y;

		float fEuDist = sqrt( pow((x2 - x1),2)*1.0 + pow((y2 - y1), 2) );
		float fAngle = atan( (y2 - y1)*1.0 /(x2 - x1) )*180/pi; //Get Degree

		pointsEuDist.push_back(fEuDist);
		linesAngle.push_back(fAngle);
	}


	//////////////////////////////////////////////////////////////////////////////////////
	//Filter by angles
	//Find out the most frequent angle
	//////////////////////////////////////////////////////////////////////////////////////	
	map<float, int>angleMap;
	map<float, int>::iterator itAngle;

	float fCurrentAngle, fTmpCurrentAngle;
	float maxAngle,minAngle;
	int nAngleRange = 15;
	int nFrequent = 0;

	for (int i=0; i<linesAngle.size(); i++) {
		fCurrentAngle = linesAngle.at(i);
		maxAngle = fCurrentAngle + nAngleRange;
		minAngle = fCurrentAngle - nAngleRange;

		nFrequent = 1;

		for (int j=0; j<linesAngle.size(); j++) {
			if (j!=i) {
				fTmpCurrentAngle = linesAngle.at(j);
				if ((fTmpCurrentAngle >= minAngle) && (fTmpCurrentAngle <= maxAngle)) {
					nFrequent = nFrequent + 1;
				}
			}
		}

		angleMap.insert(pair<float, int>(fCurrentAngle, nFrequent));
	}

	float mostCommonAngle = 0.0;
	int freNumAngle = 0;

	for ( itAngle = angleMap.begin(); itAngle != angleMap.end(); itAngle++ ) {
		if (itAngle->second > freNumAngle) {
			freNumAngle = itAngle->second;
			mostCommonAngle = itAngle->first;
		}
	}

	maxAngle = mostCommonAngle + nAngleRange;
	minAngle = mostCommonAngle - nAngleRange;


	//////////////////////////////////////////////////////////////////////////////////////
	//Filter by Eu distance
	//Find out the most frequent Euclidian distance
	//////////////////////////////////////////////////////////////////////////////////////
	map<float, int>euDistMap;
	map<float, int>::iterator itEuDist;

	float fCurrentEuDist, fTmpCurrentEuDist;
	float maxEuDist,minEuDist;
	float fEuDistRange = 0.20;
	int nEuDistFrequent = 0;

	for (int i=0; i<pointsEuDist.size(); i++) {
		fCurrentEuDist = pointsEuDist.at(i);
		maxEuDist = fCurrentEuDist*(1.0 + fEuDistRange);
		minEuDist = fCurrentEuDist*(1.0 - fEuDistRange);

		nEuDistFrequent = 1;

		for (int j=0; j<pointsEuDist.size(); j++) {
			if (j!=i) {
				fTmpCurrentEuDist = pointsEuDist.at(j);
				if ((fTmpCurrentEuDist >= minEuDist) && (fTmpCurrentEuDist <= maxEuDist)) {
					nEuDistFrequent = nEuDistFrequent + 1;
				}
			}
		}

		euDistMap.insert(pair<float, int>(fCurrentEuDist, nEuDistFrequent));
	}

	float mostCommonEuDist = 0.0;
	int freNumEuDist = 0;

	for ( itEuDist = euDistMap.begin(); itEuDist != euDistMap.end(); itEuDist++ ) {
		if (itEuDist->second > freNumEuDist) {
			freNumEuDist = itEuDist->second;
			mostCommonEuDist = itEuDist->first;
		}
	}

	maxEuDist = mostCommonEuDist*(1.0 + fEuDistRange);
	minEuDist = mostCommonEuDist*(1.0 - fEuDistRange);

	///////////////////////////////////////////////////////////////////
	//Final Process
	//Only the distance and angle of matched points is in the most common group, the matched points are valid
	///////////////////////////////////////////////////////////////////
	vector<DMatch>::const_iterator itM = inMatches.begin();
	vector<float>::const_iterator itAngleV = linesAngle.begin();
	vector<float>::const_iterator itEuDistV = pointsEuDist.begin();


	for (; itAngleV != linesAngle.end(); itAngleV++, itEuDistV++, itM++) {
		fCurrentAngle = *itAngleV;
		fCurrentEuDist = *itEuDistV;

		if ((fCurrentAngle >= minAngle) && (fCurrentAngle <= maxAngle) && (fCurrentEuDist >= minEuDist) && (fCurrentEuDist <= maxEuDist)) {
			finalMatches.push_back(*itM);

		}

	}

}


//vector<DMatch> OrbMatching::DoMatching(Mat& image1, Mat& image2, double &time)
vector<DMatch> OrbMatching::DoMatching(Mat &image1, Mat &image2, double &time, int &matchedCount, float &fMaxFeatureRatio, float &fAvgFeatureRatio, float &fEuDistRatio)
{
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	vector<DMatch> matches;

	matchedCount = 0;
	fMaxFeatureRatio = 0.0;
	fAvgFeatureRatio = 0.0;
	fEuDistRatio = 0.0;
	time = 0.0;

//	OrbFeatureDetector detector(1000);
	OrbFeatureDetector detector(1000, 1.1, 16);

	OrbDescriptorExtractor extractor;

	detector.detect(image1, keypoints1);
	if (keypoints1.size() == 0) {
		matches.clear();
		return matches;
	}


	extractor.compute(image1, keypoints1, descriptors1);
	if (descriptors1.empty()) {
		matches.clear();
		return matches;
	}

	//store the vocabulary
//	FileStorage fs("F:\\tmp\\descriptor11.txt", FileStorage::WRITE);
//	fs << "DES" << descriptors1;
//	fs.release();


//	Size matSize;

//	matSize = descriptors1.size();


	//Extract SURF feature points/feature descriptors for image 2
	detector.detect(image2, keypoints2);
	if (keypoints2.size() == 0) {
		matches.clear();
		return matches;
	}

	extractor.compute(image2, keypoints2, descriptors2);
	if (descriptors2.empty()) {
		matches.clear();
		return matches;
	}


	//Match the two image descriptors
/////	BruteForceMatcher<SL2<float>> matcher; //SL2  //BruteForceMatcher is old version
////	BFMatcher matcher(NORM_L2);
	BFMatcher matcher(NORM_HAMMING);

	//FlannBasedMatcher matcher;

	//From image1 to image2 based on k nearest neighbour (k=2)
	vector<vector<DMatch>> matches1;

	//matcher.match(descriptors1, descriptors2, matches);
	matcher.knnMatch(descriptors1, descriptors2, matches1, 2);

	//From image2 to image1 based on k nearest neighbour (k=2)
	vector<vector<DMatch>> matches2;
	matcher.knnMatch(descriptors2, descriptors1, matches2, 2);

	if (matches1.size() < 3 || matches2.size() < 3) {
		matches.clear();
		return matches;		
	}

	//Remove matches for which NN ratio is > threshold
	//Clean image1->image2 matches
	int removed = ratioTest(matches1);

	//Clean image2->image1 matches
	removed = ratioTest(matches2);

	//Remove non-symmetrical matches
	vector<DMatch> symMatches;
	symmetryTest(matches1, matches2, symMatches);

#if 0 //If with final slope & distance filter
	Mat imageMatchesFinal;
	drawMatches(image1, keypoints1, image2, keypoints2, symMatches, imageMatchesFinal, Scalar(0,0,255));
//	drawMatches(image1, keypoints1, image2, keypoints2, symMatches, imageMatches, Scalar(0,0,255));

	imwrite("f:\\tmp\\SurfMatchedAfterFinalFilter.jpg", imageMatchesFinal);
	namedWindow("Surf Matched Final");
	imshow("Surf Matched Final", imageMatchesFinal);

	waitKey(5000);
	return symMatches;

#endif


	if (symMatches.size() < 5) {
		//symMatches.clear();
		return symMatches;
	}

	//Validate matches using RANSAC
	ransacTest(symMatches, keypoints1, keypoints2, matches);

	if (matches.size() < 5) {
		//matches.clear();
		return matches;
	}


#if 1  //Fianl filter with Slope and Distance
	vector<DMatch> finalMatches;


	filterWithSlopeDistance(image1, image2, keypoints1, keypoints2, matches, finalMatches);
#if 1 ////


	float total = 0.0f;
	float fratio = 0.0f;
	float max1 = 0.0f;
	float max2 = 0.0f;
	for (int k = 0; k<finalMatches.size(); k++) {
//		cout<<"KeyPoints1.octave="<<keypoints1[matches.at(k).queryIdx].octave<<", KeyPoints2.octave="<<keypoints2[matches.at(k).trainIdx].octave<<endl;
		//cout<<"======Ratio="<<1.0*keypoints1[matches.at(k).queryIdx].octave/keypoints2[matches.at(k).trainIdx].octave<<endl;
	//	cout<<"KeyPoints1.scale="<<keypoints1[matches.at(k).queryIdx].size<<", KeyPoints2.scale="<<keypoints2[matches.at(k).trainIdx].size<<endl;
		/* Scale = size * 1.2/9 */
		fratio = keypoints1[finalMatches.at(k).queryIdx].size*1.2/9.0/(keypoints2[finalMatches.at(k).trainIdx].size*1.2/9.0);
//		cout<<"Scale Ratio="<<fratio<<endl;
		total = total + fratio;
		if (keypoints1[finalMatches.at(k).queryIdx].size > max1) max1 = keypoints1[finalMatches.at(k).queryIdx].size;
		if (keypoints2[finalMatches.at(k).trainIdx].size > max2) max2 = keypoints2[finalMatches.at(k).trainIdx].size;
	}

	int nIdx = finalMatches.size()/2;


	if (finalMatches.size() >= 2) {
		float fDist1 = 0.0; //The Euclidean distance of two matching feature points in Image 1
	
		float x11, y11, x12, y12;
		x11 = keypoints1[finalMatches.at(0).queryIdx].pt.x;
		y11 = keypoints1[finalMatches.at(0).queryIdx].pt.y;

		x12 = keypoints1[finalMatches.at(2).queryIdx].pt.x;
		y12 = keypoints1[finalMatches.at(2).queryIdx].pt.y;

		fDist1 = sqrt( pow((x12 - x11),2)*1.0 + pow((y12 - y11), 2) );

		float fDist2 = 0.0; //The Euclidean distance of two matching feature points in Image 1
		float x21, y21, x22, y22;
		x21 = keypoints2[finalMatches.at(0).trainIdx].pt.x;
		y21 = keypoints2[finalMatches.at(0).trainIdx].pt.y;

		x22 = keypoints2[finalMatches.at(2).trainIdx].pt.x;
		y22 = keypoints2[finalMatches.at(2).trainIdx].pt.y;

		fDist2 = sqrt( pow((x22 - x21),2)*1.0 + pow((y22 - y21), 2) );

		fEuDistRatio = fDist1/fDist2;
	}


//	cout<<"[Before Final filter] ==============" << matches.size() << endl;
//	cout<<"[After Final filter]================" << finalMatches.size() << endl;

//	cout<<"Average Ratio ====================================" << total/finalMatches.size()<<endl;
//	cout<<"Ratio from Max ==================================="<<max1/max2<<endl;
	fMaxFeatureRatio = max1/max2;   //Use Maxium Ratio
	fAvgFeatureRatio = total/finalMatches.size();
	matchedCount = finalMatches.size();
#endif ///

#else


#if 1 //////
	float total = 0.0f;
	float fratio = 0.0f;
	float max1 = 0.0f;
	float max2 = 0.0f;
	for (int k = 0; k<matches.size(); k++) {
//		cout<<"KeyPoints1.octave="<<keypoints1[matches.at(k).queryIdx].octave<<", KeyPoints2.octave="<<keypoints2[matches.at(k).trainIdx].octave<<endl;
		//cout<<"======Ratio="<<1.0*keypoints1[matches.at(k).queryIdx].octave/keypoints2[matches.at(k).trainIdx].octave<<endl;
		///cout<<"KeyPoints1.scale="<<keypoints1[matches.at(k).queryIdx].size<<", KeyPoints2.scale="<<keypoints2[matches.at(k).trainIdx].size<<endl;
		fratio = keypoints1[matches.at(k).queryIdx].size*1.2/9.0/(keypoints2[matches.at(k).trainIdx].size*1.2/9.0);
		///cout<<"Scale Ratio="<<fratio<<endl;
		total = total + fratio;
		if (keypoints1[matches.at(k).queryIdx].size > max1) max1 = keypoints1[matches.at(k).queryIdx].size;
		if (keypoints2[matches.at(k).trainIdx].size > max2) max2 = keypoints2[matches.at(k).trainIdx].size;
	}


//	cout<<"[Before Final filter] =========" << matches.size() << endl;

	float fEuDistRatio = 0.0;

	if (matches.size() >= 2) {
		float fDist1 = 0.0; //The Euclidean distance of two matching feature points in Image 1
	
		float x11, y11, x12, y12;
		x11 = keypoints1[matches.at(0).queryIdx].pt.x;
		y11 = keypoints1[matches.at(0).queryIdx].pt.y;

		x12 = keypoints1[matches.at(2).queryIdx].pt.x;
		y12 = keypoints1[matches.at(2).queryIdx].pt.y;

		fDist1 = sqrt( pow((x12 - x11),2)*1.0 + pow((y12 - y11), 2) );

		float fDist2 = 0.0; //The Euclidean distance of two matching feature points in Image 1
		float x21, y21, x22, y22;
		x21 = keypoints2[matches.at(0).trainIdx].pt.x;
		y21 = keypoints2[matches.at(0).trainIdx].pt.y;

		x22 = keypoints2[matches.at(2).trainIdx].pt.x;
		y22 = keypoints2[matches.at(2).trainIdx].pt.y;

		fDist2 = sqrt( pow((x22 - x21),2)*1.0 + pow((y22 - y21), 2) );

		fEuDistRatio = fDist1/fDist2;
	}

#endif  ////
//	cout<<"Euclidean Distance====================="<<fEuDistRatio<<endl;

//	cout<<"Average Ratio ====================================" << total/matches.size()<<endl;
//	cout<<"Ratio from Max ==================================="<<max1/max2<<endl;

#endif


	//Draw matching
///	Mat imageMatches;
///	drawMatches(image1, keypoints1, image2, keypoints2, matches, imageMatches, Scalar(0,0,255));
//	drawMatches(image1, keypoints1, image2, keypoints2, symMatches, imageMatches, Scalar(0,0,255));

	//imwrite("f:\\tmp\\kk.jpg", imageMatches);
///	namedWindow("Surf Matched");
///	imshow("Surf Matched", imageMatches);
	

	return finalMatches;

#if 1 //If with final slope & distance filter
	Mat imageMatchesFinal;
	drawMatches(image1, keypoints1, image2, keypoints2, finalMatches, imageMatchesFinal, Scalar(0,0,255));
//	drawMatches(image1, keypoints1, image2, keypoints2, symMatches, imageMatches, Scalar(0,0,255));

	imwrite("f:\\tmp\\SurfMatchedAfterFinalFilter.jpg", imageMatchesFinal);
	namedWindow("Surf Matched Final");
	imshow("Surf Matched Final", imageMatchesFinal);

	waitKey(5000);
	return finalMatches;
#else
	waitKey(10000);
	return matches;
#endif

}


