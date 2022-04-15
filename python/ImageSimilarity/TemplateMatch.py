'''
模板匹配算法
'''

import cv2
import numpy as np
import matplotlib.pyplot as plt

image_path = './image/ImageSimilarity/lena.jpg'
img = cv2.imread(image_path, 0)


template = cv2.imread('./image/ImageSimilarity/face.jpg', 0)

template_h, template_w = template.shape

methods = ['cv2.TM_CCOEFF', 'cv2.TM_CCOEFF_NORMED', 'cv2.TM_CCORR',
            'cv2.TM_CCORR_NORMED', 'cv2.TM_SQDIFF', 'cv2.TM_SQDIFF_NORMED']
 
res = cv2.matchTemplate(img, template, cv2.TM_SQDIFF)

min_val, max_val, min_index, max_index = cv2.minMaxLoc(res)

for meth in methods:
    img2 = img.copy()
 
    # 匹配方法的真值
    method = eval(meth)
    # print(meth, method)
    '''
        cv2.TM_CCOEFF 4
        cv2.TM_CCOEFF_NORMED 5
        cv2.TM_CCORR 2
        cv2.TM_CCORR_NORMED 3
        cv2.TM_SQDIFF 0
        cv2.TM_SQDIFF_NORMED 1
    '''
    res = cv2.matchTemplate(img, template, method)
    # 函数返回值就是矩阵的最小值，最大值，最小值的索引，最大值的索引。
    min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
 
    # 如果是平方差匹配 TM_SQDIFF 或归一化平方差匹配 TM_SQDIFF_NORMED，取最小值
    if method in [cv2.TM_SQDIFF, cv2.TM_SQDIFF_NORMED]:
        top_left = min_loc
    else:
        top_left = max_loc
    bottom_right = (top_left[0] + template_w, top_left[1] + template_h)
 
    # 画矩形
    cv2.rectangle(img2, top_left, bottom_right, 255, 2)
 
    plt.subplot(121), plt.imshow(res, cmap='gray')
    plt.xticks([]), plt.yticks([])  # 隐藏坐标轴
    plt.subplot(122), plt.imshow(img2, cmap='gray')
    plt.xticks([]), plt.yticks([])
    plt.suptitle(meth)
    plt.show()