#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat frame, grayFrame;
    VideoCapture cap(0);
    namedWindow("Camera", CV_WINDOW_AUTOSIZE);

    while (1) {
        cap >> frame;
        cvtColor(frame, grayFrame, CV_RGB2GRAY);       
        imshow("Camera", grayFrame);
        if (waitKey(27) >= 0) break;
    }
    return 0;
}

