#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat grayImage, gradX, gradY, absGradX, absGradY, sobelFilter;
    Mat image = imread("../samples/lena.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("lena colored", CV_WINDOW_AUTOSIZE);

    GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT);

    cvtColor(image, grayImage, CV_RGB2GRAY);

    Sobel(grayImage, gradX, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    Sobel(grayImage, gradY, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);

    convertScaleAbs(gradX, absGradX, 1, 0);
    convertScaleAbs(gradY, absGradY, 1, 0);

    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, sobelFilter);

    imshow("lena colored", image);
    imshow("lena in gray scale", grayImage);
    imshow("lena with Sobel filter", sobelFilter);

    imwrite("../results/13_lena_sobel_filter.jpg", sobelFilter);

    waitKey(0);
    return 0;
}

