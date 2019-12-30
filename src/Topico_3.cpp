#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat channels[3];
    Mat image = imread("../samples/baboon.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("baboon colored", CV_WINDOW_AUTOSIZE);

    split(image, channels);

    imshow("baboon colored", image);
    imshow("baboon red channel", channels[0]);
    imshow("baboon green channel", channels[1]);
    imshow("baboon blue channel", channels[2]);

    imwrite("../results/3_baboon_red_channel.jpg", channels[0]);
    imwrite("../results/3_baboon_green_channel.jpg", channels[1]);
    imwrite("../results/3_baboon_blue_channel.jpg", channels[2]);

    waitKey(0);
    return 0;
}

