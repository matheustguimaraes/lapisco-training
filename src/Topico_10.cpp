#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void writeTxtThresholdFiltering(Mat image) {
    FILE *txtDocument = fopen("/home/matheus/Dropbox/treinamento-pdi/results/10_image.txt", "w");
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            image.at<uchar>(i, j) > 120 ? image.at<uchar>(i, j) = 220 : image.at<uchar>(i, j) = 0;
            fprintf(txtDocument, "%d ", image.at<uchar>(i, j));
        }
        fprintf(txtDocument, "\n");
    }
    fclose(txtDocument);
}

int main() {
    Mat grayImage, thresholdFilter;
    Mat image = imread("/home/matheus/Dropbox/treinamento-pdi/samples/tiger.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("baboon colored", CV_WINDOW_AUTOSIZE);

    cvtColor(image, grayImage, CV_RGB2GRAY);

    imshow("tiger in gray scale", grayImage);

    threshold(grayImage, thresholdFilter, 120, 220, CV_THRESH_BINARY);
    writeTxtThresholdFiltering(thresholdFilter);

    imshow("tiger colored", image);
    imshow("tiger in threshold filtering", thresholdFilter);

    waitKey(0);
    return 0;
}

