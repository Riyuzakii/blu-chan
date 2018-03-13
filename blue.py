import cv2
import numpy as np

img = cv2.imread('./today/frame0000.jpg')
b,g,r = cv2.split(img)

th3 = cv2.adaptiveThreshold(b,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY,51,31)
cv2.imshow('ImageWindow', th3)

cv2.waitKey()