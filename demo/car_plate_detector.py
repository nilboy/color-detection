#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
sys.path.append('../python')
from color_detection.color_detector import *
import cv2

if __name__ == '__main__':
    plate_detector = ColorDetector('../data/config/car_plate.ini')
    plate_detector.compute('../data/image/demo.jpg')
    f = open('detections.txt')
    src = cv2.imread('../data/image/demo.jpg')
    for line in f:
        points = line.strip().split(' ')
        points = [ int(item) for item in points[1:]]

        cv2.line(src, (points[0],points[1]), (points[2], points[3]),(0,0,255), 3)
        cv2.line(src, (points[2], points[3]), (points[4], points[5]), (0,0,255), 3)
        cv2.line(src, (points[4], points[5]), (points[6], points[7]), (0,0,255), 3)
        cv2.line(src, (points[6], points[7]), (points[0],points[1]), (0,0,255), 3)

    cv2.imshow('demo',src)
    cv2.waitKey(1200)
    cv2.destroyAllWindows()