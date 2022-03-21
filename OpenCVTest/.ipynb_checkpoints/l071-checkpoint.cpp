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
    Mat orgImage = image.clone();
    Mat grayImage, blurImage, cannyImage, dilateImage, erodeImage, roi;
    vector<Vec3f> circles;
    int threshold1 = 50, threshold2 = 100, minDist = 150, minPercentage = 29;
    double amount = 0;
    int coinsP = 0, coinsN = 0, coinsD = 0, coinsQ = 0, coinsS = 0;
    vector < int > coinTypes;
    
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    ////////////////////////// Basic Functions
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    GaussianBlur(grayImage, blurImage, Size(5,5), 0 ,0 );
    Canny(blurImage, cannyImage, threshold1, threshold2);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    dilate(cannyImage, dilateImage, kernel);
    imwrite("./Images/dilateImage.jpg",dilateImage);
    HoughCircles(cannyImage, circles, HOUGH_GRADIENT, 1,
                 minDist,  // change this value to detect circles with different distances to each other
                 threshold2, minPercentage, 70, 130 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    
    for( size_t  i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        int leftX = c[0]-c[2], leftY = c[1]-c[2];
        if(leftX < 0) {
            leftX = 0;
        }
        if(leftY < 0) {
            leftY = 0;
        }
        roi = image(Rect(leftX, leftY, 2*c[2], 2*c[2]));
        Mat mask(roi.rows, roi.cols, CV_8UC3, Scalar(0,0,0));
        circle(mask, Point(c[2],c[2]), c[2], Scalar(255,255,255), FILLED);
        mask = roi&mask;
        Scalar mean1 = mean(mask);
//         imwrite("./Images/roi.jpg",roi);
//         imwrite("./Images/mask.jpg",roi&mask);
//         if(abs(((mean1[0]+mean1[1]+mean1[2])/3)- 200) > 20){
            Point center = Point(c[0], c[1]);
            // circle center
            circle( image, center, 1, Scalar(0,100,100), 3, LINE_AA);
            // circle outline
            int radius = c[2];
            circle( image, center, radius, Scalar(255,0,255), 3, LINE_AA);
//         }
       
//         if(i == 0) {
// //             Rect rois(0, 0, 2*c[2], 2*c[2]);       
            
//         }
    }
    
    if (combo[i].getY() + start >= 150) {
         if (stupidSumR > 1.3 * stupidSumB) {
              realCenter.erase(realCenter.begin() +i);
              combo.erase(combo.begin() +i);
              i--;
              amount+=0;                     
         } else {
         amount += 1;
         coinTypes.push_back(5);
         coinsS += 1; 
       }
      } else if (combo[i].getY() + start >= 103) {
         if (stupidSumR > 1.3 * stupidSumB) {
              realCenter.erase(realCenter.begin() +i);
              combo.erase(combo.begin() +i);
              i--;
              amount+=0;                     
         } else {
             amount += .25;
             coinTypes.push_back(1);
             coinsQ += 1;                     
         }

     }
     else if (combo[i].getY() + start > 80 && combo[i].getY() + start < 103) {
         if (stupidSumR > 1.3 * stupidSumB) {
             amount += .01;
             coinTypes.push_back(3);
             coinsP += 1;
         } else {
             amount += .05;
             coinTypes.push_back(2);
             coinsN += 1;
         }
     } else {
          if (stupidSumR > 1.3 * stupidSumB) {
             amount += .01;
             coinTypes.push_back(3);
             coinsP += 1;
         } else {
             coinsD += 1;
             amount += .1;
             coinTypes.push_back(4);
          }

     }
     
         for (long unsigned int i = 0; i < realCenter.size(); i++) {
             if (coinTypes[i] == 1) {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeQ);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeQ[0], shadeQ[1], shadeQ[2], false);
             } else if (coinTypes[i] == 2) {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeN);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeN[0], shadeN[1], shadeN[2], false);
             } else if (coinTypes[i] == 3) {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeP);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeP[0], shadeP[1], shadeP[2], false);
             } else if (coinTypes[i] == 4) {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeD);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeD[0], shadeD[1], shadeD[2], false);
             } else {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeS);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeS[0], shadeS[1], shadeS[2], false);
             }

         }
         cout << coinsS << " Silver Dollars, " << coinsQ << " Quarters, " << coinsD << " Dimes, " << coinsN << " Nickels, " << coinsP << " Pennies, " << "Total Sum: $" << amount << endl;
         ofstream outfile("results.txt");
         outfile << coinsS << " Silver Dollars, " << coinsQ << " Quarters, " << coinsD << " Dimes, " << coinsN << " Nickels, " << coinsP << " Pennies, " << "Total Sum: $" << amount << endl;
         outfile.close();
    imwrite("./Images/DetectCircle.jpg",image);

    return 0;
}

// Do later