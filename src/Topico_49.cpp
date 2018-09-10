#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"
#include <fstream>
#include "lbp.h"
#include "histogram.h"
#include <vector>
#include <fstream>
#include <sys/time.h>

using namespace std;
using namespace cv;
using namespace lbp;


vector<float> getLbpExtraction(Mat image) {
    Mat lbpImg = OLBP(image);
    Mat spatialHist;
    vector<float> featureVector;

    normalize(lbpImg, lbpImg, 1, 0, NORM_MINMAX, CV_8UC1);

    spatial_histogram(lbpImg, spatialHist, 1, Size(30, 30), 0);

    for (int i = 0; i < spatialHist.cols; ++i) {
        if (spatialHist.at<int>(0, i) != -1) {
            featureVector.push_back(spatialHist.at<int>(0, i));
        }
    }

    return featureVector;
}

void getFileLbp(Mat img) {
    FILE *file;
    Mat imageMat;
    vector<float> vecLBP;
    int square = 300;

    Size sizeMat(square, square);

    resize(img, imageMat, sizeMat);

    vecLBP = getLbpExtraction(imageMat);

    printf("number of local binary pattern: %.1lu\n", vecLBP.size());

    file = fopen("/home/bolsista/Documents/treinamento-pdi/results/49_LBP.txt", "w");
    for (unsigned long l = 0; l < vecLBP.size(); l += 1) {
        fprintf(file, "lbp %d = %.2f\n", int(l) + 1, vecLBP.at(l));
    }
    fclose(file);
}

int main() {
    Mat img = imread("/home/bolsista/Documents/treinamento-pdi/samples/paint.jpg", IMREAD_GRAYSCALE);

    getFileLbp(img);

    return 0;
}
