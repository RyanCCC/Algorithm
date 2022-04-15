#include "header/example.h"

using namespace cv;

void example2_5(Mat& image)
{
	// Create some windows to show the input
	// and output images in
	namedWindow("Example2_5-in", WINDOW_AUTOSIZE);
	namedWindow("Example2_5-out", WINDOW_AUTOSIZE);
	imshow("Example2_5-in", image);
	Mat out;
	GaussianBlur(image, out, Size(5, 5), 3, 3);
	GaussianBlur(out, out, Size(5, 5), 3, 3);
	imshow("Example2_5-out", out);
	waitKey(0);
}
