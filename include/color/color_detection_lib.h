#ifndef COLOR_COLOR_DETECTION_LIB_H_
#define COLOR_COLOR_DETECTION_LIB_H_
#include <string>
#include "color/color_detector.h"
void InitDetector(std::string configure_path);
void SetImage(std::string image_path);
void Compute();
void FreeDetector();
extern "C"{
    void export_init_detector(const char *configure_path);
    void export_set_image(const char *image_path);
    void export_compute();
    void export_free_detector();
}
#endif