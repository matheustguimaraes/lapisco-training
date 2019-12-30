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

IplImage *getBlobImage(IplImage *img) {
    IplImage *cannyImg, *labelImg, *blobImg;
    CvBlobs blobs;
    CvContourPolygon *polygon, *simplePolygon;

    cannyImg = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

    blobImg = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);

    labelImg = cvCreateImage(cvGetSize(cannyImg), IPL_DEPTH_LABEL, 1);

    cvCvtColor(img, cannyImg, CV_RGB2GRAY);

    cvCanny(cannyImg, cannyImg, 127, 255, 3);

    cvLabel(cannyImg, labelImg, blobs);

    cvFilterByArea(blobs, 1, 1000);

    cvZero(blobImg);

    for (CvBlobs::const_iterator iterator = blobs.begin(); iterator != blobs.end(); ++iterator) {
        cvRenderBlob(labelImg, (*iterator).second, cannyImg, blobImg, CV_BLOB_RENDER_COLOR);
        cvRenderBlob(labelImg, (*iterator).second, cannyImg, blobImg, CV_BLOB_RENDER_BOUNDING_BOX);
        polygon = cvConvertChainCodesToPolygon(&(*iterator).second->contour);
        simplePolygon = cvSimplifyPolygon(polygon, 0.1);
        cvRenderContourPolygon(simplePolygon, blobImg, CV_RGB(0, 255, 0));

        delete polygon;
        delete simplePolygon;
    }

    cvReleaseImage(&cannyImg);
    cvReleaseImage(&labelImg);

    cvReleaseBlobs(blobs);

    return blobImg;
}

int main() {
    IplImage *img, *blobImg;

    img = cvLoadImage("../samples/paint.jpg", CV_LOAD_IMAGE_COLOR);

    blobImg = getBlobImage(img);

    cvShowImage("original image", img);
    cvShowImage("image with colored square blobs", blobImg);

    cvReleaseImage(&img);
    cvReleaseImage(&blobImg);

    cvWaitKey(0);

    return 0;
}

