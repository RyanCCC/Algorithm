#include "Common.h"
#include "inpaint.h"

using namespace std;
using namespace cv;



int main()
{
    //Image inpaint https://github.com/vacancy/PyPatchMatch
    auto source = cv::imread("../../src/202112311304288.jpg", cv::IMREAD_COLOR);
    auto mask_ori = cv::imread("../../src/202112311304288_mask.jpg");

    auto mask = cv::Mat(mask_ori.size(), CV_8UC1);
    mask = cv::Scalar::all(0);
    for (int i = 0; i < mask_ori.size().height; ++i) {
        for (int j = 0; j < mask_ori.size().width; ++j) {
            auto source_ptr = mask_ori.ptr<unsigned char>(i, j);
            if (source_ptr[0] != 0 && source_ptr[1] != 0 && source_ptr[2] != 0) {
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
    return 0;
}