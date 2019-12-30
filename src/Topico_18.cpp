#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat getEqualizedImage(Mat img) {
    int minValue = 0;
    int maxValue = 0;

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            if ((maxValue == 0) && (minValue == 0)) {
                maxValue = img.at<uchar>(i, j);
                minValue = img.at<uchar>(i, j);
            }
            if (img.at<uchar>(i, j) > maxValue) {
                maxValue = img.at<uchar>(i, j);
            }
            if (img.at<uchar>(i, j) < minValue) {
                minValue = img.at<uchar>(i, j);
            }
        }
    }

    Mat_<Vec3b> equalizedHist(img.rows, img.cols, CV_8UC3);

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            equalizedHist(i, j)[0] = (255 * (img.at<uchar>(i, j) - minValue)) / (maxValue - minValue);
            equalizedHist(i, j)[1] = equalizedHist(i, j)[0];
            equalizedHist(i, j)[2] = equalizedHist(i, j)[0];
        }
    }

    return equalizedHist;
}

int main() {
    Mat img, grayImg, laplacianImg, absLaplacian, equalizedLaplacian;

    img = imread("../samples/lena.jpg");

    GaussianBlur(img, img, Size(3, 3), 0, 0, BORDER_DEFAULT);

    cvtColor(img, grayImg, CV_RGB2GRAY);

    Laplacian(grayImg, laplacianImg, CV_16S, 3, 1, 0, BORDER_DEFAULT);

    convertScaleAbs(laplacianImg, absLaplacian);

    equalizedLaplacian = getEqualizedImage(absLaplacian);

    imshow("Image with laplacian function", absLaplacian);
    imshow("Image with equalized laplacian", equalizedLaplacian);

    imwrite("../results/18_lena_laplacian.jpg", absLaplacian);
    imwrite("../results/18_lena_equalized_laplacian.jpg", equalizedLaplacian);

    waitKey(0);
    return 0;
}

