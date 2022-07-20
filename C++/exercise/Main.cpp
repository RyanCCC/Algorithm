#include "Common.h"
#include "method.h"
#include "example.h"

using namespace std;
using namespace cv;


extern void videoshow(string video);

int main()
{
    string img_path = "../../src/test.png";
    Mat img = imread(img_path);
    //图像不存在的情况
    if (img.empty()) {
        cout << "could not load image"<<endl;
    }
    //一些其他的操作可以参考：https://mp.weixin.qq.com/s/k2rnkfhTXI-fC8Vu7MfnBg
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

void videoshow(string video)
{

}
