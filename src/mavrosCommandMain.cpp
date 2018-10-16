#include <iostream>
#include "ros/ros.h"
#include <fstream>
#include <math.h>
#include "mavrosCommand.hpp"
#include <nlohmann/json.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace GeographicLib;
int frequency = 20;
int loopCounter = 0;;


int main(int argc, char* argv[]){

	ros::init(argc, argv, "testpackage");
	mavrosCommand command;
	
	ros::Rate loop_rate(frequency);
	sleep(1);

	VideoCapture cap(0);
	
	if (cap.isOpened() == false)  
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	} 

	//cap.set(CV_CAP_PROP_FRAME_WIDTH , 1920);
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT , 1080);
	Mat frame;
	Mat bwFrame;
	Mat bwFrame2;
	while (ros::ok()) {

		bool bSuccess = cap.read(frame);
		if (bSuccess == false) 
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
			break;
		}
		cvtColor(frame, bwFrame, cv::COLOR_RGB2GRAY);
		  threshold( bwFrame, bwFrame2, 220, 255,0 );
		imshow("dupa", bwFrame2);
		waitKey(10);

		ros::spinOnce();
		loop_rate.sleep();
	}	
	cap.release();
	return 0;
}
