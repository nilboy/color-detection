#include "color/color_detection_lib.h"
#include <memory>
using namespace std;
shared_ptr<ColorDetector> detector;
void InitDetector(string configure_path){
    detector = std::make_shared<ColorDetector>(configure_path); 
}
void SetImage(string image_path){
    detector->SetImage(image_path);
}
void Compute(){
    detector->Detect();
}
void FreeDetector(){
    detector.reset();
}
extern "C"{
    void export_init_detector(const char *configure_path){
        InitDetector(configure_path);
    }
    void export_set_image(const char *image_path){
        SetImage(image_path);
    }
    void export_compute(){
        Compute();
    }
    void export_free_detector(){
        FreeDetector();
    }
}
