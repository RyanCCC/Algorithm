#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void videoshow(string video) {
	namedWindow("Example3", WINDOW_AUTOSIZE);
	VideoCapture cap;
	cap.open(video);

	Mat frame;
	for (;;) {
		cap >> frame;
		if (frame.empty()) break;
		imshow("Example3", frame);
		if (waitKey(33) >= 0) break;
	}

}