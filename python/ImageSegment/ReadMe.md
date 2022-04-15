## 图像分割算法

操作步骤如下：
1. 将图像转换灰度并进行去噪
2. 使用Sobel算子计算X， Y方向上的梯度，目的是识别边缘。
3. 去噪声：首先使用低通滤波平滑图像，有助于平滑图像中的高频噪声。低筒滤波器的目的是降低图像的变化率。
4. 图像形态学处理，进行开操作，先腐蚀后膨胀，目的是闭合区域的空洞地方
5. 找到轮廓

```
cv2.threshold(src, # 一般是灰度图像
   num1, # 图像阈值
   num2, # 如果大于或者num1, 像素值将会变成 num2
# 最后一个二值化参数
   cv2.THRESH_BINARY      # 将大于阈值的灰度值设为最大灰度值，小于阈值的值设为0
   cv2.THRESH_BINARY_INV  # 将大于阈值的灰度值设为0，大于阈值的值设为最大灰度值
   cv2.THRESH_TRUNC       # 将大于阈值的灰度值设为阈值，小于阈值的值保持不变
   cv2.THRESH_TOZERO      # 将小于阈值的灰度值设为0，大于阈值的值保持不变
   cv2.THRESH_TOZERO_INV  # 将大于阈值的灰度值设为0，小于阈值的值保持不变
)
```

```
cv2.findContours(mask.copy(),
   # cv2.RETR_EXTERNAL,             #表示只检测外轮廓
   # cv2.RETR_CCOMP,                #建立两个等级的轮廓,上一层是边界
   cv2.RETR_LIST,                 #检测的轮廓不建立等级关系
   # cv2.RETR_TREE,                   #建立一个等级树结构的轮廓
   # cv2.CHAIN_APPROX_NONE,           #存储所有的轮廓点，相邻的两个点的像素位置差不超过1
   cv2.CHAIN_APPROX_SIMPLE,       #例如一个矩形轮廓只需4个点来保存轮廓信息
   # cv2.CHAIN_APPROX_TC89_L1,
   # cv2.CHAIN_APPROX_TC89_KCOS
  )
```