#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <highgui.h>

using namespace cv;
using namespace std;

void writeTxt(Mat grayImage) {
    FILE *txtDocument = fopen("../results/9_image.txt", "w");
    for (int i = 0; i < grayImage.rows; ++i) {
        for (int j = 0; j < grayImage.cols; ++j) {
            fprintf(txtDocument, "%d ", grayImage.at<uchar>(i, j));
        }
        fprintf(txtDocument, "\n");
    }
    fclose(txtDocument);
}

int main() {
    Mat grayImage;
    Mat image = imread("../samples/baboon.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("baboon colored", CV_WINDOW_AUTOSIZE);

    cvtColor(image, grayImage, CV_RGB2GRAY);
    writeTxt(grayImage);

    imshow("baboon colored", image);

    waitKey(0);
    return 0;
}

