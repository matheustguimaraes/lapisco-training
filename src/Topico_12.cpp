#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


int main() {
    FILE *txtDocument;
    char txtValues[5000];
    int reference, lines = -1, columns = -1;

    txtDocument = fopen("/home/bolsista/Documents/treinamento-pdi/results/10_image.txt", "r");

    while (!feof(txtDocument)) {
        fgets(txtValues, 5000, txtDocument);
        lines++;
    }

    rewind(txtDocument);

    while (!feof(txtDocument)) {
        fscanf(txtDocument, "%d", &reference);
        columns++;
    }

    columns = columns / lines;

    rewind(txtDocument);

    Mat_<uchar> tiger(lines, columns, 1);

    for (int x = 0; x < lines; x++) {
        for (int y = 0; y < columns; y++) {
            fscanf(txtDocument, "%d", &reference);
            tiger.at<uchar>(x, y) = reference;
        }
    }

    fclose(txtDocument);

    imshow("txt image", tiger);

    imwrite("/home/matheus/Dropbox/treinamento-pdi/results/12_txt_to_tiger.jpg", tiger);

    cvWaitKey(0);
    return 0;
}
