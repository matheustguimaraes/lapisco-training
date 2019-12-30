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
    Mat img, grayImg, gradX, gradY, absGradX, absGradY, sobelFilter, histImg, histSobelFilter;

    img = imread("../samples/lena.jpg");

    GaussianBlur(img, img, Size(3, 3), 0, 0, BORDER_DEFAULT);

    cvtColor(img, grayImg, CV_RGB2GRAY);

    Sobel(grayImg, gradX, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    Sobel(grayImg, gradY, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);

    convertScaleAbs(gradX, absGradX);
    convertScaleAbs(gradY, absGradY);

    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, sobelFilter);

    histImg = getHistogram(img);
    histSobelFilter = getHistogram(sobelFilter);

    imshow("Gray image", grayImg);
    imshow("Sobel filter", sobelFilter);
    imshow("Histogram of the image", histImg);
    imshow("Histogram of the Sobel filter", histSobelFilter);

    imwrite("../results/19_lena_histogram.jpg", histImg);
    imwrite("../results/19_lena_histogram_sobel_filter.jpg", histSobelFilter);

    waitKey(0);
    return 0;
}

