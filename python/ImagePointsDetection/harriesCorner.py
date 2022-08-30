from ast import arg
from email.mime import image
from tarfile import SYMTYPE
import cv2
import numpy as np
import argparse
import operator


def parse_opt():
    parser = argparse.ArgumentParser(description="harries Corner")
    parser.add_argument('--window_size', type=int, default=5, help='window size')
    parser.add_argument('--k_corner_response', type=float, default=0.04, help='Value of Harris corner constant between 0.04 - 0.06.')
    parser.add_argument('--threshold', type = int, default=10000, help='corner threshole')
    parser.add_argument('--image', type=str, required=True, help='process image')
    return parser

def find_harris_corners(input_img, k, window_size, threshold):
    
    corner_list = []
    output_img = cv2.cvtColor(input_img.copy(), cv2.COLOR_GRAY2RGB)
    
    offset = int(window_size/2)
    y_range = input_img.shape[0] - offset
    x_range = input_img.shape[1] - offset
    
    
    dy, dx = np.gradient(input_img)
    Ixx = dx**2
    Ixy = dy*dx
    Iyy = dy**2
    
    
    for y in range(offset, y_range):
        for x in range(offset, x_range):
            
            #Values of sliding window
            start_y = y - offset
            end_y = y + offset + 1
            start_x = x - offset
            end_x = x + offset + 1
            
            #The variable names are representative to 
            #the variable of the Harris corner equation
            windowIxx = Ixx[start_y : end_y, start_x : end_x]
            windowIxy = Ixy[start_y : end_y, start_x : end_x]
            windowIyy = Iyy[start_y : end_y, start_x : end_x]
            
            #Sum of squares of intensities of partial derevatives 
            Sxx = windowIxx.sum()
            Sxy = windowIxy.sum()
            Syy = windowIyy.sum()

            #Calculate determinant and trace of the matrix
            det = (Sxx * Syy) - (Sxy**2)
            trace = Sxx + Syy
            
            #Calculate r for Harris Corner equation
            r = det - k*(trace**2)

            if r > threshold:
                corner_list.append([x, y, r])
                output_img[y,x] = (0,0,255)
    
    return corner_list, output_img 


def main(args):
    window_size = args.window_size
    k = args.k_corner_response
    thresh = args.threshold
    image_path = args.image
    # load image
    img = cv2.imread(image_path)
    if img is None:
        print('Image does not exist.')
        return
    if len(img.shape) == 3:
            img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    if len(img.shape) == 4:
        img = cv2.cvtColor(img, cv2.COLOR_RGBA2GRAY)
    cornerList, finalImg = find_harris_corners(img,float(k), int(window_size), int(thresh))
    if finalImg is not None:
        cv2.imwrite("finalimage.png", finalImg)
    # Write top 100 corners to file
    cornerList.sort(key=operator.itemgetter(2))
    outfile = open('corners.txt', 'w')
    for i in range(100):
        outfile.write(str(cornerList[i][0]) + ' ' + str(cornerList[i][1]) + ' ' + str(cornerList[i][2]) + '\n')
    outfile.close()



if __name__ == '__main__':
    parser = parse_opt()
    args = parser.parse_args()
    main(args)


