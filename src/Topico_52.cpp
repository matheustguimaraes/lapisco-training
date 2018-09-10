#include <stdio.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat keyPoint1, keyPoint2, img1, img2, descriptorImg1, descriptorImg2, result;
    vector<KeyPoint> vecKeyPoint1, vecKeyPoint2;
    SurfDescriptorExtractor detectorSURF(100);
    SurfDescriptorExtractor extractor;
    BFMatcher matcher(NORM_L2);
    vector<DMatch> matches;

    img1 = imread("/home/bolsista/Documents/treinamento-pdi/samples/paint.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    img2 = imread("/home/bolsista/Documents/treinamento-pdi/samples/objects.png", CV_LOAD_IMAGE_GRAYSCALE);

    detectorSURF.detect(img1, vecKeyPoint1);
    detectorSURF.detect(img2, vecKeyPoint2);

    extractor.compute(img1, vecKeyPoint1, descriptorImg1);
    extractor.compute(img2, vecKeyPoint2, descriptorImg2);

    matcher.match(descriptorImg1, descriptorImg2, matches);

    drawMatches(img1, vecKeyPoint1, img2, vecKeyPoint2, matches, result);

    imshow("result image", result);

    imwrite("/home/bolsista/Documents/treinamento-pdi/results/52_surf_detection.jpg", result);

    waitKey(0);
    return 0;
}

