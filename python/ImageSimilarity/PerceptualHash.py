'''
感知哈希算法
'''

from PIL import Image
from cv2 import reduce
import numpy as np

EXTS = ['jpg', 'jpeg', 'JPG', 'JPEG', 'gif', 'GIF', 'png', 'PNG']

def avhash(image):
    if not isinstance(image, Image.Image):
        image = Image.open(image)
    image = image.resize((8, 8), Image.ANTIALIAS).convert('L')
    avg = np.sum(image)/64.
    result = np.ones_like(image)
    result = np.where(image<avg, 0, 1)
    result = result.flatten()
    return result

# 求汉明距离
def hamming(h1, h2):
    h, d = 0, h1^h2
    for item in d:
        if item == 0:
            h+=1
    return h


if __name__ == '__main__':
    image_path = './image/ImageSimilarity/lena.jpg'
    result = avhash(image_path)
    h = hamming(result, result)
    print(h/64)
    