//color_filter.h
//filter the specific color channel of input image ,and generate the binary image
#ifndef COLOR_COLOR_FILTER_H_
#define COLOR_COLOR_FILTER_H_
#include<opencv2/opencv.hpp>
class ColorFilter{
public:
    ColorFilter();
    void SetImage(cv::Mat &img);
    void SetColorRange(int min_h, int max_h);
    cv::Mat GetFilteredImage(bool adaptive_minsv=true);
private:
    cv::Mat src_img_;
    //HSV channels, minimum h of given color , maximum h of given color
    int min_h_;
    int max_h_;
};
#endif
