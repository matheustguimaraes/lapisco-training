#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, grayImage, imageWithContours;
    vector<vector<Point> > contours;

    img = imread("../samples/paint.jpg");

    cvtColor(img, grayImage, CV_RGB2GRAY);

    blur(grayImage, grayImage, Size(3, 3));

    Canny(grayImage, imageWithContours, 125, 255, 3);

    findContours(imageWithContours, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    imshow("image with Hough transform", imageWithContours);

    printf("contours numbers: %lu \n",contours.size());

    imwrite("../results/30_paint_findContours.jpg", imageWithContours);

    waitKey(0);
    return 0;
}

