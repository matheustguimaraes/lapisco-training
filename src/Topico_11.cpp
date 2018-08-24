#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void setDotInCenter(Mat grayImage, Mat_<Vec3b> imageWithCenterDot) {
    for (int i = 0; i < grayImage.rows; ++i) {
        for (int j = 0; j < grayImage.cols; ++j) {
            if ((i == grayImage.rows / 2) && (j == grayImage.cols / 2)) {
                imageWithCenterDot(i, j)[0] = 255;
                imageWithCenterDot(i, j)[1] = 255;
                imageWithCenterDot(i, j)[2] = 255;
            } else {
                imageWithCenterDot(i, j)[0] = grayImage.at<uchar>(i, j);
                imageWithCenterDot(i, j)[1] = grayImage.at<uchar>(i, j);
                imageWithCenterDot(i, j)[2] = grayImage.at<uchar>(i, j);
            }
        }
    }
}

int main() {
    Mat grayImage;
    Mat image = imread("/home/matheus/Dropbox/treinamento-pdi/samples/black_box.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("black_box", CV_WINDOW_AUTOSIZE);

    cvtColor(image, grayImage, CV_RGB2GRAY);
    Mat_<Vec3b> imageWithCenterDot(grayImage.rows, grayImage.cols, CV_8UC3);
    setDotInCenter(grayImage, imageWithCenterDot);

    imshow("black_box", image);
    imshow("black_box in gray scale", grayImage);
    imshow("black_box with white center", imageWithCenterDot);

    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/12_black_box_with_center_dot.jpg", imageWithCenterDot);

    waitKey(0);
    return 0;
}

