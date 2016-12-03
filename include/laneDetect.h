#ifndef __LANEDETECT_H
#define __LANEDETECT_H
 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include "opencv2/imgcodecs.hpp"

 #include <iostream>
 #include <stdio.h>
 #include <cmath>

 using namespace std;
 using namespace cv;

class laneDetect
{
private:
        const float PI;
        const int Horizontal;
        const int min_threshold;
        const int max_trackbar;

        string probabilistic_name;
        Mat sobelImg;
        vector<Vec4i> p_lines;
        int p_trackbar;

public:
        laneDetect();
        ~laneDetect();

        int sobelProcess(Mat grayImg, Mat& sobelImg);
        int probabilisticHoughAndDisplay(Mat img);
        float lineAngle(Vec4i line);
        void deleteHorizontal(vector<Vec4i> &lines);
        void updateLines(Mat gray, vector<Vec4i> &lines);
        void drawLanes(Mat& img, const vector<Vec4i> lines);
};

#endif // __LANEDETECT_H

