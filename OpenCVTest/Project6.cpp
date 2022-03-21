#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image = imread(argv[1], 1);
    Mat grayImage, blurImage, cannyImage, dilateImage, erodeImage;
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    ////////////////////////// Basic Functions
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    GaussianBlur(grayImage, blurImage, Size(3,3), 0 ,0 );
    Canny(blurImage, cannyImage, 50, 100);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    dilate(cannyImage, dilateImage, kernel);
    erode(cannyImage, erodeImage, kernel);

    imshow("Original", image);
    imshow("grayImage", grayImage);
    imshow("Blurred", blurImage);
    imshow("Edge", cannyImage);
    imshow("Dilate", dilateImage);
    imshow("Erode", erodeImage);

    waitKey(0);
    return 0;
}

// Do later