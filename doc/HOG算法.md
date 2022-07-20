## HOG特征算法

HOG（Histogram of Oriented Gradients）特征检测算法，是一种解决人体目标检测的图像描述子，用于表征图像局部梯度方向和梯度强度分布特性的描述符。该算法的主要思想是：在边缘具体未知未知的
情况下，边缘方向的分布也可以很好地表示行人的外形轮廓。算法的论文地址：[Histograms of Oriented Gradients for Human Detection](https://hal.inria.fr/file/index/docid/548512/filename/hog_cvpr2005.pdf)。

![image](https://user-images.githubusercontent.com/27406337/179682007-2410c97d-86c3-41a0-9f83-6e122c33e059.png)

HOG算法根据论文有如下几个步骤：

1. 颜色空间归一化Normalize gamma & color
2. 计算梯度Compute gradient
3. 生成梯度方向直方图
4. 重叠块直方图归一化
5. HOG特征

### 颜色空间归一化

颜色空间归一化是对采集到的人脸进行图像的预处理，处理光线太暗或者太强的情况，主要有两个步骤：图像灰度化以及Gamma校正。

1. 图像灰度化
彩色图像转换成灰度图，转换公式：$$Gray = 0.3\times R+0.59 \times G +0.11 \times B$$

2.Gamma校正
在图像光照不均匀的情况下，通过Gamma校正，将图像整体亮度提高或降低。公式为$$Y(x, y) = I(x, y)^{\gamma}$$其中$\gamma = 0.5$采用平方根的方法，同样也可以用对数法进行Gamma校正。

### 梯度计算

经过图像的颜色空间归一化后，可以进行梯度的计算，分别在垂直方向和水平方向上求梯度，梯度算法分别为：
- 水平方向：$[-1\quad 0\quad 1]$
- 垂直方向：$[-1\quad 0\quad 1]^T$

则有：
$$G_x(x, y) = I(x+1, y)-I(x-1, y)$$ $$G_x(x, y) = I(x, y+1)-I(x, y-1)$$ $$G(x, y)=\sqrt{G_x(x, y)^2+G_y(x, y)^2}$$ $$\theta(x, y) = arctan(\frac{G_y(x, y)}{G_x(x,y)})$$

### 梯度方向直方图

![image](https://user-images.githubusercontent.com/27406337/179684557-83114208-f856-4dc6-b008-5dfa9d3ea625.png)


### 重叠块方向直方图

![image](https://user-images.githubusercontent.com/27406337/179684885-a339e6d3-ac70-4766-893d-7220d00938e4.png)



