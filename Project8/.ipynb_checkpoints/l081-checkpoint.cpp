// Ram Reddy
// Period 4
// 04/17/2022

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace std;

using namespace cv;
                       // yaw, pitch, roll == x, y, x
Mat generateRotationMat(double x, double y, double z) {
    return (Mat_<double>(3,3) << cos(x)*cos(y), cos(x)*sin(y)*sin(z)-sin(x)*sin(y), cos(x)*sin(y)*cos(z)+sin(x)*sin(z), sin(x)*cos(y), sin(x)*sin(y)*sin(z)+cos(x)*cos(z), sin(x)*sin(y)*cos(z)-cos(x)*sin(z), (-1)*sin(y), cos(y)*sin(z), cos(y)*cos(z));
}

void part1() {
    int angle = 20;
    Mat rotationMatrix = generateRotationMat(0,(angle*M_PI)/180 ,(angle*M_PI)/180);
    vector<Mat> squarePoints;
    squarePoints.push_back((Mat_<double>(3,1) << 1,1,1));
    squarePoints.push_back((Mat_<double>(3,1) << -1,1,1));
    squarePoints.push_back((Mat_<double>(3,1) << -1,-1,1));
    squarePoints.push_back((Mat_<double>(3,1) << -1,1,-1));
    squarePoints.push_back((Mat_<double>(3,1) << 1,-1,-1));
    squarePoints.push_back((Mat_<double>(3,1) << -1,-1,-1));
    squarePoints.push_back((Mat_<double>(3,1) << 1,-1,1));
    squarePoints.push_back((Mat_<double>(3,1) << 1,1,-1));
    for (int i =0; i<360/angle; i++) {
        
    }
    cout << "M = " << endl << " "  << rotationMatrix << endl << endl;
    
}

int main() {
    part1();
    return 0;
}