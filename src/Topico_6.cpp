#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat grayImage, cannyFilter;
    Mat image = imread("../samples/lena.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("lena colored", CV_WINDOW_AUTOSIZE);

    cvtColor(image, grayImage, CV_RGB2GRAY);
    Canny(grayImage, cannyFilter, 75, 225, 3);

    imshow("lena colored", image);
    imshow("lena in gray scale", grayImage);
    imshow("lena with canny filter", cannyFilter);

    imwrite("../results/6_lena_colored.jpg", image);
    imwrite("../results/6_lena_gray_scale.jpg", grayImage);
    imwrite("../results/6_lena_canny_filter.jpg", cannyFilter);

    waitKey(0);
    return 0;
}

