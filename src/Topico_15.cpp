#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat frame, grayFrame, cannyFilter;
    VideoCapture cap(0);
    namedWindow("Camera", CV_WINDOW_AUTOSIZE);

    while (1) {
        cap >> frame;
        cvtColor(frame, grayFrame, CV_RGB2GRAY);
        Canny(grayFrame, cannyFilter, 75, 225, 3);
        imshow("Camera", cannyFilter);
        if (waitKey(27) >= 0) break;
    }
    return 0;
}

