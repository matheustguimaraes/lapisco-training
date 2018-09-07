#include <iostream>
#if (defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || (defined(__APPLE__) & defined(__MACH__)))
#include <cv.h>
#include <highgui.h>
#else
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif
#include <cvblob.h>

using namespace std;
using namespace cv;
using namespace cvb;

int main() {
    CvBlobs blobs;
    IplImage *img, *cannyImage, *labelImg;

    img = cvLoadImage("/home/matheus/Dropbox/treinamento-pdi/samples/objects.png", CV_LOAD_IMAGE_COLOR);

    cannyImage = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

    labelImg = cvCreateImage(cvGetSize(cannyImage), IPL_DEPTH_LABEL, 1);

    cvCvtColor(img, cannyImage, CV_RGB2GRAY);

    cvCanny(cannyImage, cannyImage, 127, 255, 3);

    cvLabel(cannyImage, labelImg, blobs);

    cvFilterByArea(blobs, 1, 1000);

    printf("contours: %lu \n", blobs.size());

    cvShowImage("original image", img);

    cvReleaseImage(&img);
    cvReleaseImage(&cannyImage);
    cvReleaseImage(&labelImg);

    cvReleaseBlobs(blobs);

    cvWaitKey(0);
    return 0;
}

