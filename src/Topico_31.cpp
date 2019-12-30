#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat getRectContoursImage(Mat img) {
    Mat grayImage;
    vector<vector<Point> > contours;
    RNG rng(12345);

    cvtColor(img, grayImage, CV_RGB2GRAY);

    blur(grayImage, grayImage, Size(3, 3));

    Canny(grayImage, grayImage, 125, 255, 3);

    findContours(grayImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    printf("contours numbers: %lu \n", contours.size());

    vector<vector<Point>> contoursPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> center(contours.size());
    vector<float> radius(contours.size());

    for (int i = 0; i < contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), contoursPoly[i], 3, true);
        boundRect[i] = boundingRect(Mat(contoursPoly[i]));
        minEnclosingCircle((Mat) contoursPoly[i], center[i], radius[i]);
    }

    Mat drawingContours = Mat::zeros(grayImage.size(), CV_8UC3);

    for (int i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawingContours, contoursPoly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        rectangle(drawingContours, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
    }

    return drawingContours;
}

int main() {
    Mat img, drawingImage;

    img = imread("../samples/paint.jpg");

    drawingImage = getRectContoursImage(img);

    imshow("original image", img);
    imshow("image with contours", drawingImage);

    imwrite("../results/31_paint_cvContourBoundingRect.jpg", drawingImage);

    waitKey(0);
    return 0;
}

