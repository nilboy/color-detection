#include "color/color_detector.h"
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
using namespace cv;

ColorDetector::ColorDetector(string conf_path){
    ifstream fin(conf_path);
    string line;
    getline(fin,line);
    stringstream ss(line);
    ss>>detections_out_filename_>>resized_width_>>resized_height_;
    while(getline(fin,line)){
        objects_info_.push_back(ObjectInfo(line));
    }
    fin.close();
}
// resized the src image by width and height rescale
void ColorDetector::SetImage(string image_path){
    src_img_ = imread(image_path);
    int rows = src_img_.rows;
    int cols = src_img_.cols;
    scale_ratio_ = sqrt((resized_width_ * resized_height_)*1.0/(rows*cols));
    int new_rows = int(rows * scale_ratio_), new_cols = int(cols * scale_ratio_);
    resize(src_img_, src_img_, Size(new_cols, new_rows));
}
//
vector<RotatedRect> ColorDetector::DetectSingleObject(int index){
    ObjectInfo object_info = objects_info_[index];
    color_filter_.SetImage(src_img_);
    color_filter_.SetColorRange(object_info.get_min_h(), object_info.get_max_h());
    Mat src_filtered = color_filter_.GetFilteredImage();
    //binary image
    threshold(src_filtered, src_filtered, 0, 255,
        CV_THRESH_OTSU + CV_THRESH_BINARY);
    //close morphology
    Mat element = getStructuringElement(
        MORPH_RECT, Size(20, 10));
    morphologyEx(src_filtered, src_filtered, MORPH_CLOSE, element);

    Mat t_image;
    src_filtered.copyTo(t_image);
    //
    vector<RotatedRect> detections;
    //find the contours
    vector<vector<Point>> contours;

    findContours(src_filtered,
        contours,               // a vector of contours
        CV_RETR_EXTERNAL,       // extern contours
        CV_CHAIN_APPROX_NONE);  // all pixels of each contours

    vector<vector<Point>>::iterator itc = contours.begin();
    while (itc != contours.end()) {
        RotatedRect mr = minAreaRect(Mat(*itc));

        if (!VerifyObject(mr, object_info))
            itc = contours.erase(itc);
        else{
            ++itc;

            if (mr.size.width > mr.size.height){
                mr.size.width *= 1.0;
                mr.size.height *= 1.0;
            }
            else{
                mr.size.width *= 1.0;
                mr.size.height *= 1.0;
            }
            detections.push_back(mr);
        }
    }
    return detections;
}
//
void ColorDetector::Detect(){
    vector<RotatedRect> detections;
    ofstream fout(detections_out_filename_);
    for(int class_index = 0;class_index < objects_info_.size();class_index++){
        detections = DetectSingleObject(class_index);
        for(int object_index = 0; object_index < detections.size(); object_index++){
            Point2f vertices[4];
            fout<<class_index;
            detections[object_index].points(vertices);
            for(int point=0;point<4;point++){
                int t_x = std::min(int(vertices[point].x / scale_ratio_), src_img_.cols - 1);
                int t_y = std::min(int(vertices[point].y / scale_ratio_), src_img_.rows - 1);
                fout<<" "<<t_x<<" "<<t_y;
            }
            fout<<endl;
        }
    }
    fout.close();
}
//
bool ColorDetector::VerifyObject(RotatedRect mr, ObjectInfo &object_info) {

    if(mr.size.width==0 || mr.size.height==0)
        return false;

    int min_area = object_info.get_min_area();
    int max_area = object_info.get_max_area();
    float area = mr.size.height * mr.size.width;
    
    float min_w2h = object_info.get_min_w2h();
    float max_w2h = object_info.get_max_w2h();

    float w2h = (float)mr.size.width / (float)mr.size.height;
    int min_angle = object_info.get_min_angle();
    int max_angle = object_info.get_max_angle();
    float angle = std::fabs(mr.angle);
    if (w2h < 1)
        w2h = (float)mr.size.height / (float)mr.size.width;

    if ((area < min_area || area > max_area) || (w2h < min_w2h || w2h > max_w2h) \
     || (angle < min_angle || angle > max_angle))
        return false;
    else
        return true;
}
//maybe extend by you
ColorDetector::~ColorDetector(){
    return;
}

