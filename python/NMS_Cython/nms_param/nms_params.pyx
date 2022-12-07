import numpy as np
cimport numpy as np


cdef inline np.float32_t max(np.float32_t a, np.float32_t b):
    return a if a >= b else b

cdef inline np.float32_t min(np.float32_t a, np.float32_t b):
    return a if a <= b else b

def py_cpu_nms(np.ndarray[np.float32_t,ndim=2] dets, np.float thresh):
    # dets:(m,5)  thresh:scaler
    
    cdef np.ndarray[np.float32_t, ndim=1] x1 = dets[:,0]
    cdef np.ndarray[np.float32_t, ndim=1] y1 = dets[:,1]
    cdef np.ndarray[np.float32_t, ndim=1] x2 = dets[:,2]
    cdef np.ndarray[np.float32_t, ndim=1] y2 = dets[:,3]
    cdef np.ndarray[np.float32_t, ndim=1] scores = dets[:, 4]
    
    cdef np.ndarray[np.float32_t, ndim=1] areas = (y2-y1+1) * (x2-x1+1)
    cdef np.ndarray[np.int_t, ndim=1]  index = scores.argsort()[::-1]    # can be rewriten
    keep = []
    
    cdef long ndets = dets.shape[0]
    cdef np.ndarray[np.int_t, ndim=1] suppressed = np.zeros(ndets, dtype=np.int)
    
    cdef int _i, _j
    
    cdef int i, j
    
    cdef np.float32_t ix1, iy1, ix2, iy2, iarea
    cdef np.float32_t w, h
    cdef np.float32_t overlap, ious
    
    j=0
    
    for _i in range(ndets):
        i = index[_i]
        
        if suppressed[i] == 1:
            continue
        keep.append(i)
        
        ix1 = x1[i]
        iy1 = y1[i]
        ix2 = x2[i]
        iy2 = y2[i]
        
        iarea = areas[i]
        
        for _j in range(_i+1, ndets):
            j = index[_j]
            if suppressed[j] == 1:
                continue
            xx1 = max(ix1, x1[j])
            yy1 = max(iy1, y1[j])
            xx2 = min(ix2, x2[j])
            yy2 = min(iy2, y2[j])
    
            w = max(0.0, xx2-xx1+1)
            h = max(0.0, yy2-yy1+1)
            
            overlap = w*h 
            ious = overlap / (iarea + areas[j] - overlap)
            if ious>thresh:
                suppressed[j] = 1
    
    return keep