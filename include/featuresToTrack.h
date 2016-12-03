#ifndef __FEATURESTOTRACK_H
#define __FEATURESTOTRACK_H
 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include "opencv2/imgcodecs.hpp"
 #include "opencv2/video/tracking.hpp"

 #include <iostream>
 #include <stdio.h>
 #include <cmath>

 using namespace std;
 using namespace cv;

class featuresToTrack
{
private:
        const int Min_Y;
        const int MAX_COUNT;
        Mat prevGray, gray;
        vector<Point2f> points[2];
        TermCriteria termcrit;
        Size winSize;

public:
        featuresToTrack();
        ~featuresToTrack();

        void updateTrackPoints(Mat grayImg);
        void addTrackPoints(Point2f point);
        void drawTrackPoints(Mat img);
        void clearAllTrackPoints()      { points[0].clear();   points[1].clear();}
};

#endif // __FEATURESTOTRACK_H


