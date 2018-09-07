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

void getAutoBlobImages(IplImage *img) {
    IplImage *cannyImg, *labelImg, *blobImg;
    CvBlobs blobs;
    CvContourPolygon *polygon, *simplePolygon;
    CvRect rectangle;
    int count = 0;
    char nameBlobUnit[100] = {0};

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
        rectangle = cvRect((*iterator).second->minx, (*iterator).second->miny,
                           ((*iterator).second->maxx - (*iterator).second->minx),
                           (*iterator).second->maxy - (*iterator).second->miny);
        cvSetImageROI(blobImg, rectangle);
        count++;

        sprintf(nameBlobUnit, "blob %d", count);
        cvShowImage(nameBlobUnit, blobImg);
        cvResetImageROI(blobImg);

        delete polygon;
        delete simplePolygon;
    }

    cvShowImage("image with colored square blobs", blobImg);

    cvReleaseImage(&img);
    cvReleaseImage(&cannyImg);
    cvReleaseImage(&labelImg);
    cvReleaseImage(&blobImg);

    cvReleaseBlobs(blobs);
}

int main() {
    IplImage *img = cvLoadImage("/home/matheus/Dropbox/treinamento-pdi/samples/paint.jpg", CV_LOAD_IMAGE_COLOR);

    cvShowImage("original image", img);

    getAutoBlobImages(img);

    cvWaitKey(0);

    return 0;
}

