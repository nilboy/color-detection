#include "color/object_info.h"
#include <sstream>
using namespace std;
ObjectInfo::ObjectInfo(int min_angle, int max_angle, double min_w2h, double max_w2h, \
    int min_area, int max_area, int min_h, int max_h){
    min_angle_ = min_angle;
    max_angle_ = max_angle;
    min_w2h_ = min_w2h;
    max_w2h_ = max_w2h;
    min_area_ = min_area;
    max_area_ = max_area;
    min_h_ = min_h;
    max_h_ = max_h;
}
ObjectInfo::ObjectInfo(std::string line){
    stringstream ss(line);
    ss>>min_angle_>>max_angle_>>min_w2h_>>max_w2h_>>min_area_>>max_area_>>min_h_>>max_h_;
}
