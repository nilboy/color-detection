#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
import ConfigParser
import time

class ConfigProcessor(object):
    """
    parser the configure file ,and generate the c++ libcolordetection.so 
    configure file. And record some information
    """

    def __init__(self):
        self.parser = ConfigParser.ConfigParser()
        self.objects_names = []
        self.output_file = ''

    def process(self, config_file):
        """parse the configure file

        generate some useful information and record them
        """
        self.objects = []
        self.objects_names = []
        self.config_file = config_file
        self.parser.read(self.config_file)
        sections = self.parser.sections()
        if not 'detector' in sections:
            return False
        try:
            index = 0
            for i in xrange(len(sections)):
                if sections[i] == 'detector':
                    self.output_file = self.parser.get(sections[i], 'output_file')
                    self.resized_width = int(self.parser.get(sections[i], 'resized_width'))
                    self.resized_height = int(self.parser.get(sections[i], 'resized_height'))
                else:
                    info = self.__get_object_info(sections[i])
                    self.objects.append(info[1])
                    self.objects_names.append(str(info[0]))
                    index += 1
        except Exception, e:
            print 'configure file wrong, please check it'
            raise e
        else:
            out_config_file_name = str(int(time.time()*1000)) + '.ini'
            out_config_file = open(out_config_file_name, 'w')
            out_config_file.write(str(self.output_file) + ' ' + str(self.resized_width) + ' ' + str(self.resized_height) + '\n')
            for i in xrange(len(self.objects)):
                out_config_file.write(self.objects[i])
            out_config_file.close()
            return out_config_file_name
    
    def get_objects_names():
        """Return the object class names

        """
        return self.objects_names

    def __get_object_info(self, section):
        """get the object class info of section

        """
        name = self.parser.get(section, 'name')
        min_angle = int(self.parser.get(section, 'min_angle'))
        max_angle = int(self.parser.get(section, 'max_angle'))
        min_w2h = float(self.parser.get(section, 'min_w2h'))
        max_w2h = float(self.parser.get(section, 'max_w2h'))
        min_area = int(self.parser.get(section, 'min_area'))
        max_area = int(self.parser.get(section, 'max_area'))
        min_h = int(self.parser.get(section, 'min_h'))
        max_h = int(self.parser.get(section, 'max_h'))
        info = str(min_angle) + ' ' + str(max_angle) + ' ' + str(min_w2h) + ' ' + \
            str(max_w2h) + ' ' + str(min_area) + ' ' + str(max_area) + ' ' + \
            str(min_h) + ' ' + str(max_h) + '\n'
        return (name, info)