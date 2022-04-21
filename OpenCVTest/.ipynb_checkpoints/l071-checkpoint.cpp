// Ram Reddy
// Period 4
// 3/20/2022

#include <stdio.h>

#include <iostream>

#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace std;

using namespace cv;

void part1(int threshold1, int threshold2, string filename, int minDist, int minPercentage, int minRadius, int maxRadius, int blur, int quarterLimit) {
    Mat image = imread(filename, 1);
    Mat orgImage = image.clone();
    Mat grayImage, blurImage, cannyImage, dilateImage, roi;
    Mat grayImage2, blurImage2, cannyImage2, dilateImage2;
    vector < Vec3f > circles, circles2;
        vector < int > coinTypes;
    double amount = 0;
    int coinsP = 0, coinsN = 0, coinsD = 0, coinsQ = 0, coinsS = 0;
    int shadeP[3] = {
        0,
        0,
        255
    };
    int shadeN[3] = {
        128,
        0,
        128
    };
    int shadeD[3] = {
        255,
        0,
        0
    };
    int shadeQ[3] = {
        0,
        255,
        0
    };
    int shadeS[3] = {
        0,
        255,
        255
    };
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    imwrite("./imageg.jpg", grayImage);
    GaussianBlur(grayImage, blurImage, Size(blur, blur), 0, 0);
    Canny(blurImage, cannyImage, threshold1, threshold2);
    imwrite("./imagef.jpg", cannyImage);
    if (maxRadius <= 130) {
        HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1,
            minDist,
            threshold2, minPercentage, minRadius, maxRadius
        );
    } else {
        HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1,
            minDist,
            threshold2, minPercentage, minRadius, 120
        );
    }

    for (int i = 0; i < circles.size(); i++) {
        Vec3i c = circles[i];
        int leftX = c[0] - c[2], leftY = c[1] - c[2];
        if (leftX < 0) {
            leftX = 0;
        }
        if (leftY < 0) {
            leftY = 0;
        }
        roi = image(Rect(leftX, leftY, 2 * c[2], 2 * c[2]));
        Mat mask(roi.rows, roi.cols, CV_8UC3, Scalar(0, 0, 0));
        circle(mask, Point(c[2], c[2]), c[2], Scalar(255, 255, 255), FILLED);
        mask = roi & mask;
        Scalar mean1 = mean(mask);
        int stupidSumB = mean1.val[0], stupidSumG = mean1.val[1], stupidSumR = mean1.val[2];
        if ((stupidSumB + stupidSumR + stupidSumG) / 3 > 215) {
            circles.erase(circles.begin() + i);
            i--;
            amount += 0;
        } else if (c[2] >= quarterLimit) {
            if (stupidSumR > 1.3 * stupidSumB) {
                circles.erase(circles.begin() + i);
                i--;
                amount += 0;
            } else {
                amount += .25;
                coinTypes.push_back(1);
                coinsQ += 1;
            }

        } else if (c[2] > 80 && c[2] < quarterLimit) {
            if (stupidSumR > 1.3 * stupidSumB || (stupidSumB + stupidSumR + stupidSumG) / 3 < 50) {
                amount += .01;
                coinTypes.push_back(3);
                coinsP += 1;
            } else {
                amount += .05;
                coinTypes.push_back(2);
                coinsN += 1;
            }
        } else {
            if (stupidSumR > 1.3 * stupidSumB || (stupidSumB + stupidSumR + stupidSumG) / 3 < 50) {
                amount += .01;
                coinTypes.push_back(3);
                coinsP += 1;
            } else {
                coinsD += 1;
                amount += .1;
                coinTypes.push_back(4);
            }

        }
    }
    if (maxRadius > 130) {
        HoughCircles(grayImage, circles2, HOUGH_GRADIENT, 1,
            minDist,
            threshold2, minPercentage, 150, maxRadius
        );
        for (int i = 0; i < circles2.size(); i++) {
            circles.push_back(circles2[i]);
            amount += 1;
            coinTypes.push_back(5);
            coinsS += 1;
        }
    }

    for (int i = 0; i < circles.size(); i++) {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        if (coinTypes[i] == 1) {
            circle(image, center, 0, Scalar(shadeQ[0], shadeQ[1], shadeQ[2]), 4, LINE_AA);
            circle(image, center, c[2], Scalar(shadeQ[0], shadeQ[1], shadeQ[2]), 4, LINE_AA);
        } else if (coinTypes[i] == 2) {
            circle(image, center, 0, Scalar(shadeN[0], shadeN[1], shadeN[2]), 4, LINE_AA);
            circle(image, center, c[2], Scalar(shadeN[0], shadeN[1], shadeN[2]), 4, LINE_AA);
        } else if (coinTypes[i] == 3) {
            circle(image, center, 0, Scalar(shadeP[0], shadeP[1], shadeP[2]), 4, LINE_AA);
            circle(image, center, c[2], Scalar(shadeP[0], shadeP[1], shadeP[2]), 4, LINE_AA);
        } else if (coinTypes[i] == 4) {
            circle(image, center, 0, Scalar(shadeD[0], shadeD[1], shadeD[2]), 4, LINE_AA);
            circle(image, center, c[2], Scalar(shadeD[0], shadeD[1], shadeD[2]), 4, LINE_AA);
        } else {
            circle(image, center, 0, Scalar(shadeS[0], shadeS[1], shadeS[2]), 4, LINE_AA);
            circle(image, center, c[2], Scalar(shadeS[0], shadeS[1], shadeS[2]), 4, LINE_AA);
        }

    }
    cout << coinsS << " Silver Dollars, " << coinsQ << " Quarters, " << coinsD << " Dimes, " << coinsN << " Nickels, " << coinsP << " Pennies, " << "Total Sum: $" << amount << endl;
    ofstream outfile("results.txt");
    outfile << coinsS << " Silver Dollars, " << coinsQ << " Quarters, " << coinsD << " Dimes, " << coinsN << " Nickels, " << coinsP << " Pennies, " << "Total Sum: $" << amount << endl;
    outfile.close();
    imwrite("./coins.jpg", image);
}

int main(int argc, char ** argv) {
    int threshold1 = 50, threshold2 = 100, minDist = 105, minPercentage = 40, maxRadius = 130, minRadius = 70, blur = 5, quarterLimit = 105;
    string filename = "";
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-L") == 0) {
            threshold1 = stoi(string(argv[i + 1]));
        }
        if (strcmp(argv[i], "-H") == 0) {
            threshold2 = stoi(string(argv[i + 1]));
        }
        if (strcmp(argv[i], "-F") == 0) {
            filename = string(argv[i + 1]);
        }
        if (strcmp(argv[i], "-MDist") == 0) {
            minDist = stoi(string(argv[i + 1]));
        }
        if (strcmp(argv[i], "-TCircle") == 0) {
            minPercentage = stoi(string(argv[i + 1]));
        }
        if (strcmp(argv[i], "-MinRadius") == 0) {
            maxRadius = stoi(string(argv[i + 1]));
        }
        if (strcmp(argv[i], "-MaxRadius") == 0) {
            maxRadius = stoi(string(argv[i + 1]));
        }
        if (strcmp(argv[i], "-Blur") == 0) {
            blur = stoi(string(argv[i + 1]));
        }
        if (strcmp(argv[i], "-QLimit") == 0) {
            quarterLimit = stoi(string(argv[i + 1]));
        }
    }

    part1(threshold1, threshold2, filename, minDist, minPercentage, minRadius, maxRadius, blur, quarterLimit);
    return 0;
}