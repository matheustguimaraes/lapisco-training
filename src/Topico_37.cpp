#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, grayImg, otsuThresholdImg, structuringElement;

    img = imread("../samples/black_lightning.jpg");

    cvtColor(img, grayImg, CV_RGB2GRAY);

    GaussianBlur(grayImg, grayImg, Size(3, 3), 1);

    threshold(grayImg, otsuThresholdImg, 0, 255, THRESH_OTSU);

    structuringElement = getStructuringElement(MORPH_RECT, Size(1, 3), Point(-1, -1));

    imshow("Otsu's threshold image", otsuThresholdImg);

    for (int i = 0; i < 5; ++i) {
        dilate(otsuThresholdImg, otsuThresholdImg, structuringElement, Point(-1, -1), i);        
        imshow("dilated image with vertical structuring element", otsuThresholdImg);
    }

    imwrite("../results/37_black_lightning_dilated_vertical_element.jpg", otsuThresholdImg);

    waitKey(0);
    return 0;
}

