#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>    

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat image,M2;
    image = imread("./frame0001.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    Mat M ;

    //cv::namedWindow("Original",1);
    //cv::imshow("Original", image); 
    GaussianBlur( image, image, Size( 15, 15 ), 10, 10 );

    //cv::namedWindow("Blurred",1);
    //cv::imshow("Blurred", image); 
    for(int i=0;i<720;i++){
        for(int j=0;j<1280;j++){
            int blue = image.at<cv::Vec3b>(i,j)[0]; 

            if(blue>155){
            image.at<cv::Vec3b>(i,j)[0] = 255;
            image.at<cv::Vec3b>(i,j)[1] = 255;
            image.at<cv::Vec3b>(i,j)[2] = 255;
        	}
            else {
            image.at<cv::Vec3b>(i,j)[0] = 0;
            image.at<cv::Vec3b>(i,j)[1] = 0;
            image.at<cv::Vec3b>(i,j)[2] = 0;
        	}
        }
    }
    cv::cvtColor(image, image, CV_RGB2GRAY);
	/*vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours( image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	double min_area=10000; // area threshold
 	double max_area=20000; // area threshold
 	for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
 	{
 	  double area=contourArea( contours[i],false);  //  Find the area of contour
 	  if(area<min_area)
 	  	contours.erase(contours.begin() + i);
 	  
		drawContours( image, contours, i, Scalar(0,0,255), 2, 8, hierarchy, 0, Point() ); 	
	}*/
	cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(40, 40));
cv::morphologyEx( image, image, cv::MORPH_CLOSE, structuringElement );
    cv::namedWindow("Normal",1);
    cv::imshow("Normal", image);    
    waitKey(0);//Wait for a keystroke in the window
    return 0;
}