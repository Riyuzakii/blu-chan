import numpy as np
import cv2
import glob
import os
import pickle
import matplotlib.pyplot as plt
import pylab
import time
import imageio
from scipy.misc import imread, imresize, imsave

out_examples = 0
MOV_AVG_LENGTH = 5

def main():
	t_bin0 = time.time()
    img_b = image_binary(img)
    t_bin = time.time() - t_bin0

def image_binary(img, sobel_kernel=7, mag_thresh=(3, 255), s_thresh=(170, 255)):
    # --------------------------- Binary Thresholding ----------------------------
    # Binary Thresholding is an intermediate step to improve lane line perception
    # it includes image transformation to gray scale to apply sobel transform and
    # binary slicing to output 0,1 type images according to pre-defined threshold.
    #
    # Also it's performed RGB to HSV transformation to get S information which in-
    # tensifies lane line detection.
    #
    # The output is a binary image combined with best of both S transform and mag-
    # nitude thresholding.

    hls = cv2.cvtColor(img, cv2.COLOR_RGB2HLS)
    gray = hls[:, :, 1]
    s_channel = hls[:, :, 2]


    # Binary matrixes creation
    sobel_binary = np.zeros(shape=gray.shape, dtype=bool)
    s_binary = sobel_binary
    combined_binary = s_binary.astype(np.float32)

    # Sobel Transform
    sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=sobel_kernel)
    sobely = 0 #cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=sobel_kernel)

    sobel_abs = np.abs(sobelx**2 + sobely**2)
    sobel_abs = np.uint8(255 * sobel_abs / np.max(sobel_abs))

    sobel_binary[(sobel_abs > mag_thresh[0]) & (sobel_abs <= mag_thresh[1])] = 1

    # Threshold color channel
    s_binary[(s_channel >= s_thresh[0]) & (s_channel <= s_thresh[1])] = 1

    # Combine the two binary thresholds

    combined_binary[(s_binary == 1) | (sobel_binary == 1)] = 1
    combined_binary = np.uint8(255 * combined_binary / np.max(combined_binary))

    #plt.imshow(combined_binary, cmap='gray')
    #plt.show()

    # ---------------- MASKED IMAGE --------------------
    offset = 100
    mask_polyg = np.array([[(0 + offset, img.shape[0]),
                            (img.shape[1] / 2.5, img.shape[0] / 1.65),
                            (img.shape[1] / 1.8, img.shape[0] / 1.65),
                            (img.shape[1], img.shape[0])]],
                          dtype=np.int)

    # mask_polyg = np.concatenate((mask_polyg, mask_polyg, mask_polyg))

    # Next we'll create a masked edges image using cv2.fillPoly()
    mask_img = np.zeros_like(combined_binary)
    ignore_mask_color = 255

    # This time we are defining a four sided polygon to mask
    # Applying polygon
    cv2.fillPoly(mask_img, mask_polyg, ignore_mask_color)
    masked_edges = cv2.bitwise_and(combined_binary, mask_img)

    return masked_edges