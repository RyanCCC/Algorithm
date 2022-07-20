#include "Common.h"
#include <iostream>
#include "HOG.h"

using namespace std;
using namespace cv;

int main()
{
   
    string img1 = "../../src/lena.jpg";
    //HOG算法
    Mat image = imread(img1);
    HOG_main(image);
   
    return 0;
}