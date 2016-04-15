//color_filter.cc
//filter the specific color channel of input image ,and generate the binary image
#include "color/color_filter.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
using namespace std;
using namespace cv;
ColorFilter::ColorFilter(){
    return;
}
void ColorFilter::SetImage(cv::Mat &img){
    src_img_=img;
}
void ColorFilter::SetColorRange(int min_h,int max_h){
    min_h_=min_h;
    max_h_=max_h;
}
cv::Mat ColorFilter::GetFilteredImage(bool adaptive_minsv){
    // min and max cared sv channel
    const double kMaxSv = 255;
    const double kMinReferenceSv = 64;
    const double kMinAbsoluteSv = 95;
    double range_h = double((this->max_h_ - this->min_h_)/2);
    double average_h = double((this->max_h_ + this->min_h_)/2);

    Mat src_hsv;
    //change rgb image to hsv space
    cvtColor(src_img_, src_hsv, CV_BGR2HSV);
    vector<Mat> hsv_split;
    split(src_hsv, hsv_split);
    equalizeHist(hsv_split[2], hsv_split[2]);
    merge(hsv_split, src_hsv);
    //if the image is continue,merge it to one channel
    int channels = src_hsv.channels();
    int num_rows = src_hsv.rows;
    int num_cols = src_hsv.cols * channels;
    if(src_hsv.isContinuous()){
        num_cols *= num_rows;
        num_rows = 1; 
    }
    uchar *point=nullptr;
    for(int row=0;row<num_rows;row++){
        point = src_hsv.ptr<uchar>(row);
        for(int col=0;col<num_cols;col+=3){
            //HSV value for pixel[row][col]
            int h = point[col];
            int s = point[col+1];
            int v = point[col+2];
            bool color_matched = false;
            if(h > this->min_h_ && h < this->max_h_){
                double h_diff = fabs(h - average_h);
                double rate = h_diff/range_h;
                double min_sv = 0;
                if(adaptive_minsv){
                    min_sv = kMinReferenceSv - kMinReferenceSv/2*(1 - rate);
                }
                else{
                    min_sv = kMinAbsoluteSv;
                }
                if(s > min_sv && s < kMaxSv && v > min_sv && v < kMaxSv)
                    color_matched = true;
            }
            if(color_matched){
                point[col] = 0;
                point[col+1] = 0;
                point[col+2] = 255;
            }
            else{
                point[col] = 0;
                point[col+1] = 0;
                point[col+2] = 0;
            }
        }
    }
    split(src_hsv, hsv_split);
    return hsv_split[2];  
}
