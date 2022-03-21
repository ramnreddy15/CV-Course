#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

using namespace cv;

int main()
{
    // Creates a blank image
    Mat image = Mat(512,512,CV_8UC3, Scalar(255,255,255));
    
    // Drwaing shapes and text
    circle(image, Point(256,256), 155, Scalar(0,69,255), FILLED);
    rectangle(image, Point(130,226), Point(382, 286), Scalar(255,255,255), FILLED);
    line(image, Point(130, 296), Point(382, 296), Scalar(255,255,255), 2);
    putText(image, "This is COOL", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75,Scalar(0,69,255), 2);
    
    imwrite("./Images/blankImage.jpg",image);
//     imwrite("./croppedImage.jpg",croppedImage);
    
    return 0;
}
