#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void setFileLoop(double statistics[]) {
    FILE *file;
    file = fopen("/home/matheus/Dropbox/treinamento-pdi/results/47_central_moments.txt", "w");
    for (int i = 0; i < 7; ++i) {
        fprintf(file, "central moment %2.d = %20.20lf\n", i + 1, statistics[i]);
    }
    fclose(file);
}

void getFileStatistics() {
    Mat img, grayImage, thresholdImg;
    Moments vecMoments;
    vector<vector<Point>> contours;
    double central[7] = {0};

    img = imread("/home/matheus/Dropbox/treinamento-pdi/samples/black_box.jpg", CV_LOAD_IMAGE_COLOR);

    cvtColor(img, grayImage, CV_RGB2GRAY);

    threshold(grayImage, thresholdImg, 127, 255, CV_THRESH_BINARY);

    findContours(thresholdImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (vector<vector<Point>>::const_iterator itr = contours.begin(); itr != contours.end(); itr++) {
        vecMoments = moments(Mat(*itr));
        central[0] = vecMoments.mu20;
        central[1] = vecMoments.mu11;
        central[2] = vecMoments.mu02;
        central[3] = vecMoments.mu30;
        central[4] = vecMoments.mu21;
        central[5] = vecMoments.mu12;
        central[6] = vecMoments.mu03;
    }
    setFileLoop(central);
}

int main() {
    getFileStatistics();

    waitKey(0);
    return 0;
}

