#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat getHistogram(Mat img) {
    int aux, normalization;
    int bins[256] = {0};
    int maxValue = 0;
    int minValue = 0;

    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            aux = img.at<uchar>(y, x);
            bins[aux]++;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (maxValue < bins[i]) {
            maxValue = bins[i];
        } else if (minValue > bins[i]) {
            minValue = bins[i];
        }
    }

    normalization = maxValue / 200;

    for (int x = 0; x < 256; x++) {
        bins[x] /= normalization;
    }

    Mat_<Vec3b> hist(256, 256, CV_8UC3);

    for (int i = 0; i < hist.rows; i++) {
        for (int j = 0; j < hist.cols; j++) {
            if (i >= hist.rows - bins[j]) {
                hist(i, j)[0] = 0;
                hist(i, j)[1] = 0;
                hist(i, j)[2] = 0;
            } else {
                hist(i, j)[0] = 255;
                hist(i, j)[1] = 255;
                hist(i, j)[2] = 255;
            }
        }
    }
    return hist;
}

int main() {
    Mat img, grayImage, equalizedImage, grayHist, equalizedHist;

    img = imread("../samples/lena.jpg");
    imshow("Gray Image", grayImage);

    cvtColor(img, grayImage, CV_RGB2GRAY);

    equalizeHist(grayImage, equalizedImage);

    grayHist = getHistogram(grayImage);
    equalizedHist = getHistogram(equalizedImage);

    imshow("Gray Image", grayImage);
    imshow("Equalized Image", equalizedImage);
    imshow("Gray Histogram", grayHist);
    imshow("Equalized Histogram", equalizedHist);

    imwrite("../results/16_lena_equalized.jpg", equalizedImage);
    imwrite("../results/16_lena_gray_histogram.jpg", grayHist);
    imwrite("../results/16_lena_equalized_histogram.jpg", equalizedHist);

    waitKey(0);
    return 0;
}
