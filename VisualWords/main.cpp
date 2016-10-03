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
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
using namespace cv; 


String strFilePre = "E:\\TestVideo\\MeasureTimeOnPhone_SizeInRange\\query_";


void TrainBag_ORB()
{
	//to store the input file names
	char * filename = new char[100];        
	//to store the current input image
	Mat input;  

	double fDist = 0.0;

//	char * filenameDist = new char[100];
//	sprintf(filenameDist,"F:\\tmp\\tt\\DistMatrixORB800.csv");
//	ofstream fsD;
//	fsD.open(filenameDist);

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

#if 0
	for(int i=0; i<dictionary.rows; i++) {
		//cout << i <<endl;
		for (int j=0; j<dictionary.rows; j++) {
			cout << i << ":" << j << endl;
			fDist = 0.0;
			for (int k=0; k<dictionary.cols; k++) {
				fDist = fDist  + pow((dictionary.at<float>(i,k) - dictionary.at<float>(j,k)),2)*1.0;
			}

			fDist = sqrt(fDist);

//			fsD << fDist << ",";
		}
		
//		fsD << "\n";

	}

//	fsD.close();
#endif
}



void TrainBag()
{
	//to store the input file names
	char * filename = new char[100];        
	//to store the current input image
	Mat input;    

	//To store the keypoints that will be extracted by SIFT
	vector<KeyPoint> keypoints;
	//To store the SIFT descriptor of current image
	Mat descriptor;
	//To store all the descriptors that are extracted from all the images.
	Mat featuresUnclustered;
	//The SIFT feature extractor and descriptor
//	SiftDescriptorExtractor detector;    
	SurfDescriptorExtractor detector;

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
	Mat dictionary=bowTrainer.cluster(featuresUnclustered);    
	//store the vocabulary
	FileStorage fs("F:\\tmp\\tt\\dictionarySURF800.yml", FileStorage::WRITE);
	fs << "vocabulary" << dictionary;
	fs.release();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

void TrainDictionary_ORB()
{
	//To store the keypoints that will be extracted by SIFT
	vector<KeyPoint> keypoints;
	//To store the SIFT descriptor of current image
	Mat descriptor;
	//To store all the descriptors that are extracted from all the images.
	Mat featuresUnclustered;

	OrbDescriptorExtractor detector;

	char *strDictionaryFile = new char[200];
	char *strImgListFile = new char[200];
	string strImgFile;
	char *strImgFilePre = new char[200];

	string textline;
	vector<string> fields;
	int nImgCount;
	int nX, nY, nWidth, nHeight;
	Mat inputImage;
	Mat roiFrame;
	int nIndex = 0;
	
	memset(strDictionaryFile, 0x00, 200);
	memset(strImgListFile, 0x00, 200);
	memset(strImgFilePre, 0x00, 200);

	//the number of bags
	int dictionarySize=1600;

	strcpy(strDictionaryFile, "F:\\tmp\\tt\\Dict\\DictORB1600.yml");

	strcpy(strImgFilePre, "E:\\USC_Project\\SkyEye\\Training\\");

	strcpy(strImgListFile, "E:\\USC_Project\\SkyEye\\Training\\info_total_forVisualWordsTrain.dat");

	ifstream infile(strImgListFile, ios::in);

	if (infile.good()) {
		while(getline(infile,textline,'\n')) {
			fields = split(textline, ' ');
			nIndex = nIndex + 1;
			cout <<"Processing Line..... " <<nIndex<<endl;

			if (fields.size() > 1) {
				//sprintf(strImgFile, "%s%s", strImgFilePre, fields.at(0).c_str());
				strImgFile = strImgFilePre +  fields.at(0);
				cout<<strImgFile<<endl;
				//inputImage = imread(strImgFile, CV_LOAD_IMAGE_GRAYSCALE); //Load as grayscale
				inputImage = imread(strImgFile, CV_LOAD_IMAGE_GRAYSCALE); //Load as grayscale

				nImgCount = atoi(fields.at(1).c_str());

				for (int i=0; i<nImgCount; i++) {
					nX = atoi(fields.at(2 + 4*i).c_str());
					nY = atoi(fields.at(2 + 4*i + 1).c_str());
					nWidth = atoi(fields.at(2 + 4*i + 2).c_str());
					nHeight = atoi(fields.at(2 + 4*i + 3).c_str());
					Rect rect(nX, nY, nWidth, nHeight);
					roiFrame = inputImage(rect);

					//detect feature points
					detector.detect(roiFrame, keypoints);
					//compute the descriptors for each keypoint
					detector.compute(roiFrame, keypoints, descriptor);        
					//put the all feature descriptors in a single Mat object 
					featuresUnclustered.push_back(descriptor); 
				}

			}

		}

		infile.close();
	}
	
	cout<<"K-Means Clustering.............."<<endl;

	//Construct BOWKMeansTrainer
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
	FileStorage fs(strDictionaryFile, FileStorage::WRITE);
	fs << "vocabulary" << dictionary;
	fs.release();

}


void TrainDictionary_SIFT_SURF()
{
	//To store the keypoints that will be extracted by SIFT
	vector<KeyPoint> keypoints;
	//To store the SIFT descriptor of current image
	Mat descriptor;
	//To store all the descriptors that are extracted from all the images.
	Mat featuresUnclustered;

	char *strDictionaryFile = new char[200];
	char *strImgListFile = new char[200];
	string strImgFile;
	char *strImgFilePre = new char[200];

	string textline;
	vector<string> fields;
	int nImgCount;
	int nX, nY, nWidth, nHeight;
	Mat inputImage;
	Mat roiFrame;
	int nIndex = 0;
	
	memset(strDictionaryFile, 0x00, 200);
	memset(strImgListFile, 0x00, 200);
	memset(strImgFilePre, 0x00, 200);

	//the number of bags
	int dictionarySize=3200;

	SiftDescriptorExtractor detector;    
//	SurfDescriptorExtractor detector;

	strcpy(strDictionaryFile, "F:\\tmp\\tt\\Dict\\DictSIFT3200.yml");

	strcpy(strImgFilePre, "E:\\USC_Project\\SkyEye\\Training\\");

	strcpy(strImgListFile, "E:\\USC_Project\\SkyEye\\Training\\info_total_forVisualWordsTrain.dat");
	
	ifstream infile(strImgListFile, ios::in);


	if (infile.good()) {
		while(getline(infile,textline,'\n')) {
			fields = split(textline, ' ');
			nIndex = nIndex + 1;
			cout <<"Processing Line..... " <<nIndex<<endl;

			if (fields.size() > 1) {
				//sprintf(strImgFile, "%s%s", strImgFilePre, fields.at(0).c_str());
				strImgFile = strImgFilePre +  fields.at(0);
				//inputImage = imread(strImgFile, CV_LOAD_IMAGE_GRAYSCALE); //Load as grayscale
				inputImage = imread(strImgFile, CV_LOAD_IMAGE_GRAYSCALE); //Load as grayscale

				nImgCount = atoi(fields.at(1).c_str());

				for (int i=0; i<nImgCount; i++) {
					nX = atoi(fields.at(2 + 4*i).c_str());
					nY = atoi(fields.at(2 + 4*i + 1).c_str());
					nWidth = atoi(fields.at(2 + 4*i + 2).c_str());
					nHeight = atoi(fields.at(2 + 4*i + 3).c_str());
					Rect rect(nX, nY, nWidth, nHeight);
					roiFrame = inputImage(rect);

					//detect feature points
					detector.detect(roiFrame, keypoints);
					//compute the descriptors for each keypoint
					detector.compute(roiFrame, keypoints, descriptor);        
					//put the all feature descriptors in a single Mat object 
					featuresUnclustered.push_back(descriptor); 
				}

			}

		}

		infile.close();
	}
	
	cout<<"K-Means Clustering.............."<<endl;

	//Construct BOWKMeansTrainer
	//define Term Criteria
	TermCriteria tc(CV_TERMCRIT_ITER,100,0.001);
	//retries number
	int retries=1;
	//necessary flags
	int flags=KMEANS_PP_CENTERS;
	//Create the BoW (or BoF) trainer
	BOWKMeansTrainer bowTrainer(dictionarySize,tc,retries,flags);
	//cluster the feature vectors
	Mat dictionary=bowTrainer.cluster(featuresUnclustered);    
	//store the vocabulary
	FileStorage fs(strDictionaryFile, FileStorage::WRITE);
	fs << "vocabulary" << dictionary;
	fs.release();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TestImg_ORB()
{
	Mat dictionaryF;
    FileStorage fs("F:\\tmp\\tt\\dictionaryORB800.yml", FileStorage::READ);
    fs["vocabulary"] >> dictionaryF;
    fs.release();    
    
	//convert to 8bit unsigned format
	Mat dictionary(dictionaryF.rows,dictionaryF.cols,CV_8U);
	dictionaryF.convertTo(dictionary,CV_8U); 
	//create a matcher with BruteForce-Hamming distance
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    //create Orb feature point extracter
    Ptr<FeatureDetector> detector(new OrbFeatureDetector());
    Ptr<DescriptorExtractor> extractor(new OrbDescriptorExtractor);    

	//create BoF (or BoW) descriptor extractor
    BOWImgDescriptorExtractor bowDE(extractor,matcher);
    //Set the dictionary with the vocabulary we created in the first step
    bowDE.setVocabulary(dictionary);
 
	Mat bowDescriptor1;
	Mat bowDescriptor2;
	Mat bowDescriptor3;
	Mat bowDescriptor4;
	Mat bowDescriptor5;
	Mat bowDescriptor6;

	for (int i=1; i<=6; i++) {
		//To store the image file name
		char * filename = new char[100];
		//To store the image tag name - only for save the descriptor in a file
		char * imageTag = new char[10];
		char *resultDescript = new char[100];
		char *retIndex = new char[100];

		//open the file to write the resultant descriptor
		sprintf(resultDescript, "F:\\tmp\\tt\\descriptor\\ORB800_descriptor%d.yml", i);
//		FileStorage fs1(resultDescript, FileStorage::WRITE); 
		ofstream fs1;

		fs1.open(resultDescript);
    
		//the image file with the location. change it according to your image file location
		sprintf(filename,"F:\\tmp\\tt\\car%d.jpg", i);        
		//read the image
		Mat img=imread(filename,CV_LOAD_IMAGE_GRAYSCALE);        
		//To store the keypoints that will be extracted by SIFT
		vector<KeyPoint> keypoints;        
		//Detect SIFT keypoints (or feature points)
		detector->detect(img,keypoints);
		//To store the BoW (or BoF) representation of the image
		//Mat bowDescriptor;        
		vector<vector<int>> myvec;
		Mat dess;

		switch (i) {
			case 1:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor1, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor1.rows; a++) {
					for (int b=0; b<bowDescriptor1.cols; b++) {
						fs1 << bowDescriptor1.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 2:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor2, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor2.rows; a++) {
					for (int b=0; b<bowDescriptor2.cols; b++) {
						fs1 << bowDescriptor2.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 3:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor3, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor3.rows; a++) {
					for (int b=0; b<bowDescriptor3.cols; b++) {
						fs1 << bowDescriptor3.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 4:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor4, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor4.rows; a++) {
					for (int b=0; b<bowDescriptor4.cols; b++) {
						fs1 << bowDescriptor4.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 5:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor5, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor5.rows; a++) {
					for (int b=0; b<bowDescriptor5.cols; b++) {
						fs1 << bowDescriptor5.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 6:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor6, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor6.rows; a++) {
					for (int b=0; b<bowDescriptor6.cols; b++) {
						fs1 << bowDescriptor6.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;

		}

		//extract BoW (or BoF) descriptor from given image
		//bowDE.compute(img,keypoints,bowDescriptor, &myvec);
 
		//prepare the yml (some what similar to xml) file
		//sprintf(imageTag,"img%d", i);            
		//write the new BoF descriptor to the file
		//fs1 << imageTag << bowDescriptor;        
 
		//You may use this descriptor for classifying the image.
        fs1.close();
    
		//release the file storage
		sprintf(retIndex, "F:\\tmp\\tt\\index\\ORB800_index%d.txt", i);

		FileStorage fs2(retIndex, FileStorage::WRITE); 
		fs2 << "Index" << myvec;

		cout<< "Size:" << myvec.size() <<endl;
//		myvec.size();
//		vector<int> tmp;

//		for(int t=1; t<myvec.size(); t++) {
//			tmp = myvec.at(t);
//			for (int s = 1; s<tmp.size(); s++) {
//				fs2 << tmp.at(s) <<",";
//			}
//		}

		fs2.release();

	}

//	int cmpmethod = CV_COMP_CORREL;
//	int cmpmethod =  CV_COMP_CHISQR;
//	int cmpmethod = CV_COMP_INTERSECT;
	int cmpmethod = CV_COMP_BHATTACHARYYA;

	double ret21 = compareHist(bowDescriptor2, bowDescriptor1, cmpmethod);
	double ret22 = compareHist(bowDescriptor2, bowDescriptor2, cmpmethod);
	double ret23 = compareHist(bowDescriptor2, bowDescriptor3, cmpmethod);
	double ret24 = compareHist(bowDescriptor2, bowDescriptor4, cmpmethod);
	double ret25 = compareHist(bowDescriptor2, bowDescriptor5, cmpmethod);
	double ret26 = compareHist(bowDescriptor2, bowDescriptor6, cmpmethod);

	cout<<"2-1 (diff car):			" << ret21 << endl;
	cout<<"2-2 (same image:			" << ret22 << endl;
	cout<<"2-3 (same car same angle, same light):	" << ret23 << endl;
	cout<<"2-4 (same car, different angle):			" << ret24 << endl;
	cout<<"2-5 (same car, same angle, different light):	" << ret25 << endl;
	cout<<"2-6 (different car):		" << ret26 << endl;

	getchar();
}



void TestImg()
{
	Mat dictionary; 
    FileStorage fs("F:\\tmp\\tt\\dictionarySURF800.yml", FileStorage::READ);
    fs["vocabulary"] >> dictionary;
    fs.release();    
    
    //create a nearest neighbor matcher
    Ptr<DescriptorMatcher> matcher(new FlannBasedMatcher);
    //create Sift feature point extracter
//    Ptr<FeatureDetector> detector(new SiftFeatureDetector());
//    Ptr<DescriptorExtractor> extractor(new SiftDescriptorExtractor);   
    Ptr<FeatureDetector> detector(new SurfFeatureDetector());
    Ptr<DescriptorExtractor> extractor(new SurfDescriptorExtractor);    

	//create BoF (or BoW) descriptor extractor
    BOWImgDescriptorExtractor bowDE(extractor,matcher);
    //Set the dictionary with the vocabulary we created in the first step
    bowDE.setVocabulary(dictionary);
 
	Mat bowDescriptor1;
	Mat bowDescriptor2;
	Mat bowDescriptor3;
	Mat bowDescriptor4;
	Mat bowDescriptor5;
	Mat bowDescriptor6;

 
	for (int i=1; i<=6; i++) {
		//To store the image file name
		char * filename = new char[100];
		//To store the image tag name - only for save the descriptor in a file
		char * imageTag = new char[10];
		char *resultDescript = new char[100];
		char *resultDescriptss = new char[100];

		char *retIndex = new char[100];

		//open the file to write the resultant descriptor
		sprintf(resultDescript, "F:\\tmp\\tt\\descriptor\\SURF800_descriptor%dSP.yml", i);
	//	FileStorage fs1(resultDescript, FileStorage::WRITE);    
		ofstream fs1;

		fs1.open(resultDescript);

		//sprintf(resultDescriptss, "F:\\tmp\\tt\\descriptor\\SIFT800_descriptor%d_ss.yml", i);
		//FileStorage fs11(resultDescriptss, FileStorage::WRITE);    

		//the image file with the location. change it according to your image file location
		sprintf(filename,"F:\\tmp\\tt\\car%d.jpg", i);        
		//read the image
		Mat img=imread(filename,CV_LOAD_IMAGE_GRAYSCALE);        
		//To store the keypoints that will be extracted by SIFT
		vector<KeyPoint> keypoints;        
		//Detect SIFT keypoints (or feature points)
		detector->detect(img,keypoints);
		//To store the BoW (or BoF) representation of the image

		vector<vector<int>> myvec;
		Mat dess;

		switch (i) {
			case 1:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor1, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor1.rows; a++) {
					for (int b=0; b<bowDescriptor1.cols; b++) {
						fs1 << bowDescriptor1.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 2:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor2, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor2.rows; a++) {
					for (int b=0; b<bowDescriptor2.cols; b++) {
						fs1 << bowDescriptor2.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 3:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor3, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor3.rows; a++) {
					for (int b=0; b<bowDescriptor3.cols; b++) {
						fs1 << bowDescriptor3.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 4:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor4, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor4.rows; a++) {
					for (int b=0; b<bowDescriptor4.cols; b++) {
						fs1 << bowDescriptor4.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 5:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor5, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor5.rows; a++) {
					for (int b=0; b<bowDescriptor5.cols; b++) {
						fs1 << bowDescriptor5.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;
			case 6:
				//extract BoW (or BoF) descriptor from given image
				bowDE.compute(img,keypoints,bowDescriptor6, &myvec, &dess);
 
				//prepare the yml (some what similar to xml) file
				sprintf(imageTag,"img%d", i);            
				//write the new BoF descriptor to the file
				for (int a=0; a<bowDescriptor6.rows; a++) {
					for (int b=0; b<bowDescriptor6.cols; b++) {
						fs1 << bowDescriptor6.at<float>(a,b) << ",";
					}
					fs1 << "\n";
				}
				break;

		}
	//	fs1 << imageTag << bowDescriptor;        
		//fs11 << imageTag << dess;        
 
		//You may use this descriptor for classifying the image.
            
		//release the file storage
		fs1.close();
		//fs11.release();

		//release the file storage
		sprintf(retIndex, "F:\\tmp\\tt\\index\\SURF800_index%dSP.txt", i);

//		FileStorage fs2(retIndex, FileStorage::WRITE);
		
		ofstream fs2;

		fs2.open(retIndex);

		vector<vector<int>>::iterator u;
		vector<int>::iterator v;
		int count= 0;
		for(u = myvec.begin(); u != myvec.end(); u++)
		{
			count = count + 1;
			cout<<"Count::" <<count <<endl;
			for(v = (*u).begin(); v != (*u).end(); v++)
			{
				fs2 << *v << ",";
			}
			fs2 << "\n";
		}

		fs2.close();

	}

//	int cmpmethod = CV_COMP_CORREL;
//	int cmpmethod =  CV_COMP_CHISQR;
//	int cmpmethod = CV_COMP_INTERSECT;
	int cmpmethod = CV_COMP_BHATTACHARYYA;

	double ret21 = compareHist(bowDescriptor2, bowDescriptor1, cmpmethod);
	double ret22 = compareHist(bowDescriptor2, bowDescriptor2, cmpmethod);
	double ret23 = compareHist(bowDescriptor2, bowDescriptor3, cmpmethod);
	double ret24 = compareHist(bowDescriptor2, bowDescriptor4, cmpmethod);
	double ret25 = compareHist(bowDescriptor2, bowDescriptor5, cmpmethod);
	double ret26 = compareHist(bowDescriptor2, bowDescriptor6, cmpmethod);

	cout<<"2-1 (diff car):			" << ret21 << endl;
	cout<<"2-2 (same image:			" << ret22 << endl;
	cout<<"2-3 (same car same angle, same light):	" << ret23 << endl;
	cout<<"2-4 (same car, different angle):			" << ret24 << endl;
	cout<<"2-5 (same car, same angle, different light):	" << ret25 << endl;
	cout<<"2-6 (different car):		" << ret26 << endl;

	getchar();

}

int main()
{
//	TrainDictionary_ORB();
	TrainDictionary_SIFT_SURF();

//	TrainBag();
//	TrainBag_ORB();

//	TestImg();
//	TestImg_ORB();

	return 0;
}