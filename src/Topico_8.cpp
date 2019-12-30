#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat grayImage, resizeMinorImage, resizeMajorImage;
    Mat image = imread("../samples/baboon.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("baboon colored", CV_WINDOW_AUTOSIZE);

    cvtColor(image, grayImage, CV_RGB2GRAY);
    resize(grayImage, resizeMinorImage, Size(256, 256));
    resize(grayImage, resizeMajorImage, Size(1026, 1026));

    imshow("baboon colored", image);
    imshow("baboon in gray scale", grayImage);
    imshow("baboon resized to minor scale", resizeMinorImage);
    imshow("baboon resized to major scale", resizeMajorImage);

    imwrite("../results/baboon_colored.jpg", image);
    imwrite("../results/baboon_gray_scale.jpg", grayImage);
    imwrite("../results/8_baboon_minor_scale.jpg", resizeMinorImage);
    imwrite("../results/8_baboon_major_scale.jpg", resizeMajorImage);

    waitKey(0);
    return 0;
}

