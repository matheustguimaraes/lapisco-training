#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat grayImage;
    Mat image = imread("/home/matheus/Dropbox/treinamento-pdi/samples/baboon.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("baboon colored", CV_WINDOW_AUTOSIZE);

    cvtColor(image, grayImage, CV_RGB2GRAY);

    imshow("baboon colored", image);
    imshow("baboon gray scale", grayImage);
    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/2_baboon_gray_scale.jpg", grayImage);

    waitKey(0);
    return 0;
}

