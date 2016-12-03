#include "../include/laneDetect.h"

laneDetect::laneDetect() : PI(3.1415926535), Horizontal(12), p_trackbar(1), min_threshold(50), max_trackbar(550)
{
        probabilistic_name = "Hough Lines";
        cout << "laneDetect()" << endl;
}

laneDetect::~laneDetect()
{
        cout << "~laneDetect()" << endl;
}

int laneDetect::sobelProcess(Mat grayImg, Mat& sobelImg)
{
        int scale = 1;
        int delta = 0;
        int ddepth = CV_16S;

        if(grayImg.empty())
                return -1;
        //![reduce_noise]
        GaussianBlur( grayImg, grayImg, Size(3,3), 0, 0, BORDER_DEFAULT );

        //![sobel]
        /// Generate grad_x and grad_y
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;

        /// Gradient X
        //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        Sobel( grayImg, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );

        /// Gradient Y
        //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
        Sobel( grayImg, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
        //![sobel]

        //![convert]
        convertScaleAbs( grad_x, abs_grad_x );
        convertScaleAbs( grad_y, abs_grad_y );
        //![convert]

        //![blend]
        /// Total Gradient (approximate)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, sobelImg );
        //![blend]

        this->sobelImg = sobelImg;
//        //![display]
//        imshow( "sobel image", sobelImg );
}

int laneDetect::probabilisticHoughAndDisplay(Mat img)
{
        Mat threshImg;
/// Erode, dilate
        int an = 3;
        Mat element = getStructuringElement(MORPH_RECT, Size(an*2+1, an*2+1), Point(an, an) );
        dilate(img, img, element);

        sobelProcess(img, sobelImg);

        threshold(sobelImg, threshImg, 88, 255, CV_THRESH_BINARY);
        HoughLinesP( threshImg, p_lines, 1, CV_PI/180, min_threshold + p_trackbar, 30, 10 );

    // Delete the horizontal lines
//    deleteHorizontal(p_lines);

        for( size_t i = 0; i < p_lines.size(); i++ )
        {
                Vec4i l = p_lines[i];
                if(abs( lineAngle( p_lines[i]) ) > Horizontal)
                        line( img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,0), 3, LINE_AA);
        }

        // adaptive change p_trackbar value
        int s = p_lines.size();
        if(s > 25 &&
           p_trackbar <= (max_trackbar - 10))
                p_trackbar += 10;
        else if(s < 6 && p_trackbar >= 10)
                p_trackbar -= 10;

        cout << "p_trackbar value: " << p_trackbar << endl;
        cout << "line number: " << s << endl;

        imshow( probabilistic_name, img);
}

float laneDetect::lineAngle(Vec4i line)
{
        int dx = line[2] - line[0];
        int dy = line[3] - line[1];
        float angle;
        angle = atan( (double)dy / (double)dx );
        angle *= 180 / PI;

        return angle;
}

void laneDetect::deleteHorizontal(vector<Vec4i> &lines)
{
        bool ept(false);
        if(lines.empty())
        {
                lines = p_lines;
                ept = true;
        }


        float angle;
        vector<Vec4i>::iterator it;
        for(it = lines.begin(); it != lines.end(); it++)
        {
                angle = abs( lineAngle( *it) );
                if(angle < 20)
                        lines.erase(it);
        }

        if(ept)
                p_lines = lines;
}

void laneDetect::updateLines(Mat gray, vector<Vec4i> &lines)
{
        Mat threshImg;
        /// Erode, dilate
        int an = 3;
        Mat element = getStructuringElement(MORPH_RECT, Size(an*2+1, an*2+1), Point(an, an) );
        dilate(gray, gray, element);

        sobelProcess(gray, sobelImg);

        threshold(sobelImg, threshImg, 88, 255, CV_THRESH_BINARY);
        HoughLinesP( threshImg, lines, 1, CV_PI/180, min_threshold + p_trackbar, 30, 10 );

        // adaptive change p_trackbar value
        int s = lines.size();
        if(s > 25 &&
           p_trackbar <= (max_trackbar - 10))
                p_trackbar += 10;
        else if(s < 6 && p_trackbar >= 10)
                p_trackbar -= 10;
}

void laneDetect::drawLanes(Mat& img, const vector<Vec4i> lines)
{
        for( size_t i = 0; i < lines.size(); i++ )
        {
                Vec4i l = lines[i];
                if(abs( lineAngle( lines[i]) ) > Horizontal)
                        line( img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        }
}
