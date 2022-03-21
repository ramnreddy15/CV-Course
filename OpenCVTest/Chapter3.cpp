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
    Mat resizedImage, croppedImage;
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    // Resize and crop
    resize(image, resizedImage, Size(100,100)); // Can use decimals instead to scale the iamge dynamically use resize(image, resizedImage, Size(),0.5,0.5); 
    
    Rect roi(10,10,100,100);
    croppedImage = image(roi);

    imwrite("./resizedImage.jpg",resizedImage);
    imwrite("./croppedImage.jpg",croppedImage);
    
    return 0;
}
