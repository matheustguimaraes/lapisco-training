#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, grayImage, adaptiveThresholdImg;
    vector<vector<Point> > contours;

    img = imread("../samples/lena.jpg");

    cvtColor(img, grayImage, CV_RGB2GRAY);

    GaussianBlur(grayImage, grayImage, Size(3, 3), 1);
    adaptiveThreshold(grayImage, adaptiveThresholdImg, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 13, 5);

    imshow("original image", img);
    imshow("thresholded image", adaptiveThresholdImg);

    imwrite("../results/28_lena_adaptive_threshold.jpg", adaptiveThresholdImg);

    waitKey(0);
    return 0;
}

