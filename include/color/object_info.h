#ifndef COLOR_OBJECT_INFO_H_
#define COLOR_OBJECT_INFO_H_
#include <string>
class ObjectInfo{
private:
    // angle range [-90,90]
    int min_angle_ = -100;
    int max_angle_ = 100;
    // width to height range
    double min_w2h_ = 0.1;
    double max_w2h_ = 10;
    //area range
    int min_area_ = 0;
    int max_area_ = 9999999;
    //color H(in HSV) range [0,180]
    int min_h_ = 0;
    int max_h_ = 180;
public:
    ObjectInfo(int min_angle, int max_angle, double min_w2h, double max_w2h, int min_area, int max_area, int min_h, int max_h);
    ObjectInfo(std::string line);
    int get_min_angle(){
        return min_angle_;
    }
    int get_max_angle(){
        return max_angle_;
    }
    double get_min_w2h(){
        return min_w2h_;
    }
    double get_max_w2h(){
        return max_w2h_;
    }
    int get_min_area(){
        return min_area_;
    }
    int get_max_area(){
        return max_area_;
    }
    int get_min_h(){
        return min_h_;
    }
    int get_max_h(){
        return max_h_;
    }
};
#endif
