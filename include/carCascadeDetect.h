#ifndef __CARCASCADEDETECT_H
#define __CARCASCADEDETECT_H
 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

 #include <iostream>
 #include <stdio.h>
 #include <ctime>

 using namespace std;
 using namespace cv;

class carCascadeDetect
{
private:
        const int minSize, maxSize;
        string win;
        string cascadeName;
        CascadeClassifier csd;


public:
        carCascadeDetect();
        ~carCascadeDetect();
        void detectAndDisplay( Mat frame );
        void detectGrayImgAndDisplay(Mat gray);
        void drawCars(Mat& frame, std::vector<Rect> cars);
        vector<Rect> detectGrayImgAndReturnRect(Mat gray);
};

#endif // __CARCASCADEDETECT_H
