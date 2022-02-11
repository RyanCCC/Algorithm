#include "Common.h"
#include "header/method.h"
#include"header/example.h"
#include "HazeRemoval.h"
#include "GuideFilter.h"
#include "DarkChannel.h"
#include "sift.h"

using namespace std;
using namespace cv;


extern void videoshow(string video);

int main()
{
    //sift算法
    string img1 = "./src/lena.jpg";;
    string img2 = "./src/lena_test.jpg";
    sift_main(img1, img2);
    //去雾算法
    for (int i = 1; i <= 8; i++)
    {
        Mat src = imread("./src/" + to_string(i) + ".bmp");
        Mat res;

        HazeRemoval(src, res);

        imshow("Input", src);
        imshow("Dehaze", res);

        waitKey(0);
    }
    string img_path = "./src/test.png";
    Mat img = imread(img_path);
    example2_5(img);
    cout << max_customer(1, 2) << endl;
    cout << min_customer(1, 2) << endl;
    string video = "./src/01.mp4";
    videoshow(video);
    namedWindow("Test");
    imshow("Test", img);
    waitKey(0);
    return 0;
}