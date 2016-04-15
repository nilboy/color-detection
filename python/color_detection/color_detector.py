#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from .config_parser import *
from ctypes import cdll
import os
class ColorDetector(object):
    """object detector by color

    """
    def __init__(self,config_file=None):
        curdir = os.path.dirname(os.path.abspath(__file__))
        self.detector = cdll.LoadLibrary( curdir + '/libcolordetection.so')
        self.cfp = ConfigProcessor()
        if config_file:
            self.init(config_file)

    def init(self, config_file):
        """init the detector by configure file

        """
        self.out_config_file = self.cfp.process(config_file)
        self.detector.export_init_detector(self.out_config_file)
        #self.detector.export_init_detector('../../conf.ini')

    def compute(self, img_path):
        """detect the image

        """
        if not os.path.exists(img_path):
            raise Exception(str(img_path) + ' doesn\'t exist')
        self.detector.export_set_image(img_path)
        self.detector.export_compute()

        #
        
        src_file = open(self.cfp.output_file,'r')
        lines = []
        for line in src_file:
            items = line.strip().split(' ')
            index = int(items[0])
            object_name = self.cfp.objects_names[index]
            line = object_name + line[len(items[0]):]
            lines.append(line)
        src_file.close()
        dst_file = open(self.cfp.output_file,'w')
        for line in lines:
            dst_file.write(line)
        dst_file.close()
        
    def __del__(self):
        """release the detector

        """
        os.system('rm ' + str(self.out_config_file))
        self.detector.export_free_detector()