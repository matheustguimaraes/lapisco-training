#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat grayImage, thresholdFilter;
    Mat image = imread("../samples/tiger.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("tiger colored", CV_WINDOW_AUTOSIZE);

    cvtColor(image, grayImage, CV_RGB2GRAY);
    threshold(grayImage, thresholdFilter, 120, 220, CV_THRESH_BINARY);

    imshow("tiger colored", image);
    imshow("tiger in gray scale", grayImage);
    imshow("tiger with threshold filtering", thresholdFilter);

    imwrite("../results/tiger_colored.jpg", image);
    imwrite("../results/tiger_gray_scale.jpg", grayImage);
    imwrite("../results/7_tiger_threshold_filtering.jpg", thresholdFilter);

    waitKey(0);
    return 0;
}

