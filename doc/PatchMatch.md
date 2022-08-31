## PatchMatch

PatchMatch算法出自论文：PatchMatch: A Randomized Correspondence Algorithm for Structural Image Editing，它是找近似最近邻的方法，效率非常快，它的基本思想如下图所示：
![](../doc/src/PatchMatch_20220831112824.png)

根据上图，以蓝色为主题，A表示的是原图像，矩形框代表待修复的patch块，要修复patch_A块就需要在B图（原图）中搜索一个最合适的块patch_B，而从patch_A到patch_B的偏移量就是offset，如图中箭头所示。

蓝色为主patch块，红色是蓝色向左移一个像素，绿色是蓝色向上移一个像素。上图  (a)：随机初始化  (b)：传播  (c)：随机扰动搜索。PatchMatch 的核心思想是利用图像的连续性（consistence）， 一个图像A的patch_A（蓝色）附近的Patch块（红色绿色）的最近邻（B中的红色绿色框）最有可能出现在Patch_A的最近邻（B中的蓝色框）附近，利用这种图像的连续性大量减少搜索的范围，通过迭代的方式保证大多数点能尽快收敛。

