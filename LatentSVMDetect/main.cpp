#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <opencv2\legacy\legacy.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>


using namespace std;
using namespace cv; 


#if 0
#ifdef WIN32
#include <io.h>
#else
#include <dirent.h>
#endif

#ifdef HAVE_CVCONFIG_H
#include <cvconfig.h>
#endif

#ifdef HAVE_TBB
#include "tbb/task_scheduler_init.h"
#endif

using namespace std;
using namespace cv;
#endif

static void help()
{
    cout << "This program demonstrated the use of the latentSVM detector." << endl <<
            "It reads in a trained object models and then uses them to detect the objects in an images." << endl <<
             endl <<
            "Call:" << endl <<
            "./latentsvm_multidetect <imagesFolder> <modelsFolder> [<overlapThreshold>][<threadsNumber>]" << endl <<
            "<overlapThreshold> - threshold for the non-maximum suppression algorithm." << endl <<
            "Example of <modelsFolder> is opencv_extra/testdata/cv/latentsvmdetector/models_VOC2007" << endl <<
             endl <<
            "Keys:" << endl <<
            "'n' - to go to the next image;" << endl <<
            "'esc' - to quit." << endl <<
            endl;
}

static void detectAndDrawObjects( Mat& image, LatentSvmDetector& detector, const vector<Scalar>& colors, float overlapThreshold, int numThreads )
{
    vector<LatentSvmDetector::ObjectDetection> detections;

    TickMeter tm;
    tm.start();
    detector.detect( image, detections, overlapThreshold, numThreads);
    tm.stop();

    cout << "Detection time = " << tm.getTimeSec() << " sec" << endl;

    const vector<string> classNames = detector.getClassNames();
    CV_Assert( colors.size() == classNames.size() );

    for( size_t i = 0; i < detections.size(); i++ )
    {
        const LatentSvmDetector::ObjectDetection& od = detections[i];
        rectangle( image, od.rect, colors[od.classID], 3 );
    }
    // put text over the all rectangles
    for( size_t i = 0; i < detections.size(); i++ )
    {
        const LatentSvmDetector::ObjectDetection& od = detections[i];
        putText( image, classNames[od.classID], Point(od.rect.x+4,od.rect.y+13), FONT_HERSHEY_SIMPLEX, 0.55, colors[od.classID], 2 );
    }
}

#if 0
static void readDirectory( const string& directoryName, vector<string>& filenames, bool addDirectoryName=true )
{
    filenames.clear();

#ifdef WIN32
    struct _finddata_t s_file;
    string str = directoryName + "\\*.*";

    intptr_t h_file = _findfirst( str.c_str(), &s_file );
    if( h_file != static_cast<intptr_t>(-1.0) )
    {
        do
        {
            if( addDirectoryName )
                filenames.push_back(directoryName + "\\" + s_file.name);
            else
                filenames.push_back((string)s_file.name);
        }
        while( _findnext( h_file, &s_file ) == 0 );
    }
    _findclose( h_file );
#else
    DIR* dir = opendir( directoryName.c_str() );
    if( dir != NULL )
    {
        struct dirent* dent;
        while( (dent = readdir(dir)) != NULL )
        {
            if( addDirectoryName )
                filenames.push_back( directoryName + "/" + string(dent->d_name) );
            else
                filenames.push_back( string(dent->d_name) );
        }
    }
#endif

    sort( filenames.begin(), filenames.end() );
}
#endif

//int main(int argc, char* argv[])
int main()
{
    //help();

    string images_folder, models_folder;
    float overlapThreshold = 0.2f;
    int numThreads =1;
#if 0
    if( argc > 2 )
    {
        images_folder = argv[1];
        models_folder = argv[2];
        if( argc > 3 ) overlapThreshold = (float)atof(argv[3]);
        if( overlapThreshold < 0 || overlapThreshold > 1)
        {
            cout << "overlapThreshold must be in interval (0,1)." << endl;
            exit(-1);
        }

        if( argc > 4 ) numThreads = atoi(argv[4]);
    }
#endif

	images_folder = "E:\\TestVideo\\Set1";


    vector<string> images_filenames, models_filenames;
//    readDirectory( images_folder, images_filenames );
//    readDirectory( models_folder, models_filenames );

	//models_filenames.push_back("E:\\Self_Practice\\ObjectDetection\\LatentSVMDetect\\haarcascade_vehicle.xml");
//	models_filenames.push_back("C:\\OpenCV2.4.5\\opencv\\samples\\cpp\\matching_to_many_images\\train\\trainImages.txt");
	models_filenames.push_back("C:\\OpenCV2.4.5\\opencv\\samples\\cpp\\matching_to_many_images\\train\\1.png");
	models_filenames.push_back("C:\\OpenCV2.4.5\\opencv\\samples\\cpp\\matching_to_many_images\\train\\2.png");
	models_filenames.push_back("C:\\OpenCV2.4.5\\opencv\\samples\\cpp\\matching_to_many_images\\train\\3.png");

	//String baseImageFile = "E:\\TestVideo\\Set1\\SelfTook.jpg";
//String baseImageFile = "E:\\TestVideo\\Set2\\self_fromOthers1.jpg";	//self_fromOthers1~2
	images_filenames.push_back("C:\\OpenCV2.4.5\\opencv\\samples\\cpp\\matching_to_many_images\\query");
	//images_filenames.push_back("E:\\TestVideo\\Set1\\SelfTook.jpg");
	//images_filenames.push_back("E:\\TestVideo\\Set2\\self_fromOthers1.jpg");
		cout<<"Here0......"<<endl;
			getchar();
    LatentSvmDetector detector( models_filenames );
    if( detector.empty() )
    {
        cout << "Models cann't be loaded" << endl;
		getchar();
        exit(-1);
    }
	cout<<"Here1......"<<endl;
	getchar();
    const vector<string>& classNames = detector.getClassNames();
    cout << "Loaded " << classNames.size() << " models:" << endl;
    for( size_t i = 0; i < classNames.size(); i++ )
    {
        cout << i << ") " << classNames[i] << "; ";
    }
    cout << endl;

    cout << "overlapThreshold = " << overlapThreshold << endl;
	getchar();

    vector<Scalar> colors;
    generateColors( colors, detector.getClassNames().size() );

    for( size_t i = 0; i < images_filenames.size(); i++ )
    {
        Mat image = imread(images_filenames[i]);
        if( image.empty() )  continue;

        cout << "Process image " << images_filenames[i] << endl;
        detectAndDrawObjects( image, detector, colors, overlapThreshold, numThreads );

        imshow( "result", image );

        for(;;)
        {
            int c = waitKey();
            if( (char)c == 'n')
                break;
            else if( (char)c == '\x1b' )
                exit(0);
        }
    }

    return 0;
}
