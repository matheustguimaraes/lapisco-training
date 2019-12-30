#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void setFileLoop(double hu[]) {
    FILE *file;
    file = fopen("../results/48_hu_moments.txt", "w");
    for (int i = 0; i < 7; ++i) {
        fprintf(file, "hu moment %2.d = %20.20lf\n", i + 1, hu[i]);
    }
    fclose(file);
}

void getFileStatistics() {
    Mat img, grayImage, thresholdImg;
    Moments vecMoments;
    vector<vector<Point>> contours;
    double hu[7] = {0};

    img = imread("../samples/black_box.jpg", CV_LOAD_IMAGE_COLOR);

    cvtColor(img, grayImage, CV_RGB2GRAY);

    threshold(grayImage, thresholdImg, 127, 255, CV_THRESH_BINARY);

    findContours(thresholdImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (vector<vector<Point>>::const_iterator itr = contours.begin(); itr != contours.end(); itr++) {
        vecMoments = moments(Mat(*itr));
        HuMoments(vecMoments, hu);
        hu[0] = vecMoments.nu02;
        hu[1] = vecMoments.nu03;
        hu[2] = vecMoments.nu11;
        hu[3] = vecMoments.nu12;
        hu[4] = vecMoments.nu20;
        hu[5] = vecMoments.nu21;
        hu[6] = vecMoments.nu30;
    }
    setFileLoop(hu);
}

int main() {
    getFileStatistics();

    waitKey(0);
    return 0;
}

