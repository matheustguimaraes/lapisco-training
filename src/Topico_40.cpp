#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, grayImg, otsuThresholdImg, structuringElement;

    img = imread("/home/matheus/Dropbox/treinamento-pdi/samples/black_lightning.jpg");

    cvtColor(img, grayImg, CV_RGB2GRAY);

    GaussianBlur(grayImg, grayImg, Size(3, 3), 1);

    threshold(grayImg, otsuThresholdImg, 0, 255, THRESH_OTSU);

    structuringElement = getStructuringElement(MORPH_RECT, Size(3, 1), Point(-1, -1));

    imshow("Otsu's threshold image", otsuThresholdImg);

    for (int i = 0; i < 5; ++i) {
        erode(otsuThresholdImg, otsuThresholdImg, structuringElement, Point(-1, -1), i);
        imshow("eroded image with horizontal structuring element", otsuThresholdImg);
    }

    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/40_black_lightning_eroded_horizontal_element.jpg", otsuThresholdImg);

    waitKey(0);
    return 0;
}

