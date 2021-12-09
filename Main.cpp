#include <iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    string img_path = "./src/test.png";
    Mat img = imread(img_path);
    namedWindow("Test");
    imshow("Test", img);
    waitKey(0);
    return 0;
}