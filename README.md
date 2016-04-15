# color-detection
By *[nilboy](https://github.com/nilboy)*

This project is a simple object detection tool, which use the color information.

You can easily develop your own object detector, only by writing an object configure file.
And I provide you a simple python interface.

I provide a car plate configure file, and you can use it to detect car plate.


## Compile and Install

    git clone https://github.com/nilboy/color-detection.git
    cd color-detection
    make
    make install 
    
    
## Test
    cd demo
    python car_plate_detector.py
    
## Create your own detector
    step 1:  write an object configure file (reference data/config/)
    step 2:  use python API of ColorDetector(reference demo/car_plate_detector.py)
