#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>    

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat image,fin_img;
    image = imread("./frame0001.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file

    namedWindow("Red",1);
    
    Mat channel[3];
    split(image, channel);

    GaussianBlur( channel[0], channel[0], Size( 13, 13 ), 100, 100 );

    adaptiveThreshold(channel[0], image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 15, -2);

    imshow("Red", image);
    imwrite("dest.jpg",image);

    waitKey(0);//Wait for a keystroke in the window
    return 0;
}