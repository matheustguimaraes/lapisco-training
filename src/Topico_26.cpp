#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void setChannelColor(int *channels) {
    channels[0] = rand() % 256;
    channels[1] += 40 + channels[0];
    channels[2] += 50 + channels[1];

    while (channels[0] > 255 || channels[1] > 255 || channels[2] > 255) {
        channels[0] = rand() % 256;
        channels[1] += channels[0];
        channels[2] += channels[1];
    }
}

Mat getAutoRegionGrowing(Mat grayImage, Mat_<uchar> sampleImage, Mat_<Vec3b> regionGrowing) {
    int channels[3];
    int previous, current;

    for (int k = 0; k < grayImage.rows; k++) {
        for (int l = 0; l < grayImage.cols; l++) {
            if (grayImage.at<uchar>(k, l) == 0 && sampleImage.at<uchar>(k, l) == 0) {
                sampleImage.at<uchar>(k, l) = 255;
                setChannelColor(channels);
                previous = 1;
                current = 0;
                while (current != previous) {
                    previous = current;
                    current = 0;
                    for (int x = 0; x < grayImage.rows; x++) {
                        for (int y = 0; y < grayImage.cols; y++) {
                            if (sampleImage.at<uchar>(x, y) == 255) {
                                for (int i = x - 1; i < x + 2; i++) {
                                    for (int j = y - 1; j < y + 2; j++) {
                                        if (grayImage.at<uchar>(i, j) < 127 && sampleImage.at<uchar>(i, j) != 255) {
                                            regionGrowing(i, j)[0] = channels[0];
                                            regionGrowing(i, j)[1] = channels[1];
                                            regionGrowing(i, j)[2] = channels[2];
                                            sampleImage.at<uchar>(i, j) = 255;
                                            current++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return regionGrowing;
}

Mat getRegionGrowing(Mat grayImage) {
    Mat_<uchar> sampleImage(grayImage.rows, grayImage.cols, CV_8UC1);
    Mat_<Vec3b> regionGrowing(grayImage.rows, grayImage.cols, CV_8UC1);

    for (int i = 0; i < grayImage.rows; ++i) {
        for (int j = 0; j < grayImage.cols; ++j) {
            sampleImage.at<uchar>(i, j) = 0;
            regionGrowing(i, j)[0] = 0;
            regionGrowing(i, j)[1] = 0;
            regionGrowing(i, j)[2] = 0;
        }
    }

    regionGrowing = getAutoRegionGrowing(grayImage, sampleImage, regionGrowing);

    return regionGrowing;
}

int main() {
    Mat img, grayImage, regionGrowing;

    img = imread("/home/matheus/Dropbox/treinamento-pdi/samples/paint.jpg");

    cvtColor(img, grayImage, CV_RGB2GRAY);

    regionGrowing = getRegionGrowing(grayImage);

    imshow("auto region growing", regionGrowing);

    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/26_paint_auto_region_growing.jpg", regionGrowing);

    waitKey(0);
    return 0;
}

