#include<iostream>
#include <string>
#include "Common.h"
#include "sift.h"

using namespace std;
using namespace cv;


int main()
{
    string img1 = "../../src/lena.jpg";
    string img2 = "../../src/lena_test.jpg";
 
    //sift算法
    sift_main(img1, img2);
    return 0;
}