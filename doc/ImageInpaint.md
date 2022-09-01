# 图像修复

基于C++语言实现图像修复，工程地址：`../C++/ImageInpaint`。使用方式：
```
mkdir build && cd build
cmake ..
cmake --build . --config Release
```
构建完成后，使用如下命令运行：
```
./build/inpaint sample.jpeg
```

## 图像修复算法

### INPAINT_NS : Navier-Stokes based Inpainting

参考论文：[Navier-Stokes, Fluid Dynamics, and Image and Video Inpainting](https://www.math.ucla.edu/~bertozzi/papers/cvpr01.pdf)


### INPAINT_TELEA : Fast Marching Method based

参考论文：[An Image Inpainting Technique Based on the Fast Marching Method](https://www.semanticscholar.org/paper/An-Image-Inpainting-Technique-Based-on-the-Fast-Telea/67d0cb47d14150daff08980efbea9f1267d3a4e5?p2df)


### OpenCV实现

```C
void inpaint(
    Mat src,
    Mat inpaintMask,
    Mat dst,
    double inpaintRadius,
    int flags
    )

```

```python
import cv2
dst = cv2.inpaint(src, inpaintMask, inpaintRadius, flags)
```

参数说明：
- src = Source image
- inpaintMask = A binary mask indicating pixels to be inpainted.
- dst = Destination image
- inpaintRadius = Neighborhood around a pixel to inpaint. Typically, if the regions to be inpainted are thin, smaller values produce better results (less blurry).
- flags : INPAINT_NS (Navier-Stokes based method) or INPAINT_TELEA (Fast marching based method)

### 结果展示

![](./src/Imageinpaint.png)