#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>	
#include <iostream>
#include <string>
#include <sstream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;
int main(int argc, char** argv){
	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout<<"cap failed"<< endl;
		return -1;
	}
	Mat im;
	string image="image";
	int k=5;
	cap >> im;
	namedWindow(image, CV_WINDOW_AUTOSIZE);
	namedWindow(" v", CV_WINDOW_AUTOSIZE);

	Mat gray, orig;
	Mat3b mask(im.size(), Vec3b(0,0,0));	
	Mat3b res(im.size(), Vec3b(0,0,0));
	double alpha=0.5, beta=(1.0-alpha);
	while(1){
		//waitKey(0.5);

		cap >> im;
		orig=im.clone();
		GaussianBlur(im, im, Size(k,k),	 0, 0);
		

		cvtColor(im, gray, COLOR_BGR2GRAY);
		GaussianBlur(gray,gray, Size(k,k), 0,0);

		double minVal; double maxVal; Point minLoc; Point maxLoc;
		minMaxLoc(gray, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		circle( mask, maxLoc, k, Scalar(im.at<Vec3b>(maxLoc)[0], im.at<Vec3b>(maxLoc)[1], im.at<Vec3b>(maxLoc)[2]), -1, 8, 0 );
		cout << (int)im.at<Vec3b>(maxLoc)[0] << " " << (int)im.at<Vec3b>(maxLoc)[1] << " " << (int)im.at<Vec3b>(maxLoc)[2]<<endl;
		orig.copyTo( res, mask );	
		imshow(" v", mask);		
		
		addWeighted( orig, alpha, mask, beta, 0.0, res);
		res=res*2;
		flip(res, res, 1);
		imshow(image, res);
		

	}
}
	