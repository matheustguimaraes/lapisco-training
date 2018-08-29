#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat getRegionGrowing(Mat image, Mat regionGrowing) {
    int current = 0;
    int previous = 0;
    do {
        previous = current;
        current = 0;
        for (int i = 0; i < regionGrowing.rows; i++) {
            for (int j = 0; j < regionGrowing.cols; j++) {
                if (regionGrowing.at<uchar>(i, j) == 255) {
                    for (int x = i - 1; x < i + 2; x++) {
                        for (int y = j - 1; y < j + 2; y++) {
                            if (image.at<uchar>(x, y) < 127) {
                                regionGrowing.at<uchar>(x, y) = 255;
                                current++;
                            }
                        }
                    }
                }
            }
        }
    } while (current != previous);

    return regionGrowing;
}

Mat getBlueCentroid(Mat image) {
    Mat_<Vec3b> centroid(image.rows, image.cols, CV_8UC3);
    int xCumulative = 0;
    int yCumulative = 0;
    int pixelNumbers = 0;

    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            if (image.at<uchar>(x, y) == 255) {
                centroid.at<Vec3b>(x, y)[0] = 255;
                centroid.at<Vec3b>(x, y)[1] = 0;
                centroid.at<Vec3b>(x, y)[2] = 0;

                xCumulative += x;
                yCumulative += y;
                pixelNumbers++;
            } else {
                centroid.at<Vec3b>(x, y)[0] = 255;
                centroid.at<Vec3b>(x, y)[1] = 255;
                centroid.at<Vec3b>(x, y)[2] = 255;
            }
        }
    }

    xCumulative /= pixelNumbers;
    yCumulative /= pixelNumbers;

    circle(centroid, Point(yCumulative, xCumulative), 2, CV_RGB(0, 255, 0), 5, 5, 0);

    return centroid;
}

void setMouse(int e, int x, int y, int d, void *ptr) {
    Point *p = (Point *) ptr;
    p->x = x;
    p->y = y;
}

Mat getMouseRegionGrowing(Mat image) {
    Mat regionGrowing(image.rows, image.cols, CV_8UC3);
    int m, n;
    Point p;

    cvtColor(regionGrowing, regionGrowing, CV_RGB2GRAY);

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            regionGrowing.at<uchar>(i, j) = 0;
        }
    }

    imshow("Apply seed", image);

    setMouseCallback("Apply seed", setMouse, &p);

    waitKey(0);

    m = p.x;
    n = p.y;

    regionGrowing.at<uchar>(m, n) = 255;

    regionGrowing = getRegionGrowing(image, regionGrowing);

    return regionGrowing;
}

int main() {
    Mat img, grayImage, mouseRegionGrowing, centroid;

    img = imread("/home/matheus/Dropbox/treinamento-pdi/samples/black_circle.jpg");

    cvtColor(img, grayImage, CV_RGB2GRAY);

    mouseRegionGrowing = getMouseRegionGrowing(grayImage);

    centroid = getBlueCentroid(mouseRegionGrowing);

    imshow("black circle", grayImage);
    imshow("region growing", mouseRegionGrowing);
    imshow("region growing with green centroid", centroid);

    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/22_green_centroid.jpg", centroid);

    waitKey(0);
    return 0;
}

