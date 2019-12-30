#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("../samples/baboon.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("baboon_colored", CV_WINDOW_AUTOSIZE);

    imshow("baboon_colored", image);

    imwrite("../results/baboon_colored.jpg", image);

    waitKey(0);
    return 0;
}

