#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "include/carCascadeDetect.h"
#include "include/laneDetect.h"
#include "include/featuresToTrack.h"

using namespace std;
using namespace cv;

string win = "car project";
Mat frame;
Mat gray;
char key;
carCascadeDetect csd;
laneDetect lane;
featuresToTrack track;
std::vector<Rect> cars;
vector<Vec4i> lines;

bool addPt(false);
Point2f point;
static void onMouse(int event, int x, int y, int /*flags*/, void* /*param*/)
{
        if (event == CV_EVENT_LBUTTONDOWN)
        {
                point = Point2f((float)x, (float)y);
                addPt = true;
        }
}

void getAction(char k);
void trackCurrentCars();

int main(int argc, char *argv[])
{
        namedWindow(win);
        setMouseCallback(win, onMouse, 0);

        VideoCapture cap("res/car.mp4");    //读取视频
        if( !cap.isOpened()){
                cout << "video open error" <<endl;
                return -1;
        }

        while(1)
        {
                cap >> frame;
                cvtColor( frame, gray, CV_BGR2GRAY );

                if(addPt)
                {
                        addPt = false;
                        track.addTrackPoints( point);
                }

                cars = csd.detectGrayImgAndReturnRect(gray);
                lane.updateLines(gray, lines);
                track.updateTrackPoints(gray);

                csd.drawCars(frame, cars);
                lane.drawLanes(frame, lines);
                track.drawTrackPoints(frame);

                imshow(win, frame);
                key = (char)waitKey(10);
                if(key == 'q')
                {
                        cout << "quit..." <<endl;
                        break;
                }
                getAction(key);
        }

        cap.release();
        destroyAllWindows();
        return 0;
}

void getAction(char k)
{
        switch(k)
        {
                case 'c': track.clearAllTrackPoints(); break;
                case 'a': trackCurrentCars();            break;
        }
}

void trackCurrentCars()
{
                for(int i = 0; i < cars.size(); i++)
                {
                        Point center( cars[i].x + cars[i].width*0.5, cars[i].y + cars[i].height*0.5 );
                        track.addTrackPoints( center);
                }
}
