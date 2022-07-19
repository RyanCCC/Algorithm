# 计算机视觉

本项目基于C++实现计算机视觉中的算法。包括传统的计算机视觉算法以及基于深度学习的算法。另外在Python文件夹下有相关的opencv python代码，并且设置对应的readme介绍相对应的算法。


## 文档说明

1. `C++`文件夹存放的是算法实现的C++代码，已实现的算法或者待实现的算法在下面`算法/C++`已经列出。
2. `pyhton`同`C++`文件夹，存放的是算法实现的python代码，已实现的算法或者待实现的算法在下面`算法/Python`已经列出。
3. `doc`文件夹存放的是算法的说明文档。
4. `src`文件夹存放一些图像视频等。


## 算法

### C++

- [x] [去雾算法](./doc/%E5%8E%BB%E9%9B%BE%E7%AE%97%E6%B3%95.md)
- [x] [SIFT算法](./doc/SIFT%E7%AE%97%E6%B3%95.md)
- [ ] [HOG算法](./doc/HOG%E7%AE%97%E6%B3%95.md)


### Python部分

关于Python部分算法在此不再做详细的介绍，在每个文件夹里面都有相应ReadMe文件做介绍以及相关的代码。在此只记录实现的算法。

- [x]  [ImageSimilarity：图像匹配算法，包括相似性度量的感知哈希算法、模板匹配算法、银行卡号识别实战。](./python/ImageSimilarity/ReadMe.md)
- [x]  [ImageSegment：图像分割算法](./python/ImageSegment/ReadMe.md)
- [x]  [ImageMask：Mask掩膜操作](./python/ImageMask/Main.ipynb)
- [x]  [ImageBlur：滤波](./python/ImageBlur/)
- [x]  [ImageGray：图像灰度化操作](./python/ImageGray/main.ipynb)
- [x]  [ImageMorphology：图像形态学变化](./python/ImageMorphology/ReadMe.md)
- [x]  [ImageEdgeDetection：图像边缘检测](./python/ImageEdgeDetection/main.ipynb)
- [x]  [ImageContour：图像轮廓](./python/ImageContour/main.ipynb)
- [x]  [ImageTransform：图像变换](./python/ImageTransform/ReadMe.md)
- [x]  [ImageSamplingAndClustering：图像采样与聚类](./python/ImageSamplingAndClustering/)
- [ ]  [ImagePointsDetection：图像边角点检测](./python/ImagePointsDetection/)
