#include "header/Common.h"
#include "header/method.h"
#include"header/example.h"
#include "header/HazeRemoval.h"
#include "header/GuideFilter.h"
#include "header/DarkChannel.h"
#include "header/sift.h"
#include "header/HOG.h"
#include "header/pfs.h"
#include "header/D8.h"

#include "masked_image.h"
#include "nnf.h"
#include "inpaint.h"

using namespace std;
using namespace cv;


extern void videoshow(string video);



int main()
{
    //Image inpaint https://github.com/vacancy/PyPatchMatch
    auto source = cv::imread("./src/202112311304288.jpg", cv::IMREAD_COLOR);
    auto mask_ori = cv::imread("./src/202112311304288_mask.jpg");

    auto mask = cv::Mat(mask_ori.size(), CV_8UC1);
    mask = cv::Scalar::all(0);
    for (int i = 0; i < mask_ori.size().height; ++i) {
        for (int j = 0; j < mask_ori.size().width; ++j) {
            auto source_ptr = mask_ori.ptr<unsigned char>(i, j);
            if (source_ptr[0] !=0 && source_ptr[1] != 0 && source_ptr[2] != 0) {
                mask.at<unsigned char>(i, j) = 1;
            }
        }
    }


    cv::imshow("mask", mask);
    cv::waitKey();

    //nnf算法
    auto metric = PatchSSDDistanceMetric(3);
    //计算结果
    auto result = Inpainting(source, mask, &metric).run(true, false);
    //展示图像
    cv::imwrite("./images/forest_recovered.bmp", result);
    cv::imshow("Result", result);
    cv::waitKey();


    D8_main();
    pfs();
    string img1 = "./src/lena.jpg";
    string img2 = "./src/lena_test.jpg";
    //HOG算法
    Mat image = imread(img1);
    HOG_main(image);

    //sift算法
    
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