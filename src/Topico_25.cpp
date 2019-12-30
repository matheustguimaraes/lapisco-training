#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int channelSelection(int channel, int count) {
    if (count == 0) {
        channel = 2;
        return channel;
    }
    if (count == 1) {
        channel = 0;
        return channel;
    }
    if (count == 2) {
        channel = 1;
        return channel;
    }
    return 0;
}

void setMouse(int e, int x, int y, int d, void *ptr) {
    Point *p = (Point *) ptr;
    p->x = x;
    p->y = y;
}

Mat getMouseRegionGrowing(Mat image, Mat_<Vec3b> regionGrowing) {
    int m, n;
    Point p;
    int channel = 0;
    int count = 0;
    int current = 0;
    int previous = 0;
    while (count < 3) {
        channel = channelSelection(channel, count);
        count++;

        imshow("Apply seed", image);

        setMouseCallback("Apply seed", setMouse, &p);

        waitKey(0);

        m = p.x;
        n = p.y;

        regionGrowing(m, n)[channel] = 255;

        do {
            previous = current;
            current = 0;
            for (int i = 0; i < regionGrowing.rows; i++) {
                for (int j = 0; j < regionGrowing.cols; j++) {
                    if (regionGrowing(i, j)[channel] == 255) {
                        for (int x = i - 1; x < i + 2; x++) {
                            for (int y = j - 1; y < j + 2; y++) {
                                if (image.at<uchar>(x, y) < 127) {
                                    regionGrowing(x, y)[channel] = 255;
                                    current++;
                                }
                            }
                        }
                    }
                }
            }
        } while (current != previous);
    }
    return regionGrowing;
}

Mat getRegionGrowing(Mat image) {
    Mat_<Vec3b> regionGrowing(image.rows, image.cols, CV_8UC3);

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            regionGrowing(i, j)[0] = 0;
            regionGrowing(i, j)[1] = 0;
            regionGrowing(i, j)[2] = 0;
        }
    }

    regionGrowing = getMouseRegionGrowing(image, regionGrowing);

    return regionGrowing;
}

int main() {
    Mat img, grayImage;
    img = imread("../samples/objects.png");

    cvtColor(img, grayImage, CV_RGB2GRAY);

    grayImage = getRegionGrowing(grayImage);

    imshow("region growing", grayImage);

    imwrite("../results/25_objects_three_rgb_region_growing.jpg", grayImage);

    waitKey(0);
    return 0;
}

