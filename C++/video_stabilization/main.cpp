#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
#include<cmath>
#include<time.h>
#include "videostab.h"


/*
* 视频优化参考：
* 1. https://github.com/Lakshya-Kejriwal/Real-Time-Video-Stabilization
* 2. https://zhuanlan.zhihu.com/p/250839967
*/

using namespace std;
using namespace cv;

// This class redirects cv::Exception to our process so that we can catch it and handle it accordingly.
class cvErrorRedirector {
public:
	int cvCustomErrorCallback()
	{
		std::cout << "A cv::Exception has been caught. Skipping this frame..." << std::endl;
		return 0;
	}

	cvErrorRedirector() {
		cvRedirectError((cv::ErrorCallback)cvCustomErrorCallback(), this);
	}
};

const int HORIZONTAL_BORDER_CROP = 30;

int main()
{
	//read input video
	string video = "../../src/Test4.mp4";
	ifstream fin(video);
	if (!fin) {
		cout << "File not exists."<<endl;
		return 0;
	}
	cvErrorRedirector redir;
	//Create a object of stabilization class
	VideoStab stab;

	//Initialize the VideoCapture object
	VideoCapture cap(video);
    Mat frame_2, frame2;
    Mat frame_1, frame1;

    cap >> frame_1;
    cvtColor(frame_1, frame1, COLOR_BGR2GRAY);

    Mat smoothedMat(2, 3, CV_64F);

    VideoWriter outputVideo;
    outputVideo.open("com.avi", CV_FOURCC('X', 'V', 'I', 'D'), 30, frame_1.size());

    while (true)
    {
        try {
            cap >> frame_2;

            if (frame_2.data == NULL)
            {
                break;
            }

            cvtColor(frame_2, frame2, COLOR_BGR2GRAY);

            Mat smoothedFrame;

            smoothedFrame = stab.stabilize(frame_1, frame_2);

            outputVideo.write(smoothedFrame);

            imshow("Stabilized Video", smoothedFrame);

            waitKey(10);

            frame_1 = frame_2.clone();
            frame2.copyTo(frame1);
        }
        catch (cv::Exception& e) {
            cap >> frame_1;
            cvtColor(frame_1, frame1, COLOR_BGR2GRAY);
        }

    }

    return 0;
}
