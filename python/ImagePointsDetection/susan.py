from PIL import Image
import numpy as np
#import gray
def img_extraction(image):
    """ img_extraction 函数利用susan角点检测算法，对图像进行处理"""
    print("最小灰度值，%d" % image.min())
    print("最大灰度值，%d" % image.max())
    threshold_value = (int(image.max())-int(image.min()))/10
    print("初始阈值为： %d" % threshold_value)
    offsetX = [
                -1, 0, 1,
            -2, -1, 0, 1, 2,
        -3, -2, -1, 0, 1, 2, 3,
        -3, -2, -1, 0, 1, 2, 3,
        -3, -2, -1, 0, 1, 2, 3,
            -2, -1, 0, 1, 2,
                -1, 0, 1
        ]
    offsetY = [
                -3, -3, -3,
            -2, -2, -2, -2, -2,
        -1, -1, -1, -1, -1, -1, -1,
             0, 0, 0, 0, 0, 0, 0,
             1, 1, 1, 1, 1, 1, 1,
                2, 2, 2, 2, 2,
                   3, 3, 3
        ]
    for i in range(3, image.shape[0] - 3):     # 利用圆形模板遍历图像，计算每点处的USAN值
        for j in range(3, image.shape[1] - 3):
            same = 0
            for k in range(0, 37):
                if abs(int(image[i + int(offsetY[k]), j + int(offsetX[k]), 0]) - int(image[i, j, 0])) < threshold_value:             # 计算相似度
                        same += 1
                    # print()
            if same < 18:
                image[i, j, 0] = 18 - same
                image[i, j, 1] = 18 - same
                image[i, j, 2] = 18 - same
            else:
                image[i, j, 0] = 0
                image[i, j, 1] = 0
                image[i, j, 2] = 0
def img_revise(image):
    """img_revise 函数用于对角点处理后的图像，进行非极大值抑制修正"""
    X = [-1, -1, -1, 0, 0, 1, 1, 1]     # X轴偏移
    Y = [-1, 0, 1, -1, 1, -1, 0, 1]     # Y轴偏移
    for i in range(4, image.shape[0]-4):
        for j in range(4, image.shape[1]-4):
            flag = 0
            for k in range(0, 8):
                if image[i, j, 0] <= image[int(i + X[k]), int(j + Y[k]), 0]:
                    flag += 1
                    break
            if flag == 0:       # 判断是否是周围8个点中最大的值，是则保留
                image[i, j, 0] = 255
                image[i, j, 1] = 255
                image[i, j, 2] = 255
            else:
                image[i, j, 0] = 0
                image[i, j, 1] = 0
                image[i, j, 2] = 0
if __name__ == '__main__':
    im = np.array(Image.open('checkerboard.jpg').convert('L').convert('RGB'))
    img_extraction(im)
    img_revise(im)
    result_img = Image.fromarray(im)
    result_img.show()