#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void setChannelColor(int *channels) {
    channels[0] = rand() % 256;
    channels[1] += 50 + channels[0];
    channels[2] += 30 + channels[1];

    while (channels[0] > 255 || channels[1] > 255 || channels[2] > 255) {
        channels[0] = rand() % 256;
        channels[1] += channels[0];
        channels[2] += channels[1];
    }
}

void getAutoRegionGrowing(Mat grayImage) {
    char nameUnitRegionGrowing[100];
    int minValueX, maxValueX, minValueY, maxValueY;
    int channels[3];
    int previous, current;
    Mat_<uchar> sampleImage(grayImage.rows, grayImage.cols, 1);
    Mat_<Vec3b> regionGrowing(grayImage.rows, grayImage.cols, 1);
    int count = 0;

    for (int x = 0; x < grayImage.rows; x++) {
        for (int y = 0; y < grayImage.cols; y++) {
            sampleImage.at<uchar>(x, y) = 0;
        }
    }

    for (int k = 0; k < grayImage.rows; k++) {
        for (int l = 0; l < grayImage.cols; l++) {
            if (grayImage.at<uchar>(k, l) == 0 && sampleImage.at<uchar>(k, l) == 0) {
                sampleImage.at<uchar>(k, l) = 255;

                maxValueX = k;
                minValueX = k;
                maxValueY = l;
                minValueY = l;

                setChannelColor(channels);

                count++;
                previous = 1;
                current = 0;
                while (previous != current) {
                    previous = current;
                    for (int x = 0; x < sampleImage.rows; x++) {
                        for (int y = 0; y < sampleImage.cols; y++) {
                            if (sampleImage.at<uchar>(x, y) == 255) {
                                for (int i = x - 1; i < x + 2; i++) {
                                    for (int j = y - 1; j < y + 2; j++) {
                                        if (grayImage.at<uchar>(i, j) < 127 && sampleImage.at<uchar>(i, j) != 255) {
                                            regionGrowing(i, j)[0] = channels[0];
                                            regionGrowing(i, j)[1] = channels[1];
                                            regionGrowing(i, j)[2] = channels[2];

                                            sampleImage.at<uchar>(i, j) = 255;

                                            if (i > maxValueX) { maxValueX = i; }
                                            if (i < minValueX) { minValueX = i; }
                                            if (j > maxValueY) { maxValueY = j; }
                                            if (j < minValueY) { minValueY = j; }

                                            current++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    imshow("region growing", regionGrowing);
                }
                sprintf(nameUnitRegionGrowing, "region %d", count);
                Rect region = Rect(minValueY, minValueX, maxValueY - minValueY, maxValueX - minValueX);
                Mat unitRegionGrowing = regionGrowing(region);

                imshow(nameUnitRegionGrowing, unitRegionGrowing);

                imwrite("../results/27_colored_images_auto_region_growing.jpg",
                        unitRegionGrowing);
            }
        }
    }
}

int main() {
    Mat img, gray;

    img = imread("../samples/paint.jpg");

    cvtColor(img, gray, CV_RGB2GRAY);

    imshow("original image", gray);

    getAutoRegionGrowing(gray);

    waitKey(0);
    return 0;
}

