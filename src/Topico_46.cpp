#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void setFileLoop(double statistics[]) {
    FILE *file;
    file = fopen("/home/matheus/Dropbox/treinamento-pdi/results/46_statistic_moments.txt", "w");
    for (int i = 0; i < 10; ++i) {
        fprintf(file, "statistic moment %2.d = %20.20lf\n", i + 1, statistics[i]);
    }
    fclose(file);
}

void getFileStatistics() {
    Mat img, grayImage, thresholdImg;
    Moments vecMoments;
    vector<vector<Point>> contours;
    double statistics[10] = {0};

    img = imread("/home/matheus/Dropbox/treinamento-pdi/samples/black_box.jpg", CV_LOAD_IMAGE_COLOR);

    cvtColor(img, grayImage, CV_RGB2GRAY);

    threshold(grayImage, thresholdImg, 127, 255, CV_THRESH_BINARY);

    findContours(thresholdImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (vector<vector<Point>>::const_iterator itr = contours.begin(); itr != contours.end(); itr++) {
        vecMoments = moments(Mat(*itr));
        statistics[0] = vecMoments.m00;
        statistics[1] = vecMoments.m01;
        statistics[2] = vecMoments.m02;
        statistics[3] = vecMoments.m03;
        statistics[4] = vecMoments.m10;
        statistics[5] = vecMoments.m11;
        statistics[6] = vecMoments.m12;
        statistics[7] = vecMoments.m20;
        statistics[8] = vecMoments.m21;
        statistics[9] = vecMoments.m30;
    }
    setFileLoop(statistics);
}

int main() {
    getFileStatistics();

    waitKey(0);
    return 0;
}

