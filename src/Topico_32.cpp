#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat getRectContoursImage(Mat img) {
    Mat grayImage;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345);

    cvtColor(img, grayImage, CV_RGB2GRAY);

    blur(grayImage, grayImage, Size(3, 3));

    Canny(grayImage, grayImage, 125, 255, 3);

    findContours(grayImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    printf("contours numbers: %lu \n", contours.size());

    Mat drawingContours = Mat::zeros(grayImage.size(), CV_8UC3);
    vector<Moments> vecMoments(contours.size());
    vector<Point2f> massCenters(contours.size());

    for (int i = 0; i < contours.size(); i++) {
        vecMoments[i] = moments(contours[i], false);
    }

    for (int i = 0; i < contours.size(); i++) {
        massCenters[i] = Point2f(vecMoments[i].m10 / vecMoments[i].m00, vecMoments[i].m01 / vecMoments[i].m00);
    }

    for (int i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawingContours, contours, i, color, 2, 8, hierarchy, 0, Point());
        circle(drawingContours, massCenters[i], 4, color, -1, 8, 0);
    }

    for (int i = 0; i < contours.size(); i++) {
        printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, vecMoments[i].m00,
               contourArea(contours[i]), arcLength(contours[i], true));
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawingContours, contours, i, color, 2, 8, hierarchy, 0, Point());
        circle(drawingContours, massCenters[i], 4, color, -1, 8, 0);
    }

    return drawingContours;
}

int main() {
    Mat img, drawingImage;

    img = imread("/home/matheus/Dropbox/treinamento-pdi/samples/paint.jpg");

    drawingImage = getRectContoursImage(img);

    imshow("original image", img);
    imshow("image with contours", drawingImage);

    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/32_paint_cvContourArea.jpg", drawingImage);

    waitKey(0);
    return 0;
}

