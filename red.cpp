#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>    

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat image,image2;
    image = imread("./frame0001.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    //Mat image = image;
    int width = image.size().width;
    int height = image.size().height;
    cv::namedWindow("Original",1);
    cv::imshow("Original", image); 
    GaussianBlur( image, image, Size( 15, 15 ), 10, 10 );

    //cv::namedWindow("Blurred",1);
    //cv::imshow("Blurred", image); 
    /*for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int blue = image.at<cv::Vec3b>(i,j)[0]; 

            if(blue>75){
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
    }*/
    queue < pair<int, int> > ColorBox;
    int cnt=0;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int blue = image.at<cv::Vec3b>(i,j)[0]; 

            if(blue<85){
            	image.at<cv::Vec3b>(i,j)[0] = 0;
            	image.at<cv::Vec3b>(i,j)[1] = 0;
            	image.at<cv::Vec3b>(i,j)[2] = 0;
          }
            else if(blue>135){
           		//pair<int,int> temp = make_pair(i,j);
          		ColorBox.push(make_pair(i,j));
            	image.at<cv::Vec3b>(i,j)[0] = 255;
            	image.at<cv::Vec3b>(i,j)[1] = 255;
            	image.at<cv::Vec3b>(i,j)[2] = 255;
          }
          else{
          		image.at<cv::Vec3b>(i,j)[0] = 1;
            	image.at<cv::Vec3b>(i,j)[1] = 1;
            	image.at<cv::Vec3b>(i,j)[2] = 1;
          }
        }
    }
    while(!ColorBox.empty()){
          		cnt++;
    	pair<int,int> var = ColorBox.front();
    	ColorBox.pop();
    	int arr1[] = {-1,0,1};
    	int arr2[] = {-1,0,1};
    	for(int i=0;i<3;i++){
    		for(int j=0;j<3;j++){
    			if(arr1[i]==0 && arr2[j]==0) continue;
    			if(!(var.first + arr1[i] < 0|| var.first + arr1[i] >= height || var.second + arr2[j]<0 || var.second + arr2[j]>=width)){
    				if(image.at<cv::Vec3b>(var.first + arr1[i], var.second + arr2[j])[0] == 1){
    				image.at<cv::Vec3b>(var.first + arr1[i], var.second + arr2[j])[0] = 255;
          			ColorBox.push(make_pair(var.first + arr1[i], var.second + arr2[j]));
    			}
    			else
    				image.at<cv::Vec3b>(var.first + arr1[i], var.second + arr2[j])[0] = 0;
    			}
    			//pair<int,int> temp1 = make_pair(var.first + arr1[i], var.second + arr2[j]);
    		}
    	}
    }
    cout<<cnt<<endl;
    cv::cvtColor(image, image, CV_RGB2GRAY);
	cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(40, 40));
	cv::morphologyEx( image, image, cv::MORPH_CLOSE, structuringElement );
    cv::namedWindow("Normal",1);
    cv::imshow("Normal", image);    
    waitKey(0);//Wait for a keystroke in the window
    return 0;
}