#include "../include/featuresToTrack.h"

featuresToTrack::featuresToTrack() : MAX_COUNT(500), Min_Y(55)
{
        cout << "featuresToTrack()" << endl;
        termcrit = TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
        winSize = cvSize(31, 31);
}

featuresToTrack::~featuresToTrack()
{
        cout << "~featuresToTrack()" << endl;
}

void featuresToTrack::updateTrackPoints(Mat grayImg)
{
        grayImg.copyTo(gray);

        if(!points[0].empty())
        {
                vector<uchar> status;
                vector<float> err;
                if (prevGray.empty())
                        gray.copyTo(prevGray);
                calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize, 3, termcrit, 0, 0.001);
                size_t i, k;
                for (i = k = 0; i <points[1].size(); i++)
                {
                        if (!status[i])
                                continue;

                        if(points[1][i].y < Min_Y)
                                continue;

                        points[1][k++] = points[1][i];
                }

                points[1].resize(k);
        }

        points[0] = points[1];
        cv::swap(prevGray, gray);

        cout << "Point : " << endl;
        for(int i = 0; i < points[1].size(); i++)
                cout << points[1].at(i) << " " << endl;
}

void featuresToTrack::drawTrackPoints(Mat img)
{
        size_t i;
        for (i = 0; i <points[1].size(); i++)
        {
                circle(img, points[1][i], 5, Scalar(0, 255, 0), -1, 8);
        }
}

void featuresToTrack::addTrackPoints(Point2f point)
{
        for(int i =0;  i < points[1].size(); i++)
        {
                if (norm(point - points[1][i]) <= 5)
                {
                        cout << "bad point" << endl;
                        return ;
                }
        }

        if (points[1].size() < (size_t)MAX_COUNT)
        {
                vector<Point2f> tmp;
                tmp.push_back(point);
                cornerSubPix(gray, tmp, winSize, cvSize(-1, -1), termcrit);
                points[1].push_back(tmp[0]);
        }
}

