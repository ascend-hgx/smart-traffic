 #include "../include/carCascadeDetect.h"

carCascadeDetect::carCascadeDetect() : minSize(30), maxSize(120)
{
        cout << "carCascadeDetect()" << endl;
        win = "cascade detect";
        cascadeName = "res/LBP_0.1FA_cascade.xml";

//        namedWindow(win);
        if( !csd.load( cascadeName ) ){ printf("--(!)Error loading cascade xml\n"); return ; };
}

carCascadeDetect::~carCascadeDetect()
{
        cout << "~carCascadeDetect()" << endl;
}


void carCascadeDetect::detectAndDisplay( Mat frame )
{
        std::vector<Rect> cars;
        Mat frame_gray;

        //图像预处理
        cvtColor( frame, frame_gray, CV_BGR2GRAY );

              //实验证明，目前这些预降噪处理都没有什么作用
//      equalizeHist( frame_gray, frame_gray );
//      Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
//      dilate(frame, frame, element, Point(-1, -1), 2);
//      erode(frame, frame, element, Point(-1, -1), 3);

//      imshow("gray", frame_gray);

        //--  多尺寸检测所有车辆
        csd.detectMultiScale( frame_gray, cars, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(minSize, minSize), Size(maxSize, maxSize) );

        //标示出车辆位置
        for( int i = 0; i < cars.size(); i++ )
        {
                Point center( cars[i].x + cars[i].width*0.5, cars[i].y + cars[i].height*0.5 );
                ellipse( frame, center, Size( cars[i].width*0.5, cars[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        }

        imshow(win, frame);     //显示出含有车辆标示的图片
}

void carCascadeDetect::detectGrayImgAndDisplay(Mat gray)
{
        std::vector<Rect> cars;

        //--  多尺寸检测所有车辆
        csd.detectMultiScale( gray, cars, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(minSize, minSize), Size(maxSize, maxSize) );

        //标示出车辆位置
        for( int i = 0; i < cars.size(); i++ )
        {
                Point center( cars[i].x + cars[i].width*0.5, cars[i].y + cars[i].height*0.5 );
                ellipse( gray, center, Size( cars[i].width*0.5, cars[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        }

        imshow(win, gray);     //显示出含有车辆标示的图片
}

void carCascadeDetect::drawCars(Mat& frame, std::vector<Rect> cars)
{
        //标示出车辆位置
        for( int i = 0; i < cars.size(); i++ )
        {
                Point center( cars[i].x + cars[i].width*0.5, cars[i].y + cars[i].height*0.5 );
                ellipse( frame, center, Size( cars[i].width*0.5, cars[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        }
}

vector<Rect> carCascadeDetect::detectGrayImgAndReturnRect(Mat gray)
{
        std::vector<Rect> cars;
        //--  多尺寸检测所有车辆
        csd.detectMultiScale( gray, cars, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(minSize, minSize), Size(maxSize, maxSize) );
        return cars;
}
