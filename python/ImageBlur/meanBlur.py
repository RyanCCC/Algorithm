import cv2
import matplotlib.pyplot as plt

'''
实现均值滤波
优点：
效率高，思路简单

缺点：
均值滤波本身存在着固有的缺陷，即它不能很好地保护图像细节，在图像去噪的同时也破坏图像的细节，从而使图像变得模糊，不能很好地去除噪声点，尤其是椒盐噪声
'''
 
def blur_filter_func(filename):
    img = cv2.imread(filename)
    # rgbimg = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
 
    # 均值滤波: 简单的平均卷积操作
    result = cv2.blur(img, (5, 5))
    # 显示图像
    titles = ['origin image', 'blur image']
    images = [img, result]
    for i in range(2):
        show = cv2.cvtColor(images[i], cv2.COLOR_BGR2RGB)
        plt.subplot(1, 2, i+1), plt.imshow(show)
        plt.title(titles[i])
        plt.xticks([]), plt.yticks([])
    plt.show()
 
if __name__ == '__main__':
    filename = './image/ImageBlur/lenaNoise.png'
    blur_filter_func(filename)