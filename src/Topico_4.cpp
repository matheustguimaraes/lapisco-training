#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat channels[3], hsvImage;
    Mat image = imread("../samples/baboon.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("baboon colored", CV_WINDOW_AUTOSIZE);

    cvtColor(image, hsvImage, CV_RGB2HSV);
    split(hsvImage, channels);

    imshow("baboon colored", image);
    imshow("hsv baboon", hsvImage);
    imshow("hsv baboon hue", channels[0]);
    imshow("hsv baboon saturation", channels[1]);
    imshow("hsv baboon value", channels[2]);

    imwrite("../results/4_hsv_baboon.jpg", hsvImage);
    imwrite("../results/4_hsv_baboon_hue.jpg", channels[0]);
    imwrite("../results/4_hsv_baboon_saturation.jpg", channels[1]);
    imwrite("../results/4_hsv_baboon_value.jpg", channels[2]);

    waitKey(0);
    return 0;
}

