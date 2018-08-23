#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat grayImage, medianImage, meanImage;
    Mat image = imread("/home/matheus/Dropbox/treinamento-pdi/samples/baboon.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("baboon colored", CV_WINDOW_AUTOSIZE);

    cvtColor(image, grayImage, CV_RGB2GRAY);
    medianBlur(grayImage, medianImage, CV_MEDIAN);
    blur(grayImage, meanImage, Size(3, 3), Point(-1, -1));

    imshow("baboon colored", image);
    imshow("gray baboon", grayImage);
    imshow("baboon median filter", medianImage);
    imshow("baboon mean filter", meanImage);

    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/baboon.jpg", image);
    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/5_baboon_gray_scale.jpg", grayImage);
    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/5_baboon_median_filter.jpg", medianImage);
    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/5_baboon_mean_filter.jpg", meanImage);

    waitKey(0);
    return 0;
}

