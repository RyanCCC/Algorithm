#pragma once

#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<algorithm>

using namespace cv;
using namespace std;

//keypoint class
class keypoint {
public:
	keypoint(int oct = 0, int lyr = 0, Point p = Point(0, 0), double scl = 0, float ang = 0) :
		octave(oct), layer(lyr), scale(scl), pt(p), angle(ang) {}
	static void coinvertToKeyPoint(vector<keypoint>& kpts, vector<KeyPoint>& KPts);

public:
	int octave;
	int layer;//注意从0开始
	Point pt;
	double scale;//尺度空间坐标
	float angle;
	float response;
	int oct_info;
};

//pyramid class
class pyramid {
public:
	void appendTo(int oct, Mat& img);
	void build(int oct) { pyr.resize(oct); }
	void clear() { pyr.clear(); }
	int octaves() { return pyr.size(); }//层数
	vector<Mat>& operator[] (int oct);//重载

private:
	vector<vector<Mat>> pyr;
};

//sift class
class sift {
public:
	sift(int s = 3, double sigma = 1.6) : S(s), Sigma(sigma), debug(0) { Layers = s + 2; K = pow(2., 1. / s); }
	
	// sift检测开始入口
	//0. 参数计算+图像预处理
	bool detect(const Mat& img, vector<keypoint>& kpts, Mat& fvec);
	void info();

private:
	//1. 建立金字塔 pyr_G pyr_DOG
	void buildPyramid();

	//2. 检测特征点
	void findFeaturePoints(vector<keypoint>& kpts);

	//2.1 寻找DoG图像极值点
	//2.2 极值点筛选
	bool filterExtrema(keypoint& kpt);
	//2.3 计算特征点主方向
	void calcMainOrientation(keypoint& kpt, vector<float>& angs);

	//3. 提取特征点处的128维特征
	void calcFeatureVector(vector<keypoint>& kpts, Mat& fvec);

public:
	int debug;

private:
	int Octaves;
	int Layers;//Layers 作为高斯模糊金字塔一个octave内图像数-1
	double Sigma;
	int S;
	double K;

	//图像
	Mat img_org;
	Mat img;

	//金字塔
	pyramid pyr_G;//高斯混合模型
	pyramid pyr_DoG;//DoG金字塔

};

void sift_main(string img1, string img2);