#include <iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "header/method.h"

using namespace std;
using namespace cv;


extern void videoshow(string video);

int main()
{
    cout << max(1, 2) << endl;
    string video = "./src/01.mp4";
    videoshow(video);
    string img_path = "./src/test.png";
    Mat img = imread(img_path);
    namedWindow("Test");
    imshow("Test", img);
    waitKey(0);
    return 0;
}