#include "Common.h"
#include "HazeRemoval.h"
#include "DarkChannel.h"

using namespace std;
using namespace cv;



int main()
{

    //去雾算法
    for (int i = 1; i <= 8; i++)
    {
        Mat src = imread("../../src/" + to_string(i) + ".bmp");
        Mat res;

        HazeRemoval(src, res);

        imshow("Input", src);
        imshow("Dehaze", res);

        waitKey(0);
    }
    string img_path = "./src/test.png";
    Mat img = imread(img_path);
    //图像不存在的情况
    if (img.empty()) {
        cout << "could not load image" << endl;
    }
    return 0;
}