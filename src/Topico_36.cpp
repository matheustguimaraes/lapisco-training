#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, grayImg, otsuThresholdImg, erodedImg;

    img = imread("/home/matheus/Dropbox/treinamento-pdi/samples/tiger.jpg");

    cvtColor(img, grayImg, CV_RGB2GRAY);

    GaussianBlur(grayImg, grayImg, Size(3, 3), 1);

    threshold(grayImg, otsuThresholdImg, 0, 255, THRESH_OTSU);

    erode(otsuThresholdImg, erodedImg, Mat(), Point(-1, -1), 2, BORDER_CONSTANT, morphologyDefaultBorderValue());

    imshow("original image", img);
    imshow("Otsu's threshold image", otsuThresholdImg);
    imshow("eroded image", erodedImg);

    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/36_tiger_eroded_otsu_thresholding.jpg", erodedImg);

    waitKey(0);
    return 0;
}

