#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"
#include <fstream>
#include <cmath>

using namespace std;
using namespace cv;

void getGLCM(Mat &img) {
    FILE *file;
    float energy = 0, contrast = 0, homogeneity = 0;
    float idm = 0, entropy = 0, mean1 = 0, dissimilarity = 0;
    float asmOfImg = 0, correlation = 0;
    float mean2 = 0, mean3 = 0, omegai = 0, omegaj = 0;
    float variance = 0, sumEntropy = 0, sumVariance = 0, sumAverage = 0;
    float differenceEntropy = 0, differenceVariance = 0;
    int sizeOfImg = 256;

    int row = img.rows, col = img.cols;

    Mat gl = Mat::zeros(sizeOfImg, sizeOfImg, CV_32FC1);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            gl.at<float>(img.at<uchar>(i, j), img.at<uchar>(i, j + 1))++;
        }
    }

    gl = gl + gl.t();
    gl = gl / sum(gl)[0];

    for (int i = 0; i < sizeOfImg; i++) {
        for (int j = 0; j < sizeOfImg; j++) {
            contrast = contrast + (i - j) * (i - j) * gl.at<float>(i, j);

            homogeneity = homogeneity + gl.at<float>(i, j) / (1 + abs(i - j));

            dissimilarity = dissimilarity + gl.at<float>(i, j) * (abs(i - j));

            asmOfImg = asmOfImg + (gl.at<float>(i, j) * gl.at<float>(i, j));

            energy = energy + sqrt(asmOfImg);

            if (i != j) {
                idm = idm + gl.at<float>(i, j) /
                            ((i - j) * (i - j));
            }

            if (gl.at<float>(i, j) != 0) {
                entropy = entropy - gl.at<float>(i, j) * log10(gl.at<float>(i, j));
            }

            mean2 = mean2 + i * gl.at<float>(i, j);
            mean3 = mean3 + j * gl.at<float>(i, j);
            omegai = omegai + sqrt(gl.at<float>(i, j) * (i - mean2) * (i - mean2));
            omegaj = omegaj + sqrt(gl.at<float>(i, j) * (j - mean3) * (j - mean3));

            if (i != 0 && j != 0) {
                correlation = correlation + ((((i * j) * (gl.at<float>(i, j))) - (mean2 * mean3)) / (omegai * omegaj));
            }

            variance += ((i - (mean2 + mean3) / 2) * (i - (mean2 + mean3) / 2)) * gl.at<float>(i, j);

            for (int k = 2; k < 513; k++) {
                if (i + j == k && gl.at<float>(k) > 0) {
                    sumEntropy -= (gl.at<float>(k)) * log10(gl.at<float>(k));
                    sumVariance += (i - sumEntropy) * (i - sumEntropy) * (gl.at<float>(k));
                    sumAverage += i * gl.at<float>(k);
                }
            }

            for (int k = 0; k < 256; k++) {
                if (i - j == k && gl.at<float>(k) > 0) {
                    differenceEntropy += gl.at<float>(k) * log10(gl.at<float>(k));
                    differenceVariance += (i - (mean2 + mean3) / 2) * (i - (mean1 + mean2) / 2) * (gl.at<float>(k));
                }
            }
        }
    }

    file = fopen("/home/bolsista/Documents/treinamento-pdi/results/50_glcm.txt", "w");
    fprintf(file, "energy = %f\n", energy);
    fprintf(file, "contrast = %f\n", contrast);
    fprintf(file, "homogeneity = %f\n", homogeneity);
    fprintf(file, "idm = %f\n", idm);
    fprintf(file, "entropy = %f\n", entropy);
    fprintf(file, "dissimilarity = %f\n", dissimilarity);
    fprintf(file, "asm = %f\n", asmOfImg);
    fprintf(file, "correlation = %f\n", correlation);
    fprintf(file, "difference of variance = %f\n", differenceVariance);
    fprintf(file, "difference of entropy = %f\n", differenceEntropy);
    fprintf(file, "sum of entropy = %f\n", sumEntropy);
    fprintf(file, "sum of variance = %f\n", sumVariance);
    fprintf(file, "sum of average = %f\n", sumAverage);
    fclose(file);
}

int main() {
    Mat img = imread("/home/bolsista/Documents/treinamento-pdi/samples/paint.jpg", IMREAD_GRAYSCALE);

    getGLCM(img);

    return 0;
}
