import cv2 as cv
import numpy as np
import time
import concurrent.futures

class NCCTemplateMatch:
    def __init__(self, ref_imgs, target_imgs, scores, tpl_sums, tpl_sqr_sums, target_sums, target_sqr_sums):
        self.ref_imgs = ref_imgs
        self.target_imgs = target_imgs
        self.scores = scores
        self.tpls_sums = tpl_sums
        self.tpls_sqsums = tpl_sqr_sums
        self.target_sums = target_sums
        self.target_sqsums = target_sqr_sums
        self.nms_boxes = []
    
    def run_match(self):
        num_ps = min(6, len(self.ref_imgs))
        # print("num_ps: ", num_ps)
        start = time.perf_counter()
        with concurrent.futures.ProcessPoolExecutor(num_ps) as executor:
            matched = executor.map(self.ncc_run, self.ref_imgs, self.target_imgs, self.tpls_sums, self.tpls_sqsums, self.target_sums, self.target_sqsums, self.scores)
            self.nms_boxes = list(matched)
        end = time.perf_counter()
        print(f'Finished in {round(end-start, 2)} seconds')

    def ncc_run(self, tpl_gray, target_gray, tpl_sum, tpl_sqsum, target_sum, target_sqsum, score):
        print("run once~~~~")
        th, tw = tpl_gray.shape
        min_step = max(1, min(th // 16, tw // 16))
        h, w = target_gray.shape
        sr = 1 / (th * tw)
        t_s1 = tpl_sum[th, tw]
        t_s1_2 = t_s1 * t_s1 * sr
        t_s1_1 = t_s1 * sr
        t_s2 = tpl_sqsum[th, tw]
        sum_t = np.sqrt(t_s2 - t_s1_2)
        row = 0
        boxes = []
        confidences = []
        while row < (h - th+1):
            col = 0
            while col < (w - tw+1):
                s1 = self.get_block_sum(target_sum, col, row, col + tw, row + th)
                s2 = self.get_block_sum(target_sqsum, col, row, col + tw, row + th)
                sum1 = t_s1_1 * s1
                ss_sqr = s2 - s1 * s1 * sr
                if ss_sqr < 0:  # fix issue, 精度问题
                    ss_sqr = 0.0
                sum2 = sum_t * np.sqrt(ss_sqr)
                sum3 = np.sum(np.multiply(tpl_gray, target_gray[row:row + th, col:col + tw]))
                if sum2 == 0.0:
                    ncc = 0.0
                else:
                    ncc = (sum3 - sum1) / sum2
                if ncc > score:
                    boxes.append([col, row, tw, th])
                    confidences.append(float(ncc))
                    col += tw//2
                else:
                    col += min_step
            row += min_step

        # NMS Process
        nms_indices = cv.dnn.NMSBoxes(boxes, confidences, 0.5, 0.5)
        det_boxes = []
        print(nms_indices)
        for i in range(len(nms_indices)):
            rect_box = boxes[nms_indices[i]]
            det_boxes.append(rect_box)
        return det_boxes

    def get_block_sum(self, integal_img, x1, y1, x2, y2):
        t1 = integal_img[y1, x1]
        t2 = integal_img[y1, x2]
        t3 = integal_img[y2, x1]
        t4 = integal_img[y2, x2]
        s = t4 - t2 - t3 + t1
        return s

if __name__ == '__main__':
    print('=====test ncc=====')
    tpl_image = cv.imread('./checkerboard.jpg')
    target_image = cv.imread('./finalimage.png')
    # 灰度化
    tpl_gray = cv.cvtColor(tpl_image, cv.COLOR_BGR2GRAY)
    target_gray = cv.cvtColor(target_image, cv.COLOR_BGR2GRAY)
    # 归一化
    tpl_gray = np.float32(tpl_gray/255.0)
    target_gray = np.float32(target_gray/255.0)

    tpl_sum, tpl_sqsum = cv.integral2(tpl_gray)
    t_sum, t_sqsum = cv.integral2(target_gray)

    matcher = NCCTemplateMatch([tpl_gray], [target_gray], [0.85],[tpl_sum], [tpl_sqsum], [t_sum], [t_sqsum])
    matcher.run_match()
    for rect_box in matcher.nms_boxes[0]:
        cv.rectangle(target_image, (rect_box[0], rect_box[1]),
                 (rect_box[0]+rect_box[2], rect_box[1]+rect_box[3]), (0, 0, 255), 2, 8, 0)
    cv.imshow("result", target_image)
    cv.waitKey(0)
    cv.destroyAllWindows()


