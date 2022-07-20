#pragma once
#ifndef  VIDEOSTAB_H
#define VIDEOSTAB_H

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

class VideoStab {
public:
	VideoStab();
	VideoCapture capture;

	Mat frame2;
	Mat frame1;

	int k;
	const int HORIZONTAL_BORDER_CROP = 30;
	Mat smoothedMat;
	Mat affine;

	Mat smoothedFrame;
	
	double dx;
	double dy;
	double da;
	double ds_x;
	double ds_y;

	double sx;
	double sy;

	double scaleX;
	double scaleY;
	double theta;
	double transX;
	double transY;

	double diff_scaleX;
	double diff_scaleY;
	double diff_transX;
	double diff_transY;
	double diff_theta;

	double errscaleX;
	double errscaleY;
	double errtheta;
	double errtransX;
	double errtransY;

	double Q_scaleX;
	double Q_scaleY;
	double Q_theta;
	double Q_transX;
	double Q_transY;

	double R_scaleX;
	double R_scaleY;
	double R_theta;
	double R_transX;
	double R_transY;


	double sum_scaleX;
	double sum_scaleY;
	double sum_theta;
	double sum_transX;
	double sum_transY;

	Mat stabilize(Mat frame_1, Mat frame_2);
	void Kalman_Filter(double* scaleX, double* scaleY, double* thetha, double* transX, double* transY);
	



};



#endif // ! VIDEOSTAB_H
