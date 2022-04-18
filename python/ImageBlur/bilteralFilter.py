import cv2
import matplotlib.pyplot as plt
 
'''
双边滤波
'''
 
def bilateral_filter_func(filename):
    img = cv2.imread(filename)
 
    # 双边滤波：它能保持边界清晰的情况下有效的去除噪声，但是这种操作比较慢
    # 双边滤波拥有美颜的效果
    bilateral_filter = cv2.bilateralFilter(img, d=0, sigmaColor=100, sigmaSpace=15)
    # 显示图像
    titles = ['origin image', 'bilteral filter image']
    images = [img, bilateral_filter]
    for i in range(2):
        show = cv2.cvtColor(images[i], cv2.COLOR_BGR2RGB)
        plt.subplot(1, 2, i+1), plt.imshow(show)
        plt.title(titles[i])
        plt.xticks([]), plt.yticks([])
    plt.show()
 
if __name__ == '__main__':
    filename = './image/ImageBlur/lenaNoise.png'
    bilateral_filter_func(filename)