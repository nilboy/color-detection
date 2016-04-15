#ifndef COLOR_COLOR_DETECTOR_H_
#define COLOR_COLOR_DETECTOR_H_
#include <vector>
#include <opencv2/opencv.hpp>
#include <string>
#include "color/object_info.h"
#include "color/color_filter.h"
class ColorDetector{
public:
    //constructor from configure file
    //the format of configure file is as below
    //Example:
    //  detection_out_filename resized_width resized_height
    //  object_info_line1
    //  object_info_line2
    //  ..........
    ColorDetector(std::string conf_path);
    //destructor function , clean some temp file
    ~ColorDetector();
    void SetImage(std::string image_path);
    //detect all objects , and write the result to detection_out_filename_
    //the format of this file is as below
    //Example:
    //  objectindex1 4 points coordinates
    //  objectindex2 4 points coordinates 
    void Detect();
private:
    //Return the detection of object(index)
    std::vector<cv::RotatedRect> DetectSingleObject(int index);
    //Return true if detection mr belongs to the detected object
    bool VerifyObject(cv::RotatedRect mr, ObjectInfo &object_info);
private:
    ColorFilter color_filter_;
    // all detected objects class info
    std::vector<ObjectInfo> objects_info_;
    // the output file of detections result
    std::string detections_out_filename_;
    // detected image
    cv::Mat src_img_;
    int resized_width_;
    int resized_height_;
    // resized ratio of the src image
    double scale_ratio_;
};
#endif