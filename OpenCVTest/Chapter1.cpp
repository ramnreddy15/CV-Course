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


    
    ///////////////////////////// Showing an image
//     Mat image;
//     image = imread( argv[1], 1 );
// 
//     if ( !image.data )
//     {
//         printf("No image data \n");
//         return -1;
//     }
//     imshow("Tardigrades", image);
//      waitKey(0);
    ////////////////////////////
    
    /////////////////////////// Showing a video
    VideoCapture cap(argv[1]);
    Mat image;
    while (true) {
        cap.read(image);
        imshow("GIF", image);
        waitKey(100);

    }

    return 0;
}
