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


vector<KeyPoint> OrbMatching::GetRequiredKeypoint(Mat& image, int nRequiredKeypointNum)
{
	vector<KeyPoint> keypoints;
	Ptr<FeatureDetector> detector;
	int i;
	int nExpectedStartNum = 0;
	int nExpectedEndNum = 0;
	int nKeypointNum = 0;

	if (nRequiredKeypointNum == 20) {
		nExpectedStartNum = 0;
		nExpectedEndNum = nRequiredKeypointNum;
	} else if (nRequiredKeypointNum == 40 ||
		nRequiredKeypointNum == 60 ||
		nRequiredKeypointNum == 80 ||
		nRequiredKeypointNum == 100 ||
		nRequiredKeypointNum == 120 ||
		nRequiredKeypointNum == 140 ||
		nRequiredKeypointNum == 160 ||
		nRequiredKeypointNum == 180 ||
		nRequiredKeypointNum == 200) {
		nExpectedStartNum = nRequiredKeypointNum - 19;
		nExpectedEndNum = nRequiredKeypointNum;
	} else if (nRequiredKeypointNum == 250) {
		nExpectedStartNum = nRequiredKeypointNum - 49;
		nExpectedEndNum = nRequiredKeypointNum;
	} else if (nRequiredKeypointNum == 300) {
		nExpectedStartNum = nRequiredKeypointNum - 49;
		nExpectedEndNum = nRequiredKeypointNum;		
	} else if (nRequiredKeypointNum == 500) {
		nExpectedStartNum = nRequiredKeypointNum - 199;
		nExpectedEndNum = nRequiredKeypointNum;
	} else if (nRequiredKeypointNum == 1000) {
		nExpectedStartNum = 0;
		nExpectedEndNum = nRequiredKeypointNum + 10000;		
	}

	i=nRequiredKeypointNum;
	while(i<=1000) {
//		OrbFeatureDetector detector(i);
		OrbFeatureDetector detector(i, 1.1, 10);

		detector.detect(image, keypoints);
		nKeypointNum = keypoints.size();

		if (nKeypointNum >= nExpectedStartNum && nExpectedStartNum <= nExpectedEndNum) {
			//cout<<nKeypointNum<<endl;
			return keypoints;
		}

		i = i + 5;
	}

	return keypoints;

}



vector<DMatch> OrbMatching::DoMatching(Mat& image1, Mat& image2, int nRequiredKeypointNum, int &nNumKeypoint1, int &nNumKeypoint2)
{
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	vector<DMatch> matches;

//	OrbFeatureDetector detector(nFeatureNum, 1.2, 10); 
///	OrbFeatureDetector detector(1000, 1.2, 5);
/////	OrbFeatureDetector detector(nRequiredKeypointNum); 
	OrbDescriptorExtractor extractor;

	/////detector.detect(image1, keypoints1);

	keypoints1 = GetRequiredKeypoint(image1, nRequiredKeypointNum);
	nNumKeypoint1 = keypoints1.size();

	if (keypoints1.size() == 0) {
		matches.clear();
		return matches;
	}


	extractor.compute(image1, keypoints1, descriptors1);
//[Begin]
	Size matSize;

	matSize = descriptors1.size();

//	featureSize1 = descriptors1.elemSize()* matSize.width * matSize.height;  //Bytes
#if 0
	cout<<"[Size] [Cols]= " <<matSize.width <<" ,[Rows]= "<<matSize.height<<endl;
	cout<<"[Channel]= "<<descriptors1.channels()<<endl;
	cout<<"[Depth]= "<<descriptors1.depth()<<endl;
	cout<<"[Element Size]= "<<descriptors1.elemSize()<<endl;
	cout<<"[size of element channel]= " <<descriptors1.elemSize1()<<endl;
	cout<<"[Step0]= "<<descriptors1.step[0]<<",[Step1]="<<descriptors1.step[1]<<endl;
	cout<<"KeypointSize="<<sizeof(KeyPoint)<<",Keypoint number="<<keypoints1.size()<<",KeypointSize="<<keypoints1.size()*sizeof(KeyPoint)<<",DescriptorSize="<<featureSize1<<endl;
#endif
//	featureSize1 = featureSize1 + keypoints1.size()*sizeof(KeyPoint);

//	matSize = descriptors1.size();

	//Extract ORB feature points/feature descriptors for image 2
	///detector.detect(image2, keypoints2);
	keypoints2 = GetRequiredKeypoint(image2, nRequiredKeypointNum);
	nNumKeypoint2 = keypoints2.size();
	if (keypoints2.size() == 0) {
		matches.clear();
		return matches;
	}

	extractor.compute(image2, keypoints2, descriptors2);

//[Begin]
	matSize = descriptors2.size();
//	featureSize2 = descriptors2.elemSize()* matSize.width * matSize.height;  //Bytes
//	featureSize2 = featureSize2 + keypoints2.size()*sizeof(KeyPoint);

//[End]

	//Match the two image descriptors
	BFMatcher matcher(NORM_HAMMING);  //ORB

	//From image1 to image2 based on k nearest neighbour (k=2)
	vector<vector<DMatch>> matches1;

	//matcher.match(descriptors1, descriptors2, matches);
	matcher.knnMatch(descriptors1, descriptors2, matches1, 2);

	//From image2 to image1 based on k nearest neighbour (k=2)
	vector<vector<DMatch>> matches2;
	matcher.knnMatch(descriptors2, descriptors1, matches2, 2);

	//Remove matches for which NN ratio is > threshold
	//Clean image1->image2 matches
	int removed = ratioTest(matches1);

	//Clean image2->image1 matches
	removed = ratioTest(matches2);

	//Remove non-symmetrical matches
	vector<DMatch> symMatches;
	symmetryTest(matches1, matches2, symMatches);

	if (symMatches.size() == 0) {
		symMatches.clear();
		return symMatches;
	}

	//Validate matches using RANSAC
	ransacTest(symMatches, keypoints1, keypoints2, matches);

	if (matches.size() < 5) {
		//matches.clear();
		return matches;
	}

	vector<DMatch> finalMatches;

	filterWithSlopeDistance(image1, image2, keypoints1, keypoints2, matches, finalMatches);
	return finalMatches;
	
}


vector<DMatch> OrbMatching::DoMatching_Fixed(Mat& image1, Mat& image2, int nRequiredKeypointNum, int &nNumKeypoint1, int &nNumKeypoint2)
{
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	vector<DMatch> matches;

	OrbFeatureDetector detector(nRequiredKeypointNum, 1.1, 10); 
	OrbDescriptorExtractor extractor;

	detector.detect(image1, keypoints1);
	nNumKeypoint1 = keypoints1.size();
	if (keypoints1.size() == 0) {
		matches.clear();
		return matches;
	}

	extractor.compute(image1, keypoints1, descriptors1);

	//Extract ORB feature points/feature descriptors for image 2
	detector.detect(image2, keypoints2);
	nNumKeypoint2 = keypoints2.size();
	if (keypoints2.size() == 0) {
		matches.clear();
		return matches;
	}

	extractor.compute(image2, keypoints2, descriptors2);

	//Match the two image descriptors
	BFMatcher matcher(NORM_HAMMING);  //ORB

	//From image1 to image2 based on k nearest neighbour (k=2)
	vector<vector<DMatch>> matches1;

	//matcher.match(descriptors1, descriptors2, matches);
	matcher.knnMatch(descriptors1, descriptors2, matches1, 2);

	//From image2 to image1 based on k nearest neighbour (k=2)
	vector<vector<DMatch>> matches2;
	matcher.knnMatch(descriptors2, descriptors1, matches2, 2);

	//Remove matches for which NN ratio is > threshold
	//Clean image1->image2 matches
	int removed = ratioTest(matches1);

	//Clean image2->image1 matches
	removed = ratioTest(matches2);

	//Remove non-symmetrical matches
	vector<DMatch> symMatches;
	symmetryTest(matches1, matches2, symMatches);

	if (symMatches.size() == 0) {
		symMatches.clear();
		return symMatches;
	}

	//Validate matches using RANSAC
	ransacTest(symMatches, keypoints1, keypoints2, matches);

	if (matches.size() < 5) {
		//matches.clear();
		return matches;
	}

	vector<DMatch> finalMatches;

	filterWithSlopeDistance(image1, image2, keypoints1, keypoints2, matches, finalMatches);
	return finalMatches;
	
}


